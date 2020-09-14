
#ifndef __board_H
#define __board_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "main.h"
/*
* Define board specific parameters here
*/
#define LCD_BL_PIN GPIO_PIN_1
#define LCD_BL_PORT GPIOA

#define LCD_TOUCH_INT GPIO_PIN_5
#define LCD_TOUCH_CS GPIO_PIN_4
#define LCD_TOUCH_PORT GPIOC

//for spi flash PA5-TP_SCK/PA6-TP_MISO/PA7-TP_MOSI
#define FLASH_CS_Pin GPIO_PIN_9 //used elsewhere in w25qxxconf.h
#define FLASH_CS_GPIO_Port GPIOB 


#define BUZZER_PIN GPIO_PIN_2
#define BUZZER_PORT GPIOA

#ifdef __cplusplus
}
#endif
#endif /*__ board_H */
