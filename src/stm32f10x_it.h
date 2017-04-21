#pragma once

#ifdef __cplusplus
extern "C" {
#endif 

#include <stm32f10x.h>

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void) __attribute__ ( ( isr, naked ) );
void SysTick_Handler(void) __attribute__ ( ( isr) );

#ifdef __cplusplus
}
#endif 