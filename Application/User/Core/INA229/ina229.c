/*
 * ina229.c
 *
 *  Created on: Apr 3, 2023
 *      Author: jcaf
 */
#include "main.h"
#include "ina229.h"

extern SPI_HandleTypeDef hspi1;


#define _NOP() __asm__ __volatile__("nop")

void delay_us(unsigned int val)
{
  unsigned int i;
/*
 * noinline
 * This function attribute prevents a function from being considered for inlining. If the function does not have side effects,
 * there are optimizations other than inlining that cause function calls to be optimized away, although the function call is live.
 * To keep such calls from being optimized away, put:
 */
  asm ("");

#define CPU_HZ 32000000
#if CPU_HZ == 80000000
  for(i=0; i<val; i++)
  {
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();

    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
  }
#elif CPU_HZ == 32000000
  for(i=0; i<val; i++)
  {
    _NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
  }
#elif CPU_HZ == 16384000
  for(i=0; i<val; i++)
  {
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
  }
#elif CPU_HZ == 16000000
  for(i=0; i<val; i++)
  {
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
  }
#elif CPU_HZ == 8192000
  for(i=0; i<val; i++)
  {
    _NOP();
    _NOP();
    _NOP();
    _NOP();
  }
#elif CPU_HZ == 8000000
  for(i=0; i<val; i++)
  {
    _NOP();
    _NOP();
    _NOP();
    _NOP();
  }
#else
#error "Invalid value for CPU_HZ!"
#endif
}
/*
void ina229_init(void)
{
	uint8_t SPI_buff[4];
	uint16_t ina229_reg;
	//

	SPI_buff[0] = (INA229_REG_CONFIG<<2) | INA229_SPI_WRITE;	//write
	ina229_reg = (IN229_CONFIG_ADCRANGE_163p84mV << INA229_CONFIG_BIT_ADCRANGE);
	SPI_buff[1] = ina229_reg >> 8;
	SPI_buff[2] = ina229_reg & 0xff;
	//
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	delay_us(1);
	HAL_SPI_Transmit(&hspi1, SPI_buff, 3, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	delay_us(1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	//

	//
	SPI_buff[0] = (INA229_REG_ADC_CONFIG<<2) | INA229_SPI_WRITE;	//write
//	ina229_reg = 	(INA229_ADC_CONFIGMODE_CONTINUOUS_SHUNT_ONLY << INA229_ADC_CONFIG_BIT_MODE) | \
//						 	(INA229_ADC_CONFIGMODE_CT_1052uS << INA229_ADC_CONFIG_BIT_VSHCT) | \
//							(INA229_ADC_CONFIGMODE_AVG_SAMPLE_512 << INA229_ADC_CONFIG_BIT_AVG);

	ina229_reg = 	(INA229_ADC_CONFIGMODE_CONTINUOUS_SHUNT_ONLY << INA229_ADC_CONFIG_BIT_MODE) | \
							 	(INA229_ADC_CONFIGMODE_CT_540uS << INA229_ADC_CONFIG_BIT_VSHCT) | \
								(INA229_ADC_CONFIGMODE_AVG_SAMPLE_1024 << INA229_ADC_CONFIG_BIT_AVG);

	SPI_buff[1] = ina229_reg >> 8;
	SPI_buff[2] = ina229_reg & 0xff;
	//
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	delay_us(1);
	HAL_SPI_Transmit(&hspi1, SPI_buff, 3, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	delay_us(1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	//

	SPI_buff[0] = (INA229_REG_SHUNT_CAL<<2) | INA229_SPI_WRITE;	//write
	SPI_buff[1] = (uint8_t)( ((uint16_t)INA229_SHUNT_CAL_ADCRANGE_163p84mV)>>8);
	SPI_buff[2] = (uint8_t) ( ((uint16_t)INA229_SHUNT_CAL_ADCRANGE_163p84mV) & 0x00FF);
	//
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	delay_us(1);
	HAL_SPI_Transmit(&hspi1, SPI_buff, 3, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	delay_us(1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	//
}
*/
void ina229_init(void)
{
	uint8_t SPI_buff[4];
	uint16_t ina229_reg;
	//

	SPI_buff[0] = (INA229_REG_CONFIG<<2) | INA229_SPI_WRITE;	//write
	ina229_reg = (IN229_CONFIG_ADCRANGE_40p96mV << INA229_CONFIG_BIT_ADCRANGE);
	SPI_buff[1] = ina229_reg >> 8;
	SPI_buff[2] = ina229_reg & 0xff;
	//
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	delay_us(1);
	HAL_SPI_Transmit(&hspi1, SPI_buff, 3, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	delay_us(1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	//

	//
	SPI_buff[0] = (INA229_REG_ADC_CONFIG<<2) | INA229_SPI_WRITE;	//write
//	ina229_reg = 	(INA229_ADC_CONFIGMODE_CONTINUOUS_SHUNT_ONLY << INA229_ADC_CONFIG_BIT_MODE) | \
//						 	(INA229_ADC_CONFIGMODE_CT_1052uS << INA229_ADC_CONFIG_BIT_VSHCT) | \
//							(INA229_ADC_CONFIGMODE_AVG_SAMPLE_512 << INA229_ADC_CONFIG_BIT_AVG);

	ina229_reg = 	(INA229_ADC_CONFIGMODE_CONTINUOUS_SHUNT_ONLY << INA229_ADC_CONFIG_BIT_MODE) | \
							 	(INA229_ADC_CONFIGMODE_CT_540uS << INA229_ADC_CONFIG_BIT_VSHCT) | \
								(INA229_ADC_CONFIGMODE_AVG_SAMPLE_1024 << INA229_ADC_CONFIG_BIT_AVG);

	SPI_buff[1] = ina229_reg >> 8;
	SPI_buff[2] = ina229_reg & 0xff;
	//
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	delay_us(1);
	HAL_SPI_Transmit(&hspi1, SPI_buff, 3, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	delay_us(1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	//

	SPI_buff[0] = (INA229_REG_SHUNT_CAL<<2) | INA229_SPI_WRITE;	//write
	SPI_buff[1] = (uint8_t)( ((uint16_t)INA229_SHUNT_CAL_ADCRANGE_40p96mV)>>8);
	SPI_buff[2] = (uint8_t) ( ((uint16_t)INA229_SHUNT_CAL_ADCRANGE_40p96mV) & 0x00FF);
	//
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	delay_us(1);
	HAL_SPI_Transmit(&hspi1, SPI_buff, 3, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	delay_us(1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	//
}

uint8_t SPI_buff_tx[4];
	volatile uint8_t SPI_buff_rx[4];

/*
int32_t INA229_read_current_register(void)
{
	uint8_t SPI_buff[4];

	SPI_buff[0] = (INA229_REG_CURRENT<<2) | INA229_SPI_READ;	//read
	//
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_SPI_Transmit(&hspi1, SPI_buff, 1, HAL_MAX_DELAY);
	//
	HAL_SPI_Receive(&hspi1, SPI_buff, 3, HAL_MAX_DELAY);
	HAL_Delay(1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	//
	int32_t current = ( (SPI_buff[0]<<16) | (SPI_buff[1]<<8) | (SPI_buff[2]) ) >> 4;
	return current;


	//----------
	HAL_SPI_TransmitReceive(&hspi1, SPI_buff, SPI_buff, size, Timeout);
}
*/
#define SIGNED20(x) (int32_t) (((x)^0x80000) - 0x80000)

int32_t INA229_read_current_register(void)
{

	SPI_buff_tx[0] = (INA229_REG_CURRENT<<2) | INA229_SPI_READ;	//read
	SPI_buff_tx[1] = 0;
	SPI_buff_tx[2] = 0;
	SPI_buff_tx[3] = 0;
	//
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	delay_us(1);
	HAL_SPI_TransmitReceive(&hspi1, SPI_buff_tx, SPI_buff_rx, 4, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	delay_us(1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	//
	uint64_t value = ( (SPI_buff_rx[1]<<16) | (SPI_buff_rx[2]<<8) | (SPI_buff_rx[3]) ) >> 4;


	//Convert for 2's compliment and signed value
//	if(value > 0x7FFFF)
//	{
//		data = (float)value - 0x100000;
//	}
//	else
//	{
//		data = (float)value;
//	}
	int32_t current = SIGNED20(value);

	return current;

}
