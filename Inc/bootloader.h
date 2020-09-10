
#ifndef __bootloader_H
#define __bootloader_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32_adafruit_lcd.h"
#include "time.h"
#define BOOT_ADDR FLASH_SECTOR_3_ADDR
#define APP_ADDR             BOOT_ADDR


#define BOOTLOADER_VERSION "V 1.1.0"
#define BOOTLOADER_PATRONS "izeman, Gilles, Yur_vol"

#define BOOTLOAD_SPLASH "iGeek Zambia - Bootloader - MKS TFT 35"


extern void MX_SPI1_Init(void);


#ifdef __cplusplus
}
#endif
#endif /*__ bootloader_H */
