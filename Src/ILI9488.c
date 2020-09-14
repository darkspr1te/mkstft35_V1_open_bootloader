/****
 * ILI9488 Driver For MKS TFT35 using FSMC at 
 * #define cmdReg *(__IO uint16_t *) (0x60000000)
 * #define dataReg *(__IO uint16_t *)(0x607FFFFE)
 * which is A17 or ((1<17)-2)
 * 
 * ****/



#include "ILI9488.h"
#include "Font_24x16.h"



void TFT_Init(); //Initialization
void TFT_Clear (uint16_t color); // Clears the LCD to color
static void TFT_WriteCMD(uint16_t Data); 
static void TFT_WriteData(uint16_t data);
void LCD_Window(int16_t Xstart, int16_t Xend, int16_t Ystart, int16_t Yend); // Sets the LCD write window
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

int16_t textColor = White, BackgroundColor = Black;
int16_t fontSize = 1;


void LCD_WriteRAM_Prepare(void)
{
  	TFT_WriteCMD(ILI9341_GRAM);
}  
void TFT_Switch_Init()
{
	/* Alternate lcd configure & setup */
	#if 1
 	TFT_WriteCMD(0xE0); 
	TFT_WriteData(0x00); 
	TFT_WriteData(0x07); 
	TFT_WriteData(0x0f); 
	TFT_WriteData(0x0D); 
	TFT_WriteData(0x1B); 
	TFT_WriteData(0x0A); 
	TFT_WriteData(0x3c); 
	TFT_WriteData(0x78); 
	TFT_WriteData(0x4A); 
	TFT_WriteData(0x07); 
	TFT_WriteData(0x0E); 
	TFT_WriteData(0x09); 
	TFT_WriteData(0x1B); 
	TFT_WriteData(0x1e); 
	TFT_WriteData(0x0f);  
	TFT_WriteCMD(0xE1); 
	TFT_WriteData(0x00); 
	TFT_WriteData(0x22); 
	TFT_WriteData(0x24); 
	TFT_WriteData(0x06); 
	TFT_WriteData(0x12); 
	TFT_WriteData(0x07); 
	TFT_WriteData(0x36); 
	TFT_WriteData(0x47); 
	TFT_WriteData(0x47); 
	TFT_WriteData(0x06); 
	TFT_WriteData(0x0a); 
	TFT_WriteData(0x07); 
	TFT_WriteData(0x30); 
	TFT_WriteData(0x37); 
	TFT_WriteData(0x0f); 
	TFT_WriteCMD(0xC0); 
	TFT_WriteData(0x10); 
	TFT_WriteData(0x10); 
	TFT_WriteCMD(0xC1); 
	TFT_WriteData(0x41); 
	TFT_WriteCMD(0xC5); 
	TFT_WriteData(0x00); 
	TFT_WriteData(0x22); 
	TFT_WriteData(0x80); 
	TFT_WriteCMD(0x36); 
	int rot=1;
	if(rot == 1)
		{
			TFT_WriteData(0x68); 
		}
	else
		{
			TFT_WriteData(0xA8);
		}

	TFT_WriteCMD(0x3A); //Interface Mode Control
	TFT_WriteData(0x55);
	TFT_WriteCMD(0XB0);  //Interface Mode Control  
	TFT_WriteData(0x00); 
	TFT_WriteCMD(0xB1);   //Frame rate 70HZ  
	TFT_WriteData(0xB0); 
	TFT_WriteData(0x11); 
	TFT_WriteCMD(0xB4); 
	TFT_WriteData(0x02);   
	TFT_WriteCMD(0xB6); //RGB/MCU Interface Control
	TFT_WriteData(0x02); 
	TFT_WriteData(0x42); 
	TFT_WriteCMD(0xB7); 
	TFT_WriteData(0xC6); 
	//WriteComm(0XBE);
	//WriteData(0x00);
	//WriteData(0x04);
	TFT_WriteCMD(0xE9); 
	TFT_WriteData(0x00);
	TFT_WriteCMD(0XF7);    
	TFT_WriteData(0xA9); 
	TFT_WriteData(0x51); 
	TFT_WriteData(0x2C); 
	TFT_WriteData(0x82);
	TFT_WriteCMD(0x11); 
	HAL_Delay(120); 
	TFT_WriteCMD(0x29); 		
 #endif
}

