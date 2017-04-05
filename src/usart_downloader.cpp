#include <stm32f4xx_flash.h>

#include <cstdlib>

#include "usart_downloader.hpp"


using usart = hw::USART<hw::USARTS::USART1_PP1>;

UsartDownloader::UsartDownloader(Logger& logger)
    : logger_(logger)
{
}

#define FLASH_WRP_SECTORS (OB_WRP_Sector_1) /* sectors 2 and 3  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define FLASH_USER_START_ADDR ADDR_FLASH_SECTOR_4 /* Start address of user Flash area */

#if defined(USE_STM324xG_EVAL)
#define FLASH_USER_END_ADDR ADDR_FLASH_SECTOR_11 /* End address of user Flash area */

#else                                            /* USE_STM324x7I_EVAL or USE_STM324x9I_EVAL */
#define FLASH_USER_END_ADDR ADDR_FLASH_SECTOR_23 /* End address of user Flash area */
#endif

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0 ((uint32_t)0x08000000)  /* Base address of Sector 0, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_1 ((uint32_t)0x08004000)  /* Base address of Sector 1, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_2 ((uint32_t)0x08008000)  /* Base address of Sector 2, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_3 ((uint32_t)0x0800C000)  /* Base address of Sector 3, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_4 ((uint32_t)0x08010000)  /* Base address of Sector 4, 64 Kbytes   */
#define ADDR_FLASH_SECTOR_5 ((uint32_t)0x08020000)  /* Base address of Sector 5, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_6 ((uint32_t)0x08040000)  /* Base address of Sector 6, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_7 ((uint32_t)0x08060000)  /* Base address of Sector 7, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_8 ((uint32_t)0x08080000)  /* Base address of Sector 8, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_9 ((uint32_t)0x080A0000)  /* Base address of Sector 9, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x080C0000) /* Base address of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x080E0000) /* Base address of Sector 11, 128 Kbytes */

#define ADDR_FLASH_SECTOR_12 ((uint32_t)0x08100000) /* Base address of Sector 12, 16 Kbytes  */
#define ADDR_FLASH_SECTOR_13 ((uint32_t)0x08104000) /* Base address of Sector 13, 16 Kbytes  */
#define ADDR_FLASH_SECTOR_14 ((uint32_t)0x08108000) /* Base address of Sector 14, 16 Kbytes  */
#define ADDR_FLASH_SECTOR_15 ((uint32_t)0x0810C000) /* Base address of Sector 15, 16 Kbytes  */
#define ADDR_FLASH_SECTOR_16 ((uint32_t)0x08110000) /* Base address of Sector 16, 64 Kbytes  */
#define ADDR_FLASH_SECTOR_17 ((uint32_t)0x08120000) /* Base address of Sector 17, 128 Kbytes */
#define ADDR_FLASH_SECTOR_18 ((uint32_t)0x08140000) /* Base address of Sector 18, 128 Kbytes */
#define ADDR_FLASH_SECTOR_19 ((uint32_t)0x08160000) /* Base address of Sector 19, 128 Kbytes */
#define ADDR_FLASH_SECTOR_20 ((uint32_t)0x08180000) /* Base address of Sector 20, 128 Kbytes */
#define ADDR_FLASH_SECTOR_21 ((uint32_t)0x081A0000) /* Base address of Sector 21, 128 Kbytes */
#define ADDR_FLASH_SECTOR_22 ((uint32_t)0x081C0000) /* Base address of Sector 22, 128 Kbytes */
#define ADDR_FLASH_SECTOR_23 ((uint32_t)0x081E0000) /* Base address of Sector 23, 128 Kbytes */

#define DATA_32 ((uint32_t)0x12345678)

uint32_t uwStartSector = 0;
uint32_t uwEndSector = 0;
uint32_t uwAddress = 0;
uint32_t uwSectorCounter = 0;

__IO uint32_t uwData32 = 0;
__IO uint32_t uwMemoryProgramStatus = 0;

