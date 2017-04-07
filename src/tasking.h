#pragma once

#include "utils.h"

#define RETURN_HANDLER_NONFP_MSP 0xFFFFFFF1
#define RETURN_THREAD_NONFP_MSP 0xFFFFFFF9
#define RETURN_THREAD_NONFP_PSP 0xFFFFFFFD
#define RETURN_HANDLER_FP_MSP 0xFFFFFFE1
#define RETURN_THREAD_FP_MSP 0xFFFFFFE9
#define RETURN_THREAD_FP_PSP 0xFFFFFFED

#define DEFAULT_PSR_STATUS 0x01000000

#define USER_STACK_SIZE 512 // temporary hardcoded stack size
#define MAX_USER_TASK 32

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _taskReturns {
    TASK_NOT_EXIST = -1,
    TASK_DELETED = 1
} taskReturns;

typedef enum _taskStatus {
    SLEEP,
    RUNNING,
    IDLE,
    STOPPED,
} taskStatus;

typedef struct _coreRegisters {
    u32 r4;
    u32 r5;
    u32 r6;
    u32 r7;
    u32 r8;
    u32 r9;
    u32 r10;
    u32 r11;
} coreRegisters;

typedef struct _hwRegisters {
    u32 r0;
    u32 r1;
    u32 r2;
    u32 r3;
    u32 r12;
    u32 lr;
    u32 pc;
    u32 psr;
} hwRegisters;

typedef struct _task {
    taskStatus status;
    u32* taskStack;
    u32* sp;
    u32* spEnd;
    u8 priority;
} task;

typedef struct _listNode {
    task* task;
    struct _listNode* nextNode;
    u8 pid;
} listNode;

typedef struct _taskList {
    listNode* firstNode; // remove it
    listNode* currentNode;
    listNode* lastNode;
    u32 numberOfTasks;
} taskList;

extern taskList globalTaskList;

u8 isFirstNode(listNode* node);
u8 isLastNode(listNode* node);
u8 isCurrentNode(listNode* node);

void freeNode(listNode* nodePtr);
u32 getTaskSizeInBytes();
listNode* addTaskToList(task* taskPtr);
taskReturns deleteTaskFromList(u8 pid);
listNode* findTask(u8 searchingPid);
listNode* findTaskReturnPrev(u8 searchingPid);
void configureTask(task* taskPtr, u32 functionAddress);
void initialize_t();
int contextSwitch();
u32* scheduler();
u8 nextFreePid();

void store_context();
void load_context();
void continue_user_task(u32* stack);
void initializeMultiTasking();
u32* get_PSP();

#ifdef __cplusplus
}
#endif