void TFT_Init()
{
/*Configure ili9488 LCD*/
	HAL_Delay(10);
	TFT_WriteCMD(ILI9488_SWRESET);//0x1
	HAL_Delay(5);
	//positivegammacontrol
	TFT_WriteCMD(ILI9488_GMCTRP1);//0xe0
	TFT_WriteData(0x00);
	TFT_WriteData(0x03);
	TFT_WriteData(0x09);
	TFT_WriteData(0x08);
	TFT_WriteData(0x16);
	TFT_WriteData(0x0a);
	TFT_WriteData(0x3f);
	TFT_WriteData(0x78);
	TFT_WriteData(0x4c);
	TFT_WriteData(0x09);
	TFT_WriteData(0x0a);
	TFT_WriteData(0x08);
	TFT_WriteData(0x16);
	TFT_WriteData(0x1a);
	TFT_WriteData(0x0f);
	TFT_WriteCMD(ILI9488_SWRESET);//0x01
	//negativegammacontrol
	TFT_WriteCMD(ILI9488_GMCTRN1);//0xe1
	TFT_WriteData(0x00);
	TFT_WriteData(0x16);
	TFT_WriteData(0x19);
	TFT_WriteData(0x03);
	TFT_WriteData(0x0f);
	TFT_WriteData(0x05);
	TFT_WriteData(0x32);
	TFT_WriteData(0x45);
	TFT_WriteData(0x46);
	TFT_WriteData(0x04);
	TFT_WriteData(0x0e);
	TFT_WriteData(0x0d);
	TFT_WriteData(0x35);
	TFT_WriteData(0x37);
	TFT_WriteData(0x0f);
	//PowerControl1(Vreg1out,Verg2out)
	TFT_WriteCMD(ILI9488_PWCTR1);//0xc0
	TFT_WriteData(0x17);
	TFT_WriteData(0x15);
	HAL_Delay(5);
	//PowerControl2(VGH,VGL)
	TFT_WriteData(ILI9488_PWCTR2);//0xc1	
	TFT_WriteData(0x41);
	HAL_Delay(5);
	//PowerControl3(Vcom)
	TFT_WriteCMD(ILI9488_VMCTR1);//0xc5
	TFT_WriteData(0x00);
	TFT_WriteData(0x12);
	TFT_WriteData(0x70);
	HAL_Delay(5);
	TFT_WriteCMD(ILI9488_PIXFMT);//0x3a	
	TFT_WriteData(0x55);	//InterfacePixelFormat(16bit)
	TFT_WriteCMD(ILI9488_FRMCTR1);	//0xb1
	TFT_WriteData(0xA0);	//Framerate(60Hz)
	TFT_WriteCMD(ILI9488_INVCTR);	//0xb4
	TFT_WriteData(0x02);	//DisplayInversionControl(2-dot)
	TFT_WriteData(0x02);
	TFT_WriteData(0x02);
	TFT_WriteCMD(ILI9488_IMGFUNCT);//0xe9
		TFT_WriteData(0x00);	//SetImageFunctio(Disable24bitdata)
	TFT_WriteCMD(ILI9488_ADJCTR3);//0xf7
	TFT_WriteData(0xa9);
	TFT_WriteData(0x51);
	TFT_WriteData(0x2c);
	TFT_WriteData(0x82);
	HAL_Delay(5);
	TFT_WriteCMD(ILI9488_SLPOUT);	//ExitSleep 0x11
	HAL_Delay(120);
	TFT_WriteCMD(ILI9488_DISPON);	//Displayon 0x29
	HAL_Delay(5);
	TFT_WriteCMD(ILI9488_MADCTL); //0x36
	//	TFT_WriteData(ILI9488_MAD_DATA_RIGHT_THEN_UP);
	//	TFT_WriteData(ILI9488_MAD_DATA_RIGHT_THEN_DOWN);
	TFT_WriteData(0xa8);
#ifdef DEBUG
	printf("LCDID%x",ili9488_ReadID());
#endif
}

