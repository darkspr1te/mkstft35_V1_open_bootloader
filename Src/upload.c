#include "upload.h"
#include "main.h"
#include "ff.h"
#include "fatfs.h"
#include "w25qxx.h"
uint8_t logo_n[13] = "bmp_logo.bin";
uint8_t t[17] = "bmp_about.bin";

unsigned char bmp_public_buf[32 * 1024];
unsigned char cmp_public_buf[32 * 1024];
//extern 
//sdcard stuff
extern char SDPath[4];
extern FATFS SDFatFS;
extern FIL SDFile;
//


uint32_t logo_addroffset = 0;
void Pic_Logo_Read(uint8_t *LogoName,uint8_t *Logo_Rbuff,uint32_t LogoReadsize)
{
	W25qxx_ReadBytes(Logo_Rbuff,PIC_LOGO_ADDR+logo_addroffset,LogoReadsize);
	logo_addroffset += LogoReadsize;
	if(logo_addroffset >= LOGO_MAX_SIZE)
	{
		logo_addroffset = 0;
	}

}

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

void Pic_Read(uint8_t *Pname,uint8_t *P_Rbuff)
{
	uint8_t i, j;
	uint8_t Pic_cnt;
	uint32_t tmp_cnt = 0;
	PIC_MSG PIC;
	uint16_t *tmp_16bit_addr;
	uint8_t *tmp_8bit_addr;
  //void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);

	W25qxx_ReadBytes(&Pic_cnt,PIC_COUNTER_ADDR,1);
	if(Pic_cnt == 0xff)
	{
		Pic_cnt = 0;
	}
	
	for(i=0;i<Pic_cnt;i++)
	{
		//读取图片名称
		j = 0;
		do
		{
			W25qxx_ReadBytes(&PIC.name[j],PIC_NAME_ADDR + tmp_cnt,1);
			tmp_cnt++;
		}while(PIC.name[j++] != '\0');
		//读取图片大小值
		W25qxx_ReadBytes(PIC.size.bytes,PIC_SIZE_ADDR+i*4,4);
		//printf("name %s\r\n",PIC.name);
		if((strcmp((char*)Pname,(char*)PIC.name))==0)
		{
			W25qxx_ReadBytes((uint8_t *)P_Rbuff,PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE,PIC.size.dwords);
		//	if(DMA_ERRO_FLAG)
		//	{
		//		DMA_ERRO_FLAG = 0;
		//		SPI_FLASH_BufferRead((uint8_t *)P_Rbuff,PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE,PIC.size.dwords);
		//	}
			break;
		}
	}
}

void Pic_Read_num(uint8_t num,uint8_t *P_Rbuff)
{
	uint8_t i, j;
	uint8_t Pic_cnt;
	uint32_t tmp_cnt = 0;
	PIC_MSG PIC;
	uint16_t *tmp_16bit_addr;
	uint8_t *tmp_8bit_addr;
  //void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);

	W25qxx_ReadBytes(&Pic_cnt,PIC_COUNTER_ADDR,1);
	if(Pic_cnt == 0xff)
	{
		Pic_cnt = 0;
	}
	
	for(i=0;i<Pic_cnt;i++)
	{
		//读取图片名称
		j = 0;
		do
		{
			W25qxx_ReadBytes(&PIC.name[j],PIC_NAME_ADDR + tmp_cnt,1);
			tmp_cnt++;
		}while(PIC.name[j++] != '\0');
		//读取图片大小值
		W25qxx_ReadBytes(PIC.size.bytes,PIC_SIZE_ADDR+i*4,4);
		
		if(num==i)
		{
			W25qxx_ReadBytes((uint8_t *)P_Rbuff,PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE,PIC.size.dwords);
			//printf("name %s\r\n",PIC.name);
		//	if(DMA_ERRO_FLAG)
		//	{
		//		DMA_ERRO_FLAG = 0;
		//		SPI_FLASH_BufferRead((uint8_t *)P_Rbuff,PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE,PIC.size.dwords);
		//	}
			break;
		}
	}
}
extern w25qxx_t	w25qxx;
void spi_flash_dump(void)
{
	int count=0;

	for (count=0;count<(w25qxx.CapacityInKiloByte*1024);)
		{
			W25qxx_ReadBytes(bmp_public_buf,count,sizeof(bmp_public_buf));
			for (int prn=0;prn<sizeof(bmp_public_buf);prn++)
				{printf(bmp_public_buf);}
			count += sizeof(bmp_public_buf);
			if (count>(w25qxx.CapacityInKiloByte*1024))
			{break;}
		}
}
void test_pic()
{
    int index; 
	int x_off = 0, y_off = 0;
	int _x, _y;
	uint16_t *p_index;
	int i;
    //Pic_Read(t,bmp_public_buf);
	for (int pic_index=0;pic_index<120;pic_index++)
	{
	printf("new pic read     ");
	Pic_Read_num(pic_index,bmp_public_buf);
	y_off=0;
	x_off=0;
	for(index = 0; index < 120; index ++)
	{
	//	Pic_Logo_Read("bmp_about.bin", bmp_public_buf, 1280);

		
		i = 0;	

		LCD_setWindowArea(0, y_off * 2, 320, 2);
		//ili9320_SetCursor(0, y_off * 2);
		//LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */	
		for(_y = y_off * 2; _y < (y_off + 1) * 2; _y++)
		{
			for (x_off = 0; x_off < 320; x_off++) 
			{
				p_index = (uint16_t *)(&bmp_public_buf[i]);	
				//p_index=0xfff;					
				LCD_WriteRAM(*p_index);
				i += 2;
				
			}
			if(i >= 1280)
					break;
		}
		y_off++;		

		
	}
	LCD_Window(0, 0, 319, 239);
}
}


