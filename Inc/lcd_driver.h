/* Screen dimension (width / height) */
//Screen Type lil9488
//#define SCR_WD  480
//#define SCR_HT  320

/* 3d field dimension (width / height) */
#define WD_3D   480
#define HT_3D   320

#define LCD_WD   480
#define LCD_HT   320

/* Statistic character size */
#define CHARSIZEX 8
#define CHARSIZEY 12

/* Frame Buffer lines */
#define NLINES   16

/* Double buffer (if DMA transfer used -> speed inc)
   - 0 Double buffer disabled
   - 1 Double buffer enabled */
#define DOUBLEBUF 1

/* Button pin assign */
#define BUTTON    B, 0    /* If not used leave it that way */
/* Button active level (0 or 1) */
#define BUTTON_ON    0
/* Button input mode (0 = pull none, 1 = pull up, 2 = pull down) */
#define BUTTON_PU    0
//clear screen right 

//Enable functions for ADA Fruit programs 
#define ADAFRUIT_MODE 