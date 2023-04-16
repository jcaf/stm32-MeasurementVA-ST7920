/*
 * ST7920.c
 *
 *  Created on: Apr 12, 2023
 *      Author: jcaf
 */

#include "main.h"
//#include <stdint.h>
#include "ST7920.h"
#include "delay/delaynop.h"

extern SPI_HandleTypeDef hspi1;

uint8_t startRow, startCol, endRow, endCol; // coordinates of the dirty rectangle
uint8_t numRows = 64;
uint8_t numCols = 128;
uint8_t Graphic_Check = 0;
uint8_t image[(128 * 64)/8];

void delay(uint32_t ms)
	{
	HAL_Delay(ms);

//	SysTick->LOAD=16000-1;
//	SysTick->VAL=0;
//	SysTick->CTRL=0x5;
//
//		for (int i=0;i<ms;i++)
//		{
//			while(!(SysTick->CTRL &0x10000)){}
//		}
//	SysTick->CTRL=0;

	}

void delayUs(uint32_t us)
	{
	HAL_Delay(1);

//	SysTick->LOAD=16-1;
//	SysTick->VAL=0;
//	SysTick->CTRL=0x5;
//
//		for (int i=0;i<us;i++)
//		{
//			while(!(SysTick->CTRL &0x10000)){}
//		}
//	SysTick->CTRL=0;

	}

//static
//void SendByteSPI(uint8_t byte)
//{
//	for(int i=0;i<8;i++)
//	{
//		if((byte<<i)&0x80)
//			{
//				SID_HIGH;  // SID=1  OR MOSI
//			}
//
//		else {SID_LOW;}  // SID=0
//
//		SCK_LOW;  // SCLK =0  OR SCK
//		SCK_HIGH;  // SCLK=1
//	}
//}
void SendByteSPI(uint8_t byte)
{
	HAL_SPI_Transmit(&hspi1, &byte, 1, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);


}
//static
void ST7920_SendCmd (uint8_t cmd)
{

	CS_HIGH;  // PUll the CS high

	//delayUs(50);
	delay_us(1);

	SendByteSPI(0xf8+(0<<1));  // send the SYNC + RS(0)

	SendByteSPI(cmd&0xf0);  // send the higher nibble first

	SendByteSPI((cmd<<4)&0xf0);  // send the lower nibble

	delay_us(1);

	CS_LOW;  // PUll the CS LOW

}

//static
void ST7920_SendData (uint8_t data)
{

	CS_HIGH;

	SendByteSPI(0xf8+(1<<1));  // send the SYNC + RS(1)
	SendByteSPI(data&0xf0);  // send the higher nibble first
	SendByteSPI((data<<4)&0xf0);  // send the lower nibble
	delayUs(50);
	CS_LOW;  // PUll the CS LOW
}


void ST7920_Init (void)
{

//	RCC->AHBENR|=RCC_AHBENR_GPIOAEN;
//	GPIOA->MODER|=(GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER4_0|GPIO_MODER_MODER8_0);
//	GPIOA->MODER&=~(GPIO_MODER_MODER0_1|GPIO_MODER_MODER1_1|GPIO_MODER_MODER4_1|GPIO_MODER_MODER8_1);
//	GPIOA->OSPEEDR|=GPIO_OSPEEDER_OSPEEDR0|GPIO_OSPEEDER_OSPEEDR1|GPIO_OSPEEDER_OSPEEDR4|GPIO_OSPEEDER_OSPEEDR8;

	RST_LOW; 					// RESET=0
	delay(10);   // wait for 10ms
	RST_HIGH;

	delay(50);   //wait for >40 ms


	ST7920_SendCmd(0x30);  // 8bit mode
	delayUs(110);  //  >100us delay

	ST7920_SendCmd(0x30);  // 8bit mode
	delayUs(40);  // >37us delay

	ST7920_SendCmd(0x08);  // D=0, C=0, B=0
	delayUs(110);  // >100us delay

	ST7920_SendCmd(0x01);  // clear screen
	delay(12);  // >10 ms delay


	ST7920_SendCmd(0x06);  // cursor increment right no shift
	delay(1);  // 1ms delay

	ST7920_SendCmd(0x0C);  // D=1, C=0, B=0
    delay(1);  // 1ms delay

	ST7920_SendCmd(0x02);  // return to home
	delay(1);  // 1ms delay

}

/*
 * Due to the design of the ST7920 controller (to accomodate Mandarin and Cyrillic), you must place the text on the column according to the numbers above the diagram below. The addressing is handle by the command.
 */