void DRAW_LOGO()
{
	int index; 
	int x_off = 0, y_off = 0;
	int _x, _y;
	uint16_t *p_index;
	int i;
	int read_size = 15360;
	int bloat = 1;
	logo_addroffset=0;
	#if 1
	for(index = 0; index < 20; index ++)//480*320
	{
		Pic_Logo_Read(logo_n, bmp_public_buf, 15360);//15k
		i = 0;
		LCD_setWindowArea(0, y_off * 16, 480,16);     //480*16
		//LCD_setWindowArea(0, y_off * 16+120, 800,48);      //800*240  
		//**ili9320_SetCursor(0, y_off * 16);
		//LCD_WriteRAM_Prepare(); 
		
		for(_y = y_off * 16; _y < (y_off + 1) * 16; _y++)
		{
			for (x_off = 0; x_off < 480; x_off++) 
			{
				#if 1
				p_index = (uint16_t *)(&bmp_public_buf[i]); 					
				LCD_WriteRAM(*p_index);
				#else
				LCD_WriteRAM((uint16_t *)&bmp_public_buf[i]);
				#endif
				i += 2;
				
			}
			if(i >= 15360)
					break;
		}
		y_off++;		

		
	}
	LCD_setWindowArea(0, 0, 480, 320);
	#else
	for(index = 0; index < (20/bloat); index ++)//480*320
		{
		//Pic_Logo_Read(logo_n, bmp_public_buf,15360);//15k
		
		 W25qxx_ReadBytes(bmp_public_buf,PIC_LOGO_ADDR+logo_addroffset,(read_size*bloat));
		logo_addroffset += (read_size*bloat);
	

		i = 0;
		LCD_setWindowArea(0, y_off * (16*bloat), 480,(15*bloat)+1);     //480*16
      
		for(_y = y_off * (16*bloat); _y < (y_off + 1) * (16*bloat); _y++)
		{
			for (x_off = 0; x_off < 480; x_off++) 
			{
				p_index = (uint16_t *)(&bmp_public_buf[i]); 					
				LCD_WriteRAM(*p_index);
				i += 2;
				

			}
        
			if(i >= (read_size*bloat))
					break;
                     
		}
		y_off++;	
	if(logo_addroffset >= LOGO_MAX_SIZE)
		{break;}
	}
	LCD_setWindowArea(0, 0, 480, 320);
	#endif
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
		
		LCD_setWindowArea(xpos_pixel, y_off * 50+ypos_pixel, 200,50);     //200*200

		LCD_WriteRAM_Prepare(); 
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
				LCD_WriteRAM(*p_index);
				i += 2;
				
			}
			if(i >= 20000)
				break;
		}
		y_off++;		
	}

}

//sdcard preview stuff

int ascii2dec_test(char *ascii)
{
	int result = 0;

	if(ascii == 0)
		return 0;

	if(*(ascii) >= '0' && *(ascii) <= '9')
		result = *(ascii) - '0';
	else if(*(ascii) >= 'a' && *(ascii) <= 'f')
		result = *(ascii) - 'a' + 0x0a;
	else if(*(ascii) >= 'A' && *(ascii) <= 'F')
		result = *(ascii) - 'A' + 0x0a;
	else
		return 0;
		

	return result;
}

