#include "upload.h"
#include "main.h"
#include "stm32_adafruit_lcd.h"


uint8_t logo_n[13] = "bmp_logo.bin";
uint8_t t[17] = "bmp_pre_heat.bin";

unsigned char bmp_public_buf[32 * 1024];
//extern 
uint32_t logo_addroffset = 0;


uint32_t default_view_addroffset = 0;
void default_view_Read(uint8_t *default_view_Rbuff,uint32_t default_view_Readsize)
{
	W25qxx_ReadBytes(default_view_Rbuff,DEFAULT_VIEW_ADDR+default_view_addroffset,default_view_Readsize);
	default_view_addroffset += default_view_Readsize;
	if(default_view_addroffset >= DEFAULT_VIEW_MAX_SIZE)
	{
		default_view_addroffset = 0;
	}

}

uint32_t flash_view_addroffset = 0;
void flash_view_Read(uint8_t *flash_view_Rbuff,uint32_t flash_view_Readsize)
{
	W25qxx_ReadBytes(flash_view_Rbuff,BAK_VIEW_ADDR+flash_view_addroffset,flash_view_Readsize);
	flash_view_addroffset += flash_view_Readsize;
	if(flash_view_addroffset >= FLASH_VIEW_MAX_SIZE)
	{
		flash_view_addroffset = 0;
	}

}

void Pic_Logo_Read(uint8_t *LogoName,uint8_t *Logo_Rbuff,uint32_t LogoReadsize)
{
	int code = W25qxx_ReadBytes(Logo_Rbuff,PIC_LOGO_ADDR+logo_addroffset,LogoReadsize);
	logo_addroffset += LogoReadsize;
	if(logo_addroffset >= LOGO_MAX_SIZE)
	{
		logo_addroffset = 0;
	}
//printf("code %d\n\r",code);
}


void Pic_Read(uint8_t *Pname,uint8_t *P_Rbuff)
{
	uint8_t i, j;
	uint8_t Pic_cnt;
	uint32_t tmp_cnt = 0;
	PIC_MSG PIC;
	uint16_t *tmp_16bit_addr;
	uint8_t *tmp_8bit_addr;
    int DMA_ERRO_FLAG=0;
  //void W25qxx_ReadBytes(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
//void W25qxx_ReadBytes(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
	W25qxx_ReadBytes(&Pic_cnt,PIC_COUNTER_ADDR,1);
	if(Pic_cnt == 0xff)
	{
		Pic_cnt = 0;
	}
	//printf("pic count %d",Pic_cnt);
	for(i=0;i<Pic_cnt;i++)
	{
	
		j = 0;
		do
		{
			W25qxx_ReadBytes(&PIC.name[j],PIC_NAME_ADDR + tmp_cnt,1);
			tmp_cnt++;
		}while(PIC.name[j++] != '\0');

		W25qxx_ReadBytes(PIC.size.bytes,PIC_SIZE_ADDR+i*4,4);
		//printf("PIC.name %s",PIC.name);
		if((strcmp((char*)Pname,(char*)PIC.name))==0)
		{
			W25qxx_ReadBytes((uint8_t *)P_Rbuff,PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE,PIC.size.dwords);
			if(DMA_ERRO_FLAG)
			{
				DMA_ERRO_FLAG = 0;
				W25qxx_ReadBytes((uint8_t *)P_Rbuff,PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE,PIC.size.dwords);
			}
			break;
		}
	}
}

void test_pic()
{
    int index; 
	int x_off = 0, y_off = 0;
	int _x, _y;
	uint16_t *p_index;
	int i;
    Pic_Read(t,bmp_public_buf);

	for(index = 0; index < 120; index ++)
	{
		Pic_Logo_Read(logo_n, bmp_public_buf, 1280);

		
		i = 0;	
	
	//	LCD_setWindowArea(0, y_off * 2, 320, 2);
		//ili9320_SetCursor(0, y_off * 2);
	//	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */	
		for(_y = y_off * 2; _y < (y_off + 1) * 2; _y++)
		{
			for (x_off = 0; x_off < 320; x_off++) 
			{
				p_index = (uint16_t *)(&bmp_public_buf[i]);						
			//	LCD_WriteRAM(*p_index);
				i += 2;
				
			}
			if(i >= 1280)
					break;
		}
		y_off++;		

		
	}
	LCD_Window(0, 0, 319, 239);
}

void DRAW_LOGO()
{
	int index; 
	int x_off = 0, y_off = 0;
	int _x, _y;
	uint16_t *p_index;
	int i;
	printf("doing logo\r\n");

	for(index = 0; index < 20; index ++)//480*320
	{
		Pic_Logo_Read(logo_n, bmp_public_buf, 15360);//15k
		i = 0;
		//BSP_LCD_DrawRGB16Image(0,(16*index),480,16,*bmp_public_buf);
		//BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGB_Code);
		for (int one=0;one<16;one++)
		{
			for (int two=0;two<480;two++)
			{
				BSP_LCD_DrawPixel(two, one,(uint16_t) &bmp_public_buf[i]);
				i+=2;
			}
			if(i >= 15360)
					break;
		}
	//	LCD_setWindowArea(0, y_off * 16, 480,16);     //480*16
		//LCD_setWindowArea(0, y_off * 16+120, 800,48);      //800*240  
		//**ili9320_SetCursor(0, y_off * 16);
		//LCD_WriteRAM_Prepare();
     /*   for (x_off = 0; x_off < 480; x_off++) 
		//for(_y = y_off * 16; _y < (y_off + 1) * 16; _y++)
		{
			for(_y = y_off * 16; _y < (y_off + 1) * 16; _y++)
			// /for (x_off = 0; x_off < 480; x_off++) 
			{
				p_index = (uint16_t *)(&bmp_public_buf[i]); 					
			//	LCD_WriteRAM(*p_index);
			//BSP_LCD_DrawRGB16Image(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint16_t *pData);
			BSP_LCD_DrawPixel(x_off, _y, p_index);
			//BSP_LCD_DrawPixel(_y, x_off, &bmp_public_buf[i]);
				i += 2;

			}
            
			if(i >= 15360)
					break;
                     
		}
		y_off++;		
	*/
		
	}

//	LCD_setWindowArea(0, 0, 480, 320);
}


void Draw_default_preview(int xpos_pixel,int ypos_pixel,uint8_t sel)
{
	int index; 
	int x_off = 0, y_off = 0;
	int _x, _y;
	uint16_t *p_index;
	int i;
	uint16_t temp_p;
	
	for(index = 0; index < 4; index ++)//200*200
	{
		if(sel == 1)
		{
			flash_view_Read(bmp_public_buf, 20000);//20k
		}
		else
		{
			default_view_Read(bmp_public_buf, 20000);//20k
		}

		i = 0;
		
	//	LCD_setWindowArea(xpos_pixel, y_off * 50+ypos_pixel, 200,50);     //200*200

	//	LCD_WriteRAM_Prepare(); 
		for(_y = y_off * 50; _y < (y_off + 1) * 50; _y++)
		{
			for (x_off = 0; x_off < 200; x_off++) 
			{
				if(sel==1)
				{
					temp_p = (uint16_t)(bmp_public_buf[i]|bmp_public_buf[i+1]<<8);
					p_index = &temp_p;
				}
				else
				{
					p_index = (uint16_t *)(&bmp_public_buf[i]); 	
				}
			//	LCD_WriteRAM(*p_index);
				i += 2;
				
			}
			if(i >= 20000)
				break;
		}
		y_off++;		
	}

}
