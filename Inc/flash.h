#ifndef __FLASH_H
#define __FLASH_H
#include "stm32f4xx.h"
#include "stdint.h"
#include "board.h"
#include "stm32_adafruit_lcd.h"
typedef struct {
    uint8_t entry_sign;
    uint32_t crc;
    uint32_t crc_shadow;
    uint32_t size;          //  Size of firmware image
    uint32_t uuid;          //  Integer representing unique firmware ID
    uint16_t version;       //  Integer representing firmware version
    uint8_t closing_sign;
} FirmwareHeader_t;

typedef enum
{
	FLASH_RESULT_OK = 0,
	FLASH_RESULT_FILE_ERROR,
	FLASH_RESULT_FLASH_ERROR,
	FLASH_FILE_NOT_EXISTS,
	FLASH_FILE_CANNOT_OPEN,
	FLASH_FILE_INVALID_HASH,
	FLASH_FILE_TOO_BIG
} FlashResult;

FlashResult flash(const char *fname);

#define _SECTOR_SIZE 0x3fff
#define FLASH_PAGE_SIZE 0x3fff
#define BOOT_SECT 0xC000
#define FLASH_SIZE (_SECTOR_SIZE*FLASH_SECTOR_TOTAL)


#define FLASH_SECTOR_0_ADDR      0x08000000          // Sector 0, 16 Kbytes
#define FLASH_SECTOR_1_ADDR      0x08004000          // Sector 1, 16 Kbytes
#define FLASH_SECTOR_2_ADDR      0x08008000          // Sector 2, 16 Kbytes
#define FLASH_SECTOR_3_ADDR      0x0800C000          // Sector 3, 16 Kbytes
#define FLASH_SECTOR_4_ADDR      0x08010000          // Sector 4, 64 Kbytes
#define FLASH_SECTOR_5_ADDR      0x08020000          // Sector 5, 128 Kbytes
#define FLASH_SECTOR_6_ADDR      0x08040000          // Sector 6, 128 Kbytes
#define FLASH_SECTOR_7_ADDR      0x08060000          // Sector 7, 128 Kbytes
#define FLASH_SECTOR_8_ADDR      0x08080000          // Sector 8, 128 Kbytes
#define FLASH_SECTOR_9_ADDR      0x080A0000          // Sector 9, 128 Kbytes
#define FLASH_SECTOR_10_ADDR     0x080C0000          // Sector 10, 128 Kbytes
#define FLASH_SECTOR_11_ADDR     0x080E0000          // Sector 11, 128 Kbytes
#define FLASH_LAST_ADDR          0x080FFFFE

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

/* Base address of the Flash sectors Bank 2 */
#define ADDR_FLASH_SECTOR_12     ((uint32_t)0x08100000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_13     ((uint32_t)0x08104000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_14     ((uint32_t)0x08108000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_15     ((uint32_t)0x0810C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_16     ((uint32_t)0x08110000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_17     ((uint32_t)0x08120000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_18     ((uint32_t)0x08140000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_19     ((uint32_t)0x08160000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_20     ((uint32_t)0x08180000) /* Base @ of Sector 8, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_21     ((uint32_t)0x081A0000) /* Base @ of Sector 9, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_22     ((uint32_t)0x081C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_23     ((uint32_t)0x081E0000) /* Base @ of Sector 11, 128 Kbytes */

// clear sector containing 'addr', return 1 on success
uint8_t flash_clear_sector(uint32_t addr);

// clear sectors between 'from_addr' and 'to_addr' (included), return 1 on success
uint8_t flash_clear(uint32_t from_addr, uint32_t to_addr);
uint8_t flash_erase(uint32_t from_addr, uint32_t to_addr);

// program 'size' elements of uint32_t 'data' at 'addr', return next empty address
uint32_t flash_program_by_word(uint32_t addr, const uint32_t *data, uint32_t size);

// program 'size' elements of uint8_t 'data' at 'addr', return next empty address
uint32_t flash_program_by_byte(uint32_t addr, const uint8_t *data, uint32_t size);
static uint32_t GetSector(uint32_t Address);
typedef void (*Callable)();


#define ENTRY_VALUE 0x7E
#define CLOSE_VALUE 0xFE

#define ENTRY_OFFSET 0
#define CRC_OFFSET (ENTRY_OFFSET + sizeof(uint8_t))
#define CRC_SHADOW_OFFSET (CRC_OFFSET + sizeof(uint32_t))
#define SIZE_OFFSET (CRC_SHADOW_OFFSET + sizeof(uint32_t))
#define UUID_OFFSET (SIZE_OFFSET + sizeof(uint32_t))
#define VERSION_OFFSET (UUID_OFFSET + sizeof(uint32_t))
#define CLOSE_OFFSET (VERSION_OFFSET + sizeof(uint16_t))
#define HEADER_SIZE (CLOSE_OFFSET + sizeof(uint8_t))

#define DRIVE_NO 0
/*
Flash mksrobin encrypted firmware
*/
#define NEW_NAME        "mkstft35.cur"
#define CURR_NAME       "0:/mkstft35.bin"
#define BASIC_NAME      "mkstft35.bin"
/*
Flash vanilla firmware
*/
#define VANILLA_CURR    "0:/mkslcd.bin"
#define VANILLA_NEW     "mkslcd.cur"
#define VANILLA_BASIC   "mkslcd.bin"

#endif /* __BOOT_CONF_H */