void TFT_SetFontSize(uint16_t sizeFont)
{
	fontSize = sizeFont;
}

void TFT_DrawString(int16_t x, int16_t y, char *string, int16_t color)
{
	int i;
	for(i = 0; string[i] != 0; i++) {
		//TFT_DrawChar(x , y+ (8 * i * fontSize) , string[i], color);
		TFT_DrawChar( y+ (8 * i * fontSize),x , string[i], color);
	}
}

void TFT_DrawStringAtLine(int16_t x, int16_t y, char *string, int16_t color)
{
	int i;
	for(i = 0; string[i] != 0; i++) {
		TFT_DrawChar(x , y+ (8 * i * fontSize) , string[i], color);
	}
}

void TFT_DrawButton(int16_t x, int16_t y, char *string, int16_t color, int16_t BackgroundColor)
{
	int c;
	while(string[c] != '\0')
      c++;
	TFT_DrawFillRect(x, y, x + (9 * fontSize * c) + 20, y + 9 + 40, BackgroundColor);
	TFT_setBackgroundColor(BackgroundColor);
	TFT_DrawString(x + 20, y + 20, string, color);
}

void TFT_DrawChar(int16_t x, int16_t y, char character, int16_t color)
{
	int16_t i, j, k, h;
	char *bitmap = font8x8_basic[character];
	
	//void LCD_setWindowArea(uint16_t StartX, uint16_t StartY, uint16_t Width, uint16_t Height)
	//LCD_setWindowArea(x,y,x + (8 * fontSize) -1,y + (8 * fontSize) -1);
	#if 0
	#if 0
	LCD_Window(x, x + (8 * fontSize) -1, y, y + (8 * fontSize) -1);
	#else
	LCD_Window(y, y + (8 * fontSize) -1, x, x + (8 * fontSize) -1);
	#endif
	for(int i = 0; i < 8; i++) {
		for(h = 0; h < fontSize; h++) {
		//	for(int j = 0; j < 8; j++) {
				
				if((font8x8_basic[character][j] >> i) & 0x1) {
					
					for(k = 0; k < fontSize; k++)
						TFT_WriteData(color);
					} else {
					for(k = 0; k < fontSize; k++)
						TFT_WriteData(BackgroundColor);
				
				}
		//	}
		}
	}
	#else
	 // int x,y;
	#if 1
	LCD_Window(x, x + (8 * fontSize) -1, y, y + (8 * fontSize) -1);
	#else
	LCD_Window(y, y + (8 * fontSize) -1, x, x + (8 * fontSize) -1);
	#endif
    int set;
    int mask;
    for (x=0; x < 8; x++) {
        for (y=0; y < 8; y++) {
            set = bitmap[x] & 1 << y;
            //printf("%c", set ? 'X' : ' ');
			TFT_WriteData(set ? color:BackgroundColor);
        }
  
    }
//	HAL_Delay(10);
	#endif

}

void TFT_setTextColor(int16_t color)
{
	textColor = color;
}

void TFT_setBackgroundColor(int16_t color)
{
	BackgroundColor = color;
}

void TFT_Clear(uint16_t color) 
{
	unsigned int   i;

	LCD_WindowMax();

	for(i = 0; i < (HEIGHT*WIDTH); i++) {
		TFT_WriteData(color);
	}
}

