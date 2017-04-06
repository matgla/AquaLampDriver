#include <string.h> // for memcopy
#include <stdlib.h>
#include <stm32f4xx.h>

#include "tasking.h"
#include "hw_utils.h"
//#include "lcd.h"
#include "utils.h"

taskList globalTaskList;

volatile int pid = 1;

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

void configureTask(task *taskPtr, u32 functionAddress) {
    coreRegisters coreReg;
	hwRegisters hwReg;

    int allocationSize = sizeof(u32)*USER_STACK_SIZE;

	hwReg.psr = DEFAULT_PSR_STATUS;
	hwReg.lr = 0;
	hwReg.pc = functionAddress;

    coreReg.lr = RETURN_THREAD_NONFP_PSP;
    taskPtr->taskStack = (u32*)malloc(allocationSize);
    taskPtr->spEnd = taskPtr->taskStack + USER_STACK_SIZE;
    memcpy(taskPtr->taskStack+9, &hwReg, sizeof(hwRegisters));
    memcpy(taskPtr->taskStack, &coreReg, sizeof(coreRegisters));
    taskPtr->sp = taskPtr->taskStack;
    taskPtr->status = STOPPED;

}

u32* scheduler() {
    globalTaskList.currentNode = globalTaskList.currentNode->nextNode;
    printf("Context switch to: 0x%08x%d\n", globalTaskList.currentNode->task->sp);
    return globalTaskList.currentNode->task->sp;
}

void initializeMultiTasking() {
	//initialize();
	initalizeSysTick(10);
}


void SysTick_Handler(void)  {
    write(0, "systick\n\0", 9);
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;  // Generate PendSV interrupt
}

volatile int first = 1;

void PendSV_Handler(void)
{
    printf("pendSv\n");
  if(first == 1) {
    first++;
	} else {
		globalTaskList.currentNode->task->sp = get_PSP() - 9; 
	}

    
	context_switch(scheduler());
}
