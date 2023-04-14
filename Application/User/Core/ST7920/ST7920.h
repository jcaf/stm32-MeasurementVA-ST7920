/*
 * ST7920.h
 *
 *  Created on: Apr 12, 2023
 *      Author: jcaf
 */

#ifndef SRC_ST7920_ST7920_H_
#define SRC_ST7920_ST7920_H_

//#define SCK_LOW 	(GPIOA->BSRR=GPIO_BSRR_BR_5)
//#define SCK_HIGH 	(GPIOA->BSRR=GPIO_BSRR_BS_5)
//
//#define SID_LOW 	(GPIOA->BSRR=GPIO_BSRR_BR_7)
//#define SID_HIGH 	(GPIOA->BSRR=GPIO_BSRR_BS_7)


#define CS_LOW 		(GPIOB->BSRR=GPIO_BSRR_BR_11)
#define CS_HIGH 	(GPIOB->BSRR=GPIO_BSRR_BS_11)


#define RST_LOW 	(GPIOA->BSRR=GPIO_BSRR_BR_2)
#define RST_HIGH 	(GPIOA->BSRR=GPIO_BSRR_BS_2)


void delay(uint32_t ms);
void delayUs(uint32_t us);
void SendByteSPI(uint8_t byte);
void ST7920_SendCmd (uint8_t cmd);
void ST7920_SendData (uint8_t data);
void ST7920_Init (void);
void ST7920_SendString(int row, int col, char* string);

void ST7920_GraphicMode (int enable);
void ST7920_DrawBitmap(const unsigned char* graphic);
void ST7920_Update(void);
void ST7920_Clear();
void SetPixel(uint8_t x, uint8_t y);
void DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void DrawCircle(uint8_t x0, uint8_t y0, uint8_t radius);
void DrawFilledCircle(int16_t x0, int16_t y0, int16_t r);
void DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3);
void DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3);

void ST7920_test(void);

#endif /* SRC_ST7920_ST7920_H_ */