void ST7920_SendString(int row, int col, char* string)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0x90;
            break;
        case 2:
            col |= 0x88;
            break;
        case 3:
            col |= 0x98;
            break;
        default:
            col |= 0x80;
            break;
    }



    ST7920_SendCmd(col);

    while (*string)
    	{
    		ST7920_SendData(*string++);
    	}
}

void ST7920_GraphicMode (int enable)   // 1-enable, 0-disable
{
	if (enable == 1)
	{
		ST7920_SendCmd(0x30);  // 8 bit mode
		delay (1);
		ST7920_SendCmd(0x34);  // switch to Extended instructions
		delay (1);
		ST7920_SendCmd(0x36);  // enable graphics
		delay (1);
		Graphic_Check = 1;  // update the variable
	}

	else if (enable == 0)
	{
		ST7920_SendCmd(0x30);  // 8 bit mode
		delay (1);
		Graphic_Check = 0;  // update the variable
	}
}

void ST7920_DrawBitmap(const unsigned char* graphic)
{
	uint8_t x, y;
	for(y = 0; y < 64; y++)
	{
		if(y < 32)
		{
			for(x = 0; x < 8; x++)							// Draws top half of the screen.
			{												// In extended instruction mode, vertical and horizontal coordinates must be specified before sending data in.
				ST7920_SendCmd(0x80 | y);				// Vertical coordinate of the screen is specified first. (0-31)
				ST7920_SendCmd(0x80 | x);				// Then horizontal coordinate of the screen is specified. (0-8)
				ST7920_SendData(graphic[2*x + 16*y]);		// Data to the upper byte is sent to the coordinate.
				ST7920_SendData(graphic[2*x+1 + 16*y]);	// Data to the lower byte is sent to the coordinate.
			}
		}
		else
		{
			for(x = 0; x < 8; x++)							// Draws bottom half of the screen.
			{												// Actions performed as same as the upper half screen.
				ST7920_SendCmd(0x80 | (y-32));			// Vertical coordinate must be scaled back to 0-31 as it is dealing with another half of the screen.
				ST7920_SendCmd(0x88 | x);
				ST7920_SendData(graphic[2*x + 16*y]);
				ST7920_SendData(graphic[2*x+1 + 16*y]);
			}
		}

	}
}


// Update the display with the selected graphics
void ST7920_Update(void)
{
	ST7920_DrawBitmap(image);
}


void ST7920_Clear()
{
	if (Graphic_Check == 1)  // if the graphic mode is set
	{
		uint8_t x, y;
		for(y = 0; y < 64; y++)
		{
			if(y < 32)
			{
				ST7920_SendCmd(0x80 | y);
				ST7920_SendCmd(0x80);
			}
			else
			{
				ST7920_SendCmd(0x80 | (y-32));
				ST7920_SendCmd(0x88);
			}
			for(x = 0; x < 8; x++)
			{
				ST7920_SendData(0);
				ST7920_SendData(0);
			}
		}
	}

	else
	{
		ST7920_SendCmd(0x01);   // clear the display using command
		//delay(2); // delay >1.6 ms
	}
}

// set Pixel

void SetPixel(uint8_t x, uint8_t y)
{
  if (y < numRows && x < numCols)
  {
    uint8_t *p = image + ((y * (numCols/8)) + (x/8));
    *p |= 0x80u >> (x%8);

    *image = *p;

    // Change the dirty rectangle to account for a pixel being dirty (we assume it was changed)
    if (startRow > y) { startRow = y; }
    if (endRow <= y)  { endRow = y + 1; }
    if (startCol > x) { startCol = x; }
    if (endCol <= x)  { endCol = x + 1; }


  }

}

/* draw a line
 * start point (X0, Y0)
 * end point (X1, Y1)
 */
void DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  int dx = (x1 >= x0) ? x1 - x0 : x0 - x1;
  int dy = (y1 >= y0) ? y1 - y0 : y0 - y1;
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  for (;;)
  {
    SetPixel(x0, y0);
    if (x0 == x1 && y0 == y1) break;
    int e2 = err + err;
    if (e2 > -dy)
    {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx)
    {
      err += dx;
      y0 += sy;
    }
  }
}




/* Draw rectangle
 * start point (x,y)
 * w -> width
 * h -> height
 */
void DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	/* Check input parameters */
	if (
		x >= numCols ||
		y >= numRows
	) {
		/* Return error */
		return;
	}

	/* Check width and height */
	if ((x + w) >= numCols) {
		w = numCols - x;
	}
	if ((y + h) >= numRows) {
		h = numRows - y;
	}

	/* Draw 4 lines */
	DrawLine(x, y, x + w, y);         /* Top line */
	DrawLine(x, y + h, x + w, y + h); /* Bottom line */
	DrawLine(x, y, x, y + h);         /* Left line */
	DrawLine(x + w, y, x + w, y + h); /* Right line */
}




