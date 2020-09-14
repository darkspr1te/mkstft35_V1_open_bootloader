#ifndef __ILI9486_H__
#define __ILI9486_H__
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "main.h"
#define cmdReg *(__IO uint16_t *) (0x60000000)
//#define dataReg *(__IO uint16_t *)(0x607FFFFE)
#define dataReg *(__IO uint16_t *)(0x60040000)


// LCD Size Defenition
#ifndef WIDTH
#define WIDTH       	480         		/* Screen Width (in pixels)           */
#define HEIGHT      	320             /* Screen Hight (in pixels)           */
#define LCD_HOR_RES WIDTH
#define LCD_VER_RES HEIGHT
#endif
//

#define ILI9488_NOP           0x00
#define ILI9488_SWRESET       0x01
#define ILI9488_RDDID         0x04
#define ILI9488_RDDST         0x09

#define ILI9488_SLPIN         0x10
#define ILI9488_SLPOUT        0x11
#define ILI9488_PTLON         0x12
#define ILI9488_NORON         0x13

#define ILI9488_RDMODE        0x0A
#define ILI9488_RDMADCTL      0x0B
#define ILI9488_RDPIXFMT      0x0C
#define ILI9488_RDIMGFMT      0x0D
#define ILI9488_RDSELFDIAG    0x0F

#define ILI9488_INVOFF        0x20
#define ILI9488_INVON         0x21
#define ILI9488_GAMMASET      0x26
#define ILI9488_DISPOFF       0x28
#define ILI9488_DISPON        0x29

#define ILI9488_CASET         0x2A
#define ILI9488_PASET         0x2B
#define ILI9488_RAMWR         0x2C
#define ILI9488_RAMRD         0x2E

#define ILI9488_PTLAR         0x30
#define ILI9488_VSCRDEF       0x33
#define ILI9488_MADCTL        0x36
#define ILI9488_VSCRSADD      0x37
#define ILI9488_PIXFMT        0x3A
#define ILI9488_RAMWRCONT     0x3C
#define ILI9488_RAMRDCONT     0x3E

#define ILI9488_IMCTR         0xB0
#define ILI9488_FRMCTR1       0xB1
#define ILI9488_FRMCTR2       0xB2
#define ILI9488_FRMCTR3       0xB3
#define ILI9488_INVCTR        0xB4
#define ILI9488_DFUNCTR       0xB6

#define ILI9488_PWCTR1        0xC0
#define ILI9488_PWCTR2        0xC1
#define ILI9488_PWCTR3        0xC2
#define ILI9488_PWCTR4        0xC3
#define ILI9488_PWCTR5        0xC4
#define ILI9488_VMCTR1        0xC5
#define ILI9488_VMCTR2        0xC7

#define ILI9488_RDID1         0xDA
#define ILI9488_RDID2         0xDB
#define ILI9488_RDID3         0xDC
#define ILI9488_RDID4         0xDD

#define ILI9488_GMCTRP1       0xE0
#define ILI9488_GMCTRN1       0xE1
#define ILI9488_IMGFUNCT      0xE9

#define ILI9488_ADJCTR3       0xF7

#define ILI9488_MAD_RGB       0x08
#define ILI9488_MAD_BGR       0x00