static uint32_t GetSector(uint32_t Address)
{
    uint32_t sector = 0;

    if ((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
    {
        sector = FLASH_Sector_0;
    }
    else if ((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
    {
        sector = FLASH_Sector_1;
    }
    else if ((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
    {
        sector = FLASH_Sector_2;
    }
    else if ((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
    {
        sector = FLASH_Sector_3;
    }
    else if ((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
    {
        sector = FLASH_Sector_4;
    }
    else if ((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
    {
        sector = FLASH_Sector_5;
    }
    else if ((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
    {
        sector = FLASH_Sector_6;
    }
    else if ((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
    {
        sector = FLASH_Sector_7;
    }
    else if ((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
    {
        sector = FLASH_Sector_8;
    }
    else if ((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
    {
        sector = FLASH_Sector_9;
    }
    else if ((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
    {
        sector = FLASH_Sector_10;
    }

#if defined(USE_STM324xG_EVAL)
    else /*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
    {
        sector = FLASH_Sector_11;
    }

#else  /* USE_STM324x7I_EVAL or USE_STM324x9I_EVAL */
    else if ((Address < ADDR_FLASH_SECTOR_12) && (Address >= ADDR_FLASH_SECTOR_11))
    {
        sector = FLASH_Sector_11;
    }

    else if ((Address < ADDR_FLASH_SECTOR_13) && (Address >= ADDR_FLASH_SECTOR_12))
    {
        sector = FLASH_Sector_12;
    }
    else if ((Address < ADDR_FLASH_SECTOR_14) && (Address >= ADDR_FLASH_SECTOR_13))
    {
        sector = FLASH_Sector_13;
    }
    else if ((Address < ADDR_FLASH_SECTOR_15) && (Address >= ADDR_FLASH_SECTOR_14))
    {
        sector = FLASH_Sector_14;
    }
    else if ((Address < ADDR_FLASH_SECTOR_16) && (Address >= ADDR_FLASH_SECTOR_15))
    {
        sector = FLASH_Sector_15;
    }
    else if ((Address < ADDR_FLASH_SECTOR_17) && (Address >= ADDR_FLASH_SECTOR_16))
    {
        sector = FLASH_Sector_16;
    }
    else if ((Address < ADDR_FLASH_SECTOR_18) && (Address >= ADDR_FLASH_SECTOR_17))
    {
        sector = FLASH_Sector_17;
    }
    else if ((Address < ADDR_FLASH_SECTOR_19) && (Address >= ADDR_FLASH_SECTOR_18))
    {
        sector = FLASH_Sector_18;
    }
    else if ((Address < ADDR_FLASH_SECTOR_20) && (Address >= ADDR_FLASH_SECTOR_19))
    {
        sector = FLASH_Sector_19;
    }
    else if ((Address < ADDR_FLASH_SECTOR_21) && (Address >= ADDR_FLASH_SECTOR_20))
    {
        sector = FLASH_Sector_20;
    }
    else if ((Address < ADDR_FLASH_SECTOR_22) && (Address >= ADDR_FLASH_SECTOR_21))
    {
        sector = FLASH_Sector_21;
    }
    else if ((Address < ADDR_FLASH_SECTOR_23) && (Address >= ADDR_FLASH_SECTOR_22))
    {
        sector = FLASH_Sector_22;
    }
    else /*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_23))*/
    {
        sector = FLASH_Sector_23;
    }
#endif /* USE_STM324x7I_EVAL or USE_STM324x9I_EVAL */
    return sector;
}

typedef void (*pFunction)(void);
pFunction Jump_To_Application;
uint32_t JumpAddress;
void boot()
{
    u32 ApplicationAddress = 0x08004000;
    USART_Cmd(USART1, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, DISABLE);

    /* Set system control register SCR->VTOR  */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x4000);

    JumpAddress = *(__IO uint32_t*)(ApplicationAddress + 4);
    Jump_To_Application = (pFunction)JumpAddress;
    __set_MSP(*(__IO uint32_t*)ApplicationAddress);
    Jump_To_Application();
}

void UsartDownloader::writeToMemory()
{

    logger_ << Level::INFO << "Waiting for soft\n";
    u32 softwareSize = 0;
    //  usart::getUsart().send(10, 2);
    //  msg = usart::getUsart().getMessage();
    //logger_ << Level::INFO << "Received message: " << msg.payload[0] << ":" << msg.payload[1] << ":" << msg.payload[2] << ":" << msg.payload[3] << ":"  << "\r\n";
    // softwareSize = msg.payload_[0] << 24;
    // softwareSize += msg.payload_[1] << 16;
    // softwareSize += msg.payload_[2] << 8;
    // softwareSize += msg.payload_[3];
    // logger_ << Level::INFO << "Received soft size: " << softwareSize << ":" << msg.payload_[3] << "\r\n";

    u32 receivedSize = 0;
    u8* page = (u8*)0x20005000;
    //u8 page2[100] = {1, 2};
    int i = 0;
    while (receivedSize < softwareSize)
    {
        logger_ << Level::INFO << "Requesting block: "
                << "\r\n";
        //    usart::getUsart().send(10, 3);
        //  auto msg1 = usart::getUsart().getMessage();

        logger_ << Level::INFO << "Received: " << receivedSize << "/" << softwareSize << "\r\n";
        //page[++i%100] = msg1.size;
        // memcpy(page + receivedSize, msg1.payload_, msg1.size_);
        // receivedSize += msg1.size;
        // for(int i = 0; i < msg1.size; ++i)
        // {
        //    mpage[receivedSize++] = msg1.payload[i];
        // }
        // receivedSize += msg1.size_;
    }

    FLASH_Unlock();

    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

    while (FLASH_EraseSector(FLASH_Sector_1, VoltageRange_3) != FLASH_COMPLETE)
    {
    };
    // while (FLASH_EraseSector(FLASH_Sector_2, VoltageRange_3) != FLASH_COMPLETE){};
    // while (FLASH_EraseSector(FLASH_Sector_3, VoltageRange_3) != FLASH_COMPLETE){};
    // while (FLASH_EraseSector(FLASH_Sector_4, VoltageRange_3) != FLASH_COMPLETE){};
    // while (FLASH_EraseSector(FLASH_Sector_5, VoltageRange_3) != FLASH_COMPLETE){};
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
    // //FLASH_ClearFlag();
    for (u32 j = 0; j < softwareSize; j++)
    {
        // logger_ << Level::INFO << "D: " << msg1.payload[i] << "\r\n";
        int code;
        u8 byte = page[j];
        if ((code = FLASH_ProgramByte(0x08004000 + j, byte)) == FLASH_COMPLETE)
        {
            //logger_ << Level::ERROR << "Writing flash correct \r\n";
        }
        else if (code == FLASH_BUSY)
        {
            logger_ << Level::ERROR << "Writing flash failed FLASH_BUSY \r\n";
            return;
        }
        else if (code == FLASH_ERROR_PROGRAM)
        {
            logger_ << Level::ERROR << "Writing flash failed FLASH_ERROR_PROGRAM \r\n";
            return;
        }
        else if (code == FLASH_ERROR_WRP)
        {
            logger_ << Level::ERROR << "Writing flash failed FLASH_ERROR_WRP \r\n";
            return;
        }
        else if (code == FLASH_ERROR_OPERATION)
        {
            logger_ << Level::ERROR << "Writing flash failed FLASH_ERROR_OPERATION \r\n";
            return;
        }

        u8* data = (u8*)(0x08004000 + j);
        if (*data != page[j])
        {
            logger_ << Level::INFO << "Writing failed( " << 0x08004000 + j << "): " << *data << " != " << page[i] << "\r\n";
            return;
        }
    }

    FLASH_Lock();
    logger_ << Level::INFO << "Booting new software\r\n";

    boot();
}


void UsartDownloader::waitForProvider()
{
    char downloadCommand[4] = "DWN";
    char buffer[10];
    bool connection = false;
    int index = 0;
    logger_ << Level::INFO << "Waiting for connection \r\n";
    while (!connection)
    {
        //  usart::getUsart().send(10, 1);

        logger_ << Level::INFO << "Waiting for message!\r\n";
        // auto msg = usart::getUsart().getMessage();
        // logger_ << Level::INFO << "Received message with: " << msg.fd_ << "\r\n";
        //   if (msg.fd_ == 10 && msg.payload_[0] == 1)
        //   {
        //       logger_ << Level::INFO << "Connected to device\r\n";
        //        connection = true;
        //    }

        //     logger_ << Level::INFO << "Received byte: " << (int)data << "\n";
        //     if (data == '\n')
        //     {
        //         if (strcmp(buffer, downloadCommand) == 0)
        //         {
        //             logger_ << Level::INFO << "Received " << buffer << " command\n";
        //         }
        //         index = 0;

        //     }
        //     else
        //     {
        //         buffer[index++] = data;
        //         buffer[index] = 0;
        //         logger_ << Level::INFO << "Current  " << buffer << " command\n";

        //     }
    }
    logger_ << Level::INFO << "Exit form func\r\n";
}