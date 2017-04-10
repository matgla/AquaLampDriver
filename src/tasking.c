#include <string.h> // for memcopy
#include <stdlib.h>
#include <stm32f4xx.h>

#include "tasking.h"
#include "hw_utils.h"
//#include "lcd.h"
#include "utils.h"
#include <stdio.h>

taskList globalTaskList;

volatile int pid = 1;
static int first = 1;
void initialize_t() {
    pid = 1;
    globalTaskList.numberOfTasks = 0;
    globalTaskList.currentNode = NULL;
    globalTaskList.lastNode = NULL;
}

u32 getTaskSizeInBytes() {
    return (u32)USER_STACK_SIZE;
}

u8 nextFreePid() {
    return pid++;           // change this naive implementation in future
}

listNode* findTask(u8 searchingPid) {
    if (globalTaskList.currentNode == NULL) return NULL;
    listNode *node = globalTaskList.currentNode;
    u8 nrOfTasks = globalTaskList.numberOfTasks;
    do {
        if (node->pid == searchingPid) {
             return node;
        }
        node = node->nextNode;
    } while (--nrOfTasks);
    return NULL;
}

listNode* findTaskReturnPrev(u8 searchingPid) {
    listNode *node = globalTaskList.currentNode;
    if (node == NULL) return;
    u8 nrOfTasks = globalTaskList.numberOfTasks;
    while(nrOfTasks--) {
        if (node->nextNode->pid == searchingPid) return node;
        node = node->nextNode;
    }
    return NULL;
}

void freeNode(listNode *nodePtr) {
    if (!nodePtr) {
        return;
    }
    if (nodePtr->task->taskStack) {
        free(nodePtr->task->taskStack);
    }
    free(nodePtr);

}

u8 isFirstNode(listNode *node) {
    return node->pid == globalTaskList.firstNode->pid;
}

u8 isLastNode(listNode *node) {
    return (node->pid == globalTaskList.lastNode->pid);
}

u8 isCurrentNode(listNode *node) {
    return (node->pid == globalTaskList.currentNode->pid);
}

taskReturns deleteTaskFromList(u8 pid) {
    listNode* prevTask;
    listNode* node;
    prevTask = findTaskReturnPrev(pid);
    if(NULL != prevTask) {
        node = prevTask->nextNode;
        if (globalTaskList.numberOfTasks == 1) {
            globalTaskList.currentNode = NULL;
            globalTaskList.lastNode = NULL;
            globalTaskList.numberOfTasks = 0;
            freeNode(prevTask);
            return TASK_DELETED;
        }
        if (globalTaskList.currentNode == prevTask->nextNode) {
            globalTaskList.currentNode = prevTask->nextNode->nextNode;
        }
        if (globalTaskList.lastNode == prevTask->nextNode) {
            globalTaskList.lastNode = prevTask;
        }
        prevTask->nextNode = prevTask->nextNode->nextNode;
        globalTaskList.numberOfTasks--;
        freeNode(node);
        return TASK_DELETED;
    }
    return TASK_NOT_EXIST;
}

listNode* addTaskToList(task *taskPtr) {
    listNode *newNode = (listNode *)malloc(sizeof(listNode));
    newNode->task = taskPtr;
    newNode->pid = nextFreePid();

    if (globalTaskList.numberOfTasks == 0) {
        globalTaskList.currentNode = newNode;
        newNode->nextNode = newNode;
    } else {
        newNode->nextNode = globalTaskList.lastNode->nextNode;
        globalTaskList.lastNode->nextNode = newNode;
    }

    globalTaskList.lastNode = newNode;
    globalTaskList.numberOfTasks++;

    return newNode;
}

void task_finish()
{
    printf("Task finished\n");
    while(true) {}
}

void configureTask(task *taskPtr, u32 functionAddress) {
	void* stack = taskPtr->taskStack;
    
	coreRegisters* core = (coreRegisters*)(stack + USER_STACK_SIZE*sizeof(u32) - sizeof(coreRegisters) - sizeof(hwRegisters));
	hwRegisters* hw = (hwRegisters*)(stack + USER_STACK_SIZE*sizeof(u32) - sizeof(hwRegisters));


    if (first) { // First task should be sleep task ( idle task ), and lr points to function address, because it won't be started in handle mode 
		core->lr = functionAddress;
		first = 0;
	} else {
		core->lr = RETURN_THREAD_NONFP_PSP;
		
		hw->lr = (unsigned) &task_finish;
		hw->pc = (unsigned int) functionAddress;
		hw->psr = (unsigned int) 0x01000000;
	}

    taskPtr->sp = (void*)core;
}

void scheduler() {
    // globalTaskList.currentNode = globalTaskList.currentNode->nextNode;
    // return globalTaskList.currentNode->task->sp;
}

void initializeMultiTasking() {
	//initialize();
    NVIC_SetPriorityGrouping( 0b011 );
    initalizeSysTick(1);
    __set_BASEPRI( 0 );
    NVIC_SetPriority( PendSV_IRQn, 0xFF );

  //  __set_PSP((u32)globalTaskList.currentNode->task->sp+9);
 //   load_context();
    //__set_CONTROL(0x03);
   // __ISB();
    printf("init multi tasking\n");
    //asm("svc 1");
    //SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void multi_start()
{
    // TODO: fix for saving msp state here
    asm volatile("mov r0, %0\n" : : "r" (globalTaskList.currentNode->task->sp));
    asm volatile("msr psp, r0\n");

    asm volatile("mrs r0, psp");
    asm volatile("ldmia r0!, {r4 - r11, lr}");
    asm volatile("mov r0, #0x03\n");
    asm volatile("msr control, r0\n");
    asm volatile("isb\n");
    asm volatile("bx lr\n");
}

void __attribute__((naked)) PendSV_Handler(void)
{
    asm volatile("mrs r0, psp");
    asm volatile("stmdb r0!, {r4 - r11, lr}");
    asm volatile("msr psp, r0");

    globalTaskList.currentNode->task->sp = __get_PSP();
    globalTaskList.currentNode = globalTaskList.currentNode->nextNode;
    
	__set_PSP(globalTaskList.currentNode->task->sp);

    asm volatile("mrs r0, psp");
    asm volatile("ldmia r0!, {r4 - r11, lr}");
    asm volatile("msr psp, r0");
    asm volatile("bx lr");
}