/* Draw filled rectangle
 * Start point (x,y)
 * w -> width
 * h -> height
 */
void DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	uint8_t i;

	/* Check input parameters */
	if (
		x >= numCols ||
		y >= numRows
	) {
		/* Return error */
		return;
	}

	/* Check width and height */
	if ((x + w) >= numCols) {
		w = numCols - x;
	}
	if ((y + h) >= numRows) {
		h = numRows - y;
	}

	/* Draw lines */
	for (i = 0; i <= h; i++) {
		/* Draw lines */
		DrawLine(x, y + i, x + w, y + i);
	}
}




/* draw circle
 * centre (x0,y0)
 * radius = radius
 */
void DrawCircle(uint8_t x0, uint8_t y0, uint8_t radius)
{
  int f = 1 - (int)radius;
  int ddF_x = 1;

  int ddF_y = -2 * (int)radius;
  int x = 0;

  SetPixel(x0, y0 + radius);
  SetPixel(x0, y0 - radius);
  SetPixel(x0 + radius, y0);
  SetPixel(x0 - radius, y0);

  int y = radius;
  while(x < y)
  {
    if(f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    SetPixel(x0 + x, y0 + y);
    SetPixel(x0 - x, y0 + y);
    SetPixel(x0 + x, y0 - y);
    SetPixel(x0 - x, y0 - y);
    SetPixel(x0 + y, y0 + x);
    SetPixel(x0 - y, y0 + x);
    SetPixel(x0 + y, y0 - x);
    SetPixel(x0 - y, y0 - x);
  }
}


// Draw Filled Circle

void DrawFilledCircle(int16_t x0, int16_t y0, int16_t r)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    SetPixel(x0, y0 + r);
    SetPixel(x0, y0 - r);
    SetPixel(x0 + r, y0);
    SetPixel(x0 - r, y0);
    DrawLine(x0 - r, y0, x0 + r, y0);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        DrawLine(x0 - x, y0 + y, x0 + x, y0 + y);
        DrawLine(x0 + x, y0 - y, x0 - x, y0 - y);

        DrawLine(x0 + y, y0 + x, x0 - y, y0 + x);
        DrawLine(x0 + y, y0 - x, x0 - y, y0 - x);
    }
}



// Draw Traingle with coordimates (x1, y1), (x2, y2), (x3, y3)
void DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3)
{
	/* Draw lines */
	DrawLine(x1, y1, x2, y2);
	DrawLine(x2, y2, x3, y3);
	DrawLine(x3, y3, x1, y1);
}



// Draw Filled Traingle with coordimates (x1, y1), (x2, y2), (x3, y3)
void DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3)
{
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
	curpixel = 0;

#define ABS(x)   ((x) > 0 ? (x) : -(x))

	deltax = ABS(x2 - x1);
	deltay = ABS(y2 - y1);
	x = x1;
	y = y1;

	if (x2 >= x1) {
		xinc1 = 1;
		xinc2 = 1;
	} else {
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) {
		yinc1 = 1;
		yinc2 = 1;
	} else {
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay){
		xinc1 = 0;
		yinc2 = 0;
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;
	} else {
		xinc2 = 0;
		yinc1 = 0;
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		DrawLine(x, y, x3, y3);

		num += numadd;
		if (num >= den) {
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
}

void ST7920_test(void)
{
	 ST7920_Init();
	  	delay(100);
	  	ST7920_SendString(0, 0, "CURRENT:123.45mA");
	  	ST7920_SendString(1, 0, "VOLT:1235.25mV");
	  	ST7920_SendString(2, 0, "SWITCHES:1 2 3 4");
	  	ST7920_SendString(3, 0, "RELAYS: 1 2 3");//1234567890!@#$%^

	  	while (1) ;
	  	delay(2000);
	  	ST7920_Clear();
	  	ST7920_GraphicMode(1);
	  	//ST7920_DrawBitmap(logo);
	  	delay(2000);
	  	ST7920_Clear();
	  	DrawCircle(110, 31, 12);

	  	DrawCircle(110, 31, 16);

	  	DrawLine(3, 60, 127, 33);

	  	ST7920_Update();

	  	delay(2000);

	  	DrawRectangle (100, 12, 20, 14);

	  	ST7920_Update();

	  	delay(2000);

	  	DrawFilledRectangle(30, 20, 30, 10);

	  	ST7920_Update();

	  	delay(2000);

	  	DrawFilledCircle(15, 30, 6);

	  	ST7920_Update();

	  	DrawFilledTriangle(1, 5, 10, 5, 6, 15);

	  	ST7920_Update();

	//  	delay(2000);
	//  	ST7920_Clear();
}
