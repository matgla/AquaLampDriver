.thumb
.syntax unified

.global context_switch
context_switch:

ldmia r0!, {r4 - r11}
msr psp, r0
mov r0, #0x03
msr control, r0
bx lr

.global load_context
load_context:
mrs r0, psp
ldmia r0!, {r4 - r11, lr}
msr psp, r0
;mov r0, #0x03
;msr control, r0

bx lr

.global store_context
store_context:
mrs r0, psp
stmdb r0!, {r4 - r11, lr}
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