void TFT_DrawFillRect(int16_t startx, int16_t starty, int16_t endx, int16_t endy, int16_t color)
{
	unsigned int i;
	unsigned int sizerect = (endx - startx) * (endy - starty);
	LCD_Window(startx, endx-1, starty, endy-1);
	
	for(i=0; i < sizerect; i++) {
		TFT_WriteData(color);
	}
}

void TFT_DrawPixel(int16_t x, int16_t y, int16_t color)
{
	LCD_Window(x, x, y, y);
	
	TFT_WriteData(color);
}

void TFT_DrawCircle(int16_t x0, int16_t y0, int16_t r, int16_t color)
{
	{
    int x = -r, y = 0, err = 2-2*r, e2;
    do {
        TFT_DrawPixel(x0-x, y0+y,color);
        TFT_DrawPixel(x0+x, y0+y,color);
        TFT_DrawPixel(x0+x, y0-y,color);
        TFT_DrawPixel(x0-x, y0-y,color);
        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= 0);
	}
}

void TFT_DrawFillCircle(int16_t x0, int16_t y0, int16_t r, int16_t color)
{
    int x = -r, y = 0, err = 2-2*r, e2;
    do {
        TFT_DrawLineVertical(y0-y, y0+y, x0-x, color);
        TFT_DrawLineVertical(y0-y, y0+y, x0+x, color);
        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= 0);
}

void TFT_DrawRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t color)
{
	if (x1 > x0) TFT_DrawLineHorizontal(x0,x1,y0,color);
	else  TFT_DrawLineHorizontal(x1,x0,y0,color);

	if (y1 > y0) TFT_DrawLineVertical(y0,y1, x0, color);
	else TFT_DrawLineVertical(y1,y0, x0, color);

	if (x1 > x0) TFT_DrawLineHorizontal(x0,x1,y1,color);
	else  TFT_DrawLineHorizontal(x1,x0,y1,color);

	if (y1 > y0) TFT_DrawLineVertical(y0,y1, x1, color);
	else TFT_DrawLineVertical(y1,y0, x1, color);
	return;
}


void TFT_DrawLineHorizontal(int16_t startx, int16_t endx, int16_t y, int16_t color)
{
	int16_t i;
	
	LCD_Window(startx, endx, y, y);
	
	for(i = startx; i <= endx ; i++)
	{
		TFT_WriteData(color);
	}
}

void TFT_DrawLineVertical(int16_t starty, int16_t endy, int16_t x, int16_t color)
{
	int16_t i;
	
	LCD_Window(x, x, starty, endy);
	
	for(i = starty; i <= endy ; i++)
	{
		TFT_WriteData(color);
	}
}

static __inline void LCD_WindowMax()
{
	//LCD_Window(0, HEIGHT-1, 0, WIDTH-1);
	LCD_Window(0, WIDTH-1, 0, HEIGHT-1);
}

