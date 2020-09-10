#ifndef __board_H
#define __board_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "main.h"
#include "stm32_adafruit_lcd.h"
#define PIC_MAX_CN		100			
#define PIC_NAME_MAX_LEN		50	

#define LOGO_MAX_SIZE			(300*1024) 
#define TITLELOGO_MAX_SIZE		(150*1024) 
#define DEFAULT_VIEW_MAX_SIZE 	(200*200*2)
#define FLASH_VIEW_MAX_SIZE 			(200*200*2)

#define PIC_NAME_ADDR			0x003000	
#define PIC_SIZE_ADDR			0x007000	
#define PIC_COUNTER_ADDR		0x008000
#define PIC_LOGO_ADDR			0x009000
#define DEFAULT_VIEW_ADDR		0XC5800
#define BAK_VIEW_ADDR					(DEFAULT_VIEW_ADDR+90*1024)
#define PIC_ICON_LOGO_ADDR 	(BAK_VIEW_ADDR+80*1024)
#define PIC_DATA_ADDR				(PIC_ICON_LOGO_ADDR+350*1024)	
#define FONTINFOADDR	0x600000
#define UNIGBK_FLASH_ADDR		(FONTINFOADDR+4096)//1024
#define GBK_FLASH_ADDR	(UNIGBK_FLASH_ADDR+180224)//176*1024

#define PER_PIC_MAX_SPACE		(32*1024)

union union32
{
	uint8_t bytes[4];
	uint32_t dwords;
};

struct pic_msg
{
	uint8_t name[PIC_NAME_MAX_LEN];
	union union32 size;
};

typedef struct pic_msg PIC_MSG;

void test_pic();
void DRAW_LOGO();
void Pic_Read(uint8_t *Pname,uint8_t *P_Rbuff);
void Draw_default_preview(int xpos_pixel,int ypos_pixel,uint8_t sel);

#ifdef __cplusplus
}
#endif
#endif /*__ board_H */