/*

typedef enum {
	FR_OK = 0,				// (0) Succeeded 
	FR_DISK_ERR,			// (1) A hard error occurred in the low level disk I/O layer 
	FR_INT_ERR,				// (2) Assertion failed 
	FR_NOT_READY,			// (3) The physical drive cannot work 
	FR_NO_FILE,				// (4) Could not find the file 
	FR_NO_PATH,				// (5) Could not find the path 
	FR_INVALID_NAME,		// (6) The path name format is invalid 
	FR_DENIED,				// (7) Access denied due to prohibited access or directory full 
	FR_EXIST,				// (8) Access denied due to prohibited access 
	FR_INVALID_OBJECT,		// (9) The file/directory object is invalid 
	FR_WRITE_PROTECTED,		// (10) The physical drive is write protected 
	FR_INVALID_DRIVE,		// (11) The logical drive number is invalid 
	FR_NOT_ENABLED,			// (12) The volume has no work area 
	FR_NO_FILESYSTEM,		// (13) There is no valid FAT volume 
	FR_MKFS_ABORTED,		// (14) The f_mkfs() aborted due to any problem 
	FR_TIMEOUT,				// (15) Could not get a grant to access the volume within defined period 
	FR_LOCKED,				// (16) The operation is rejected according to the file sharing policy 
	FR_NOT_ENOUGH_CORE,		// (17) LFN working buffer could not be allocated 
	FR_TOO_MANY_OPEN_FILES,	// (18) Number of open files > _FS_LOCK 
	FR_INVALID_PARAMETER	// (19) Given parameter is invalid 
} FRESULT;

*/

void pic_disp()
{
	int addy = BUTTON_CMD1_ADDR;
	W25qxx_ReadBytes(&bmp_public_buf,BUTTON_FUNCTION1_ADDR,201);

}
static FILINFO File_info;

uint8_t drawicon_preview(char *path,int xsize_small,int ysize_small,int xsize_big,int ysize_big,char sel)
{

	uint16_t *p_index;
	int i=0;
	char re;
	UINT read;
	char temp_test[8];
	int row_1=0;
	path="0:/mks_pic/bmp_tool.bin";
#if 0
	FRESULT res = f_stat(path, &File_info);
  	printf("fname is  %s result %d\r\n",fname,res);
   	if (res != FR_OK)
		{
			printf("file not found");
			return FLASH_FILE_NOT_EXISTS;
		}
	
#endif
	re = f_mount(&SDFatFS, SDPath, 1);
	printf("mount stats  %d    ",re);
	re = f_stat(path, &File_info);
    printf("fname is  %s result %d\r\n",path,re);
    printf("file      %s  ",path);
	

	re = f_open(&SDFile,path, FA_OPEN_EXISTING | FA_READ);//huaping.gcode
	printf("file stats  %d\r\n",re);
	if(re == FR_OK)
	{
		printf("memset\r\n");
        memset(bmp_public_buf,0,sizeof(bmp_public_buf));
		if(sel == 1)//big pic
		{
			f_lseek(&SDFile,xsize_small*ysize_small+8*(ysize_small+1));
		}
		f_read(&SDFile,&bmp_public_buf,8,&read);
		if((bmp_public_buf[0] ==';')&&(bmp_public_buf[1] =='s')
			&&(bmp_public_buf[2] =='i')&&(bmp_public_buf[3] =='m')
			&&(bmp_public_buf[4] =='a')&&(bmp_public_buf[5] =='g')
			&&(bmp_public_buf[6] =='e')&&(bmp_public_buf[7] ==':'))
		{
			while(1)
			{
				f_read(&SDFile,&temp_test,2,&read);
				if(sel == 1)//big pic
				{
						bmp_public_buf[row_1*(xsize_big*4)+i/2] = (char)(ascii2dec_test(&temp_test[0])<<4|ascii2dec_test(&temp_test[1]));				
				}
				else
	            {
	              		bmp_public_buf[row_1*(xsize_small*2)+i/2] = (char)(ascii2dec_test(&temp_test[0])<<4|ascii2dec_test(&temp_test[1]));
	            }
				i=i+2;
				if(sel == 1)//big pic
				{
					if(i>=(xsize_big*4))
					{
		                i=0;
		                row_1++;
		                f_read(&SDFile,&temp_test,9,&read);					
					}
					if(row_1>ysize_big)
						break;					
				}
				else
				{
					if(i>=(xsize_small*4))
					{
		                i=0;
		                row_1++;
		                f_read(&SDFile,&temp_test,9,&read);					
					}
					if(row_1>ysize_small)
						break;
				}

			}
			f_close(&SDFile);
			return 1;
		}
	}
	f_close(&SDFile);
	return 0;

}