int DeviceCode = 0x9488;
void LCD_setWindowArea(uint16_t StartX, uint16_t StartY, uint16_t Width, uint16_t Height)
{
  int8_t s_h,s_l, e_h, e_l;
	
  uint16_t xEnd, yEnd;
	
	xEnd = StartX + Width-1;
	yEnd = StartY + Height-1;   
	
	if((DeviceCode==0x9325)||(DeviceCode==0x9328))
   {
           TFT_CMDData(0x0050,StartY);        //Specify the start/end positions of the window address in the horizontal direction by an address unit
           TFT_CMDData(0x0051,StartY + Height -1);        //Specify the start positions of the window address in the vertical direction by an address unit 
           TFT_CMDData(0x0052,320 - StartX - Width); 
           TFT_CMDData(0x0053,320 - StartX - 1 );        //Specify the end positions of the window address in the vertical direction by an address unit
	 }    
    else  if(DeviceCode==0x5761)    //** 
    {
          TFT_WriteCMD(0X2A);
          TFT_WriteData(StartX>>8);
          TFT_WriteData(StartX&0XFF);
          TFT_WriteData(xEnd>>8);
          TFT_WriteData(xEnd&0XFF);
		
         TFT_WriteCMD(0X2B);	
          TFT_WriteData(StartY>>8);	
          TFT_WriteData(StartY&0XFF);
          TFT_WriteData(yEnd>>8);	
          TFT_WriteData(yEnd&0XFF);                   
    }
		else if(DeviceCode == 0X9488)
		{
			s_h = (StartX >> 8) & 0Xff;
			s_l = StartX & 0Xff;
			e_h = ((StartX + Width - 1) >> 8) & 0Xff;
			e_l = (StartX + Width - 1) & 0Xff;
			
			TFT_WriteCMD(0x2A);
			TFT_WriteData(s_h);
			TFT_WriteData(s_l);
			TFT_WriteData(e_h);
			TFT_WriteData(e_l);
		
			s_h = (StartY >> 8) & 0Xff;
			s_l = StartY & 0Xff;
			e_h = ((StartY + Height - 1) >> 8) & 0Xff;
			e_l = (StartY + Height - 1) & 0Xff;
			
			TFT_WriteCMD(0x2B);
			TFT_WriteData(s_h);
			TFT_WriteData(s_l);
			TFT_WriteData(e_h);
			TFT_WriteData(e_l); 	
		}  

TFT_WriteCMD(ILI9341_GRAM);
}

void LCD_Window(int16_t Xstart, int16_t Xend, int16_t Ystart, int16_t Yend) 
{
	#if 0
	TFT_WriteCMD(ILI9341_PAGE_ADDR); 
	TFT_WriteData(Xstart>>8);
	TFT_WriteData(Xstart&0xff);
	TFT_WriteData(Xend>>8);
	TFT_WriteData(Xend&0xff);

	TFT_WriteCMD(ILI9341_COLUMN_ADDR);  
	   
	TFT_WriteData(Ystart>>8);
	TFT_WriteData(Ystart&0xff);
	TFT_WriteData(Yend>>8);
	TFT_WriteData(Yend&0xff);

	//TFT_WriteCMD(0x3A);    // 16/18 bits
    //TFT_WriteData(0x55);
	
	TFT_WriteCMD(ILI9341_GRAM);
	#else
	TFT_WriteCMD(ILI9341_COLUMN_ADDR);   
	TFT_WriteData(Xstart>>8);
	TFT_WriteData(Xstart&0xff);
	TFT_WriteData(Xend>>8);
	TFT_WriteData(Xend&0xff);

	TFT_WriteCMD(ILI9341_PAGE_ADDR);   
	TFT_WriteData(Ystart>>8);
	TFT_WriteData(Ystart&0xff);
	TFT_WriteData(Yend>>8);
	TFT_WriteData(Yend&0xff);

	//TFT_WriteCMD(0x3A);    // 16/18 bits
    //TFT_WriteData(0x55);
	
	TFT_WriteCMD(ILI9341_GRAM);
	#endif
}

void TFT_Show() {
	LCD_WindowMax();
}

void TFT_DrawBitmap(uint16_t *image)
{
	unsigned int i;
	LCD_Window(0, WIDTH-1, 0, HEIGHT-1);

	for(i = 0; i < (WIDTH*HEIGHT); i++) {
		TFT_WriteData(image[i]);
	}
}
void TFT_CMDData(uint16_t cmd, uint16_t data)
{
	TFT_WriteCMD(cmd);
	TFT_WriteData(data);
}
void LCD_WriteRAM(uint16_t data)
{
	dataReg = data;
}
 static __inline void TFT_WriteCMD(uint16_t data) { //WR: rise, RD: H, RS(D/CX):L
	cmdReg = data;
}


 static __inline void TFT_WriteData(uint16_t data) {
	dataReg = data;
}

static __inline int16_t TFT_ReadData() { //
	unsigned short val = 0;
  val = dataReg;
	return val;
}


 static __inline int16_t TFT_ReadStatus() { //Implement later
	
}

