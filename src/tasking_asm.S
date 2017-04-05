.thumb
.syntax unified

.global context_switch
context_switch:

mrs r1, psp
stmdb r1!, {r4 - r11, lr}

ldmia r0!, {r4 - r11, lr}
msr psp, r0

bx lr

.global continue_user_task
continue_user_task:

mov r0, #3    /* psp, unprivilieged, fpu active */
msr control, r0

bx lr


.type get_PSP, %function
.global get_PSP
get_PSP:
   mrs r0,psp
   bx lr