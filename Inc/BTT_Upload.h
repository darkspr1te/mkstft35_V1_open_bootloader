#ifndef _BOOT_H_
#define _BOOT_H_

#include "main.h"
#include "stdint.h"
#define W25QXX_SECTOR_SIZE (0x1000) // 4096-4K

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define bool _Bool
#ifndef LOGO_MAX_SIZE
  #define LOGO_MAX_SIZE            0x4B000
  #define WORD_UNICODE_SIZE       0x480000
  #define BYTE_ASCII_SIZE           0x1000
  #define LARGE_FONT_SIZE           0x3000
  #define ICON_MAX_SIZE             0x5000
  #define STRINGS_STORE_MAX_SIZE    0x5000    //label strings max size
  #define PRINT_GCODES_MAX_SIZE     0x5000    //start/end/cancel gcodes  max size
  #define CUSTOM_GCODE_MAX_SIZE     0x5000    //custom gocdes max size
  #define INFOBOX_MAX_SIZE          0xB000
  #define SMALL_ICON_MAX_SIZE       0x2000
#endif

//address in spiflash W25Qxx
#define LOGO_ADDR               0x0
#define WORD_UNICODE            LOGO_MAX_SIZE    // unicode (+0x480000 4.5M)
#define BYTE_ASCII_ADDR         (WORD_UNICODE + WORD_UNICODE_SIZE)    // ascii (+0x1000 4K)
#define LARGE_FONT_ADDR         (BYTE_ASCII_ADDR + BYTE_ASCII_SIZE)   // Large ascii font
//#define BYTE_RESERVE_ADDR      0x710000
#define STRINGS_STORE_ADDR      (LARGE_FONT_ADDR + LARGE_FONT_SIZE)   //for label strings from config file
#define PRINT_GCODES_ADDR       (STRINGS_STORE_ADDR + STRINGS_STORE_MAX_SIZE)   //for start/end/cancel gcodes from config file
#define CUSTOM_GCODE_ADDR       (PRINT_GCODES_ADDR + PRINT_GCODES_MAX_SIZE)   //for custom gcodes from config file

#define ICON_ADDR(num)          ((num) * ICON_MAX_SIZE + CUSTOM_GCODE_ADDR+CUSTOM_GCODE_MAX_SIZE)


#define ROOT_DIR "MKS"
#define HARDWARE "MKSTFT35_V1_0"
#define ADMIN_MODE_FILE "0:admin.txt"
//#define FIRMWARE_NAME STRINGIFY(HARDWARE) "." STRINGIFY(SOFTWARE_VERSION)
#define BMP_ROOT_DIR "0:" ROOT_DIR "/bmp"
#define FONT_ROOT_DIR "0:" ROOT_DIR "/font"
#define TFT_RESET_FILE "0:reset.txt"

//This List is Auto-Generated. Please add new icons in icon_list.h only

//This List is Auto-Generated. Please add new icons in small_icon_list.h only

typedef enum{
BMP_SUCCESS,
BMP_NOTFOUND,
BMP_NOT24BIT,
BMP_INVALIDFILE
}BMPUPDATE_STAT;

typedef union
{
  u16 color;
  struct{
  u16  b:5;
  u16  g:6;
  u16  r:5;
 }RGB;
}GUI_COLOR;

void scanUpdates(void);
void dispIconFail(u8 *lbl);
bool bmpDecode(char *bmp, u32 addr);

#endif