#define ILI9488_MAD_VERTICAL  0x20
#define ILI9488_MAD_X_LEFT    0x00
#define ILI9488_MAD_X_RIGHT   0x40
#define ILI9488_MAD_Y_UP      0x80
#define ILI9488_MAD_Y_DOWN    0x00
/*
#define ILI9488_MAX_X                      (ILI9488_LCD_PIXEL_HEIGHT - 1)
#define ILI9488_MAX_Y                      (ILI9488_LCD_PIXEL_WIDTH - 1)
#define ILI9488_MAD_DATA_RIGHT_THEN_UP     ILI9488_MAD_COLORMODE | ILI9488_MAD_X_LEFT  | ILI9488_MAD_Y_DOWN   | ILI9488_MAD_VERTICAL
#define ILI9488_MAD_DATA_RIGHT_THEN_DOWN   ILI9488_MAD_COLORMODE | ILI9488_MAD_X_RIGHT | ILI9488_MAD_Y_UP   | ILI9488_MAD_VERTICAL
#define ILI9488_SETCURSOR(x, y)            {LCD_IO_WriteCmd8(ILI9488_CASET); LCD_IO_WriteData16_to_2x8(ILI9488_MAX_X - x); LCD_IO_WriteData16_to_2x8(ILI9488_MAX_X - x); LCD_IO_WriteCmd8(ILI9488_PASET); LCD_IO_WriteData16_to_2x8(ILI9488_MAX_Y - y); LCD_IO_WriteData16_to_2x8(ILI9488_MAX_Y - y);}
*/
#if (LCD_ORIENTATION == 0)
#define ILI9488_MAX_X                      (ILI9488_LCD_PIXEL_WIDTH - 1)
#define ILI9488_MAX_Y                      (ILI9488_LCD_PIXEL_HEIGHT - 1)
#define ILI9488_MAD_DATA_RIGHT_THEN_UP     ILI9488_MAD_COLORMODE | ILI9488_MAD_X_RIGHT | ILI9488_MAD_Y_UP
#define ILI9488_MAD_DATA_RIGHT_THEN_DOWN   ILI9488_MAD_COLORMODE | ILI9488_MAD_X_RIGHT | ILI9488_MAD_Y_DOWN
#define ILI9488_SETCURSOR(x, y)            {LCD_IO_WriteCmd8(ILI9488_CASET); LCD_IO_WriteData16_to_2x8(ILI9488_MAX_X - x); LCD_IO_WriteData16_to_2x8(ILI9488_MAX_X - x); LCD_IO_WriteCmd8(ILI9488_PASET); LCD_IO_WriteData16_to_2x8(y); LCD_IO_WriteData16_to_2x8(y);}
#elif (LCD_ORIENTATION == 1)
#define ILI9488_MAX_X                      (ILI9488_LCD_PIXEL_HEIGHT - 1)
#define ILI9488_MAX_Y                      (ILI9488_LCD_PIXEL_WIDTH - 1)
#define ILI9488_MAD_DATA_RIGHT_THEN_UP     ILI9488_MAD_COLORMODE | ILI9488_MAD_X_RIGHT | ILI9488_MAD_Y_DOWN | ILI9488_MAD_VERTICAL
#define ILI9488_MAD_DATA_RIGHT_THEN_DOWN   ILI9488_MAD_COLORMODE | ILI9488_MAD_X_LEFT  | ILI9488_MAD_Y_DOWN | ILI9488_MAD_VERTICAL
#define ILI9488_SETCURSOR(x, y)            {LCD_IO_WriteCmd8(ILI9488_CASET); LCD_IO_WriteData16_to_2x8(x); LCD_IO_WriteData16_to_2x8(x); LCD_IO_WriteCmd8(ILI9488_PASET); LCD_IO_WriteData16_to_2x8(y); LCD_IO_WriteData16_to_2x8(y);}
#elif (LCD_ORIENTATION == 2)
#define ILI9488_MAX_X                      (ILI9488_LCD_PIXEL_WIDTH - 1)
#define ILI9488_MAX_Y                      (ILI9488_LCD_PIXEL_HEIGHT - 1)
#define ILI9488_MAD_DATA_RIGHT_THEN_UP     ILI9488_MAD_COLORMODE | ILI9488_MAD_X_LEFT  | ILI9488_MAD_Y_DOWN
#define ILI9488_MAD_DATA_RIGHT_THEN_DOWN   ILI9488_MAD_COLORMODE | ILI9488_MAD_X_LEFT  | ILI9488_MAD_Y_UP
#define ILI9488_SETCURSOR(x, y)            {LCD_IO_WriteCmd8(ILI9488_CASET); LCD_IO_WriteData16_to_2x8(x); LCD_IO_WriteData16_to_2x8(x); LCD_IO_WriteCmd8(ILI9488_PASET); LCD_IO_WriteData16_to_2x8(ILI9488_MAX_Y - y); LCD_IO_WriteData16_to_2x8(ILI9488_MAX_Y - y);}
#else
#define ILI9488_MAX_X                      (ILI9488_LCD_PIXEL_HEIGHT - 1)
#define ILI9488_MAX_Y                      (ILI9488_LCD_PIXEL_WIDTH - 1)
#define ILI9488_MAD_DATA_RIGHT_THEN_UP     ILI9488_MAD_COLORMODE | ILI9488_MAD_X_LEFT  | ILI9488_MAD_Y_UP   | ILI9488_MAD_VERTICAL
#define ILI9488_MAD_DATA_RIGHT_THEN_DOWN   ILI9488_MAD_COLORMODE | ILI9488_MAD_X_RIGHT | ILI9488_MAD_Y_UP   | ILI9488_MAD_VERTICAL
#define ILI9488_SETCURSOR(x, y)            {LCD_IO_WriteCmd8(ILI9488_CASET); LCD_IO_WriteData16_to_2x8(x); LCD_IO_WriteData16_to_2x8(x); LCD_IO_WriteCmd8(ILI9488_PASET); LCD_IO_WriteData16_to_2x8(y); LCD_IO_WriteData16_to_2x8(y);}
#endif




