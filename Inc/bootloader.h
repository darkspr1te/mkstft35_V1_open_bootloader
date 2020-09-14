
#ifndef __bootloader_H
#define __bootloader_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ILI9488.h"
#include "time.h"

#define BOOT_ADDR FLASH_SECTOR_3_ADDR
#define APP_ADDR             BOOT_ADDR


#define BOOTLADER_VERSION "V 1.0.9"
#define BOOTLOADER_PATRONS "iz3man, Gilles, Yur_vol"

#define BOOTLOAD_SPLASH "iGeek Zambia - Bootloader - MKS TFT 35"


extern void MX_SPI1_Init(void);


#ifdef __cplusplus
}
#endif
#endif /*__ bootloader_H */
