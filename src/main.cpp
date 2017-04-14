#include "stm32f4xx.h"
#include "stm32f4xx_rtc.h"
#include <boost/sml.hpp>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "kernel.hpp"
#include "logger.hpp"
#include "state_machine/bootloader_sm.hpp"
#include "types.h"
#include "utils.hpp"
#include "usart.hpp"

#include "tasking.h"

// __IO uint32_t uwAsynchPrediv = 0;
// __IO uint32_t uwSynchPrediv = 0;
//   uint8_t aShowTime[50] = {0};

// void RTC_Config()
// {
//     RTC_DateTypeDef rtc;
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
//     PWR_BackupAccessCmd(ENABLE);
//     RCC_LSICmd(ENABLE);
//     while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET) {}
//     RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
//     /* ck_spre(1Hz) = RTCCLK(LSI) /(uwAsynchPrediv + 1)*(uwSynchPrediv + 1)*/
//   uwSynchPrediv = 0xFF;
//   uwAsynchPrediv = 0x7F;
//   RCC_RTCCLKCmd(ENABLE);

//   /* Wait for RTC APB registers synchronisation */
//   RTC_WaitForSynchro();
  
//   /* Configure the RTC data register and RTC prescaler */
//   RTC_InitStructure.RTC_AsynchPrediv = uwAsynchPrediv;
//   RTC_InitStructure.RTC_SynchPrediv = uwSynchPrediv;
//   RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
//   RTC_Init(&RTC_InitStructure);
  
//   /* Set the alarm 05h:20min:30s */
//   RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
//   RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = 0x05;
//   RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x20;
//   RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x30;
//   RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
//   RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
//   RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
  
//   /* Configure the RTC Alarm A register */
//   RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);
  
//   /* Enable RTC Alarm A Interrupt */
//   RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  
//   /* Enable the alarm */
//   RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
  
//   RTC_ClearFlag(RTC_FLAG_ALRAF);
  
//   /* Set the date: Friday January 11th 2013 */
//   RTC_DateStructure.RTC_Year = 0x13;
//   RTC_DateStructure.RTC_Month = RTC_Month_January;
//   RTC_DateStructure.RTC_Date = 0x11;
//   RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Saturday;
//   RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
  
//   /* Set the time to 05h 20mn 00s AM */
//   RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
//   RTC_TimeStructure.RTC_Hours   = 0x05;
//   RTC_TimeStructure.RTC_Minutes = 0x20;
//   RTC_TimeStructure.RTC_Seconds = 0x00; 
  
//   RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);   
  
//   /* Indicator for the RTC configuration */
//   RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
// }

int main(void)
{
    SystemInit();
    hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    Logger logger("boot\0");

    hardwareInitialize();

    boost::sml::sm<BootLoaderSm> sm{logger};

    sm.process_event(evInitialize{});
    sm.process_event(evGetBootMode{});
    sm.process_event(evBoot{});
   
    while (1)
    {
        //printf("Iam in loop\n");
        int i = 0;
        for(int j = 0; j < 1000000; j++)
        {
            for (int y = 0; y < 10000; y++)
            {
                i += i;
            }
        }
        sm.process_event(evInitialize{});
    }
}


void assert_failed(u8* file, u32 line)
{
    write(0, file, strlen((char*)file));
    write(0, ":", 1);
    char buf[10];
    utils::itoa(line, buf, 10);
    write(0, buf, strlen(buf));
    write(0, " assertion failed!", 18);
    while (true)
    {
        
    }
}