#if ILI9488_COLORMODE == 0
#define ILI9488_MAD_COLORMODE    ILI9488_MAD_RGB
#else
#define ILI9488_MAD_COLORMODE    ILI9488_MAD_BGR
#endif

//
#define ILI9341_RESET			 		    	0x01
#define ILI9341_SLEEP_OUT		  			0x11
#define ILI9341_GAMMA			    			0x26
#define ILI9341_DISPLAY_OFF					0x28
#define ILI9341_DISPLAY_ON					0x29
#define ILI9341_COLUMN_ADDR					0x2A
#define ILI9341_PAGE_ADDR			  		0x2B
#define ILI9341_GRAM				    		0x2C
#define ILI9341_TEARING_OFF					0x34
#define ILI9341_TEARING_ON					0x35
#define ILI9341_DISPLAY_INVERSION		0xb4
#define ILI9341_MAC			        		0x36
#define ILI9341_PIXEL_FORMAT    		0x3A
#define ILI9341_WDB			    	  		0x51
#define ILI9341_WCD				      		0x53
#define ILI9341_RGB_INTERFACE   		0xB0
#define ILI9341_FRC					    	0xB1
#define ILI9341_BPC					    	0xB5
#define ILI9341_DFC				 	    	0xB6
#define ILI9341_Entry_Mode_Set		0xB7
#define ILI9341_POWER1						0xC0
#define ILI9341_POWER2						0xC1
#define ILI9341_VCOM1							0xC5
#define ILI9341_VCOM2							0xC7
#define ILI9341_POWERA						0xCB
#define ILI9341_POWERB						0xCF
#define ILI9341_PGAMMA						0xE0
#define ILI9341_NGAMMA						0xE1
#define ILI9341_DTCA							0xE8
#define ILI9341_DTCB							0xEA
#define ILI9341_POWER_SEQ					0xED
#define ILI9341_3GAMMA_EN					0xF2
#define ILI9341_INTERFACE					0xF6
#define ILI9341_PRC				   	  	0xF7
#define ILI9341_VERTICAL_SCROLL 	0x33

#define ILI9341_MEMCONTROL         0x36
#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

/* LCD RGB color definitions */
#define Black           0x0000			/*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255, 0   */
#define White           0xFFFF      /* 255, 255, 255 */
#define WHITE           0XFFFF      /* 255, 255, 255 */   
#define RED             0xF800      /* 255,   0,   0 */
#define BLUE            0x001F      /*   0,   0, 255 */


void TFT_Switch_Init();
void TFT_Init(); //Initialization
void TFT_Clear (uint16_t color); // Clears the LCD to color
static void TFT_WriteCMD(uint16_t Data); 
static void TFT_WriteData(uint16_t data);
void TFT_CMDData(uint16_t cmd, uint16_t data);
void LCD_WriteRAM(uint16_t data);
void LCD_Window(int16_t Xstart, int16_t Xend, int16_t Ystart, int16_t Yend); // Sets the LCD write window
void LCD_setWindowArea(uint16_t StartX, uint16_t StartY, uint16_t Width, uint16_t Height);
static void LCD_WindowMax(); // Sets the LCD write window to maximum.
void TFT_setTextColor(int16_t color); // sets text color.
void TFT_setBackgroundColor(int16_t color); // sets background color.
void TFT_DisplayChar (unsigned int ln, unsigned int col, unsigned char c);
void TFT_Show();

void TFT_DrawPixel(int16_t x, int16_t y, int16_t color); // Puts just a pixel.

void TFT_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t color);
void TFT_DrawLineVertical(int16_t starty, int16_t endy, int16_t x, int16_t color);
void TFT_DrawLineHorizontal(int16_t startx, int16_t endx, int16_t y, int16_t color);

void TFT_DrawCircle(int16_t x0, int16_t y0, int16_t r, int16_t color);
void TFT_DrawFillCircle(int16_t x0, int16_t y0, int16_t r, int16_t color);

void TFT_DrawFillRect(int16_t startx, int16_t starty, int16_t endx, int16_t endy, int16_t color);  
void TFT_DrawRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t color);

void TFT_DrawChar(int16_t x, int16_t y, char character, int16_t color);

void TFT_SetFontSize(uint16_t sizeFont);
void TFT_DrawString(int16_t x, int16_t y, char *string, int16_t color);
void TFT_DrawButton(int16_t x, int16_t y, char *string, int16_t color, int16_t BackgroundColor);

void TFT_DrawBitmap(uint16_t *image);

static int16_t TFT_ReadPins();
static int16_t TFT_ReadData();
static int16_t TFT_ReadStatus();





#endif