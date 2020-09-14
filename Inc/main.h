

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

#define LCD_ORIENTATION 1
SPI_HandleTypeDef hspi1; 
#define osDelay(x) HAL_Delay(x)

void Error_Handler(void);
//static void MX_SPI1_Init(void);



#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

