/*
 * max72xx.h
 *
 *  Created on: Oct 30, 2023
 *      Author: OMAR
 */

#ifndef MAX72XX_H_
#define MAX72XX_H_

#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "spi.h"
#include <stdbool.h>

#define spi_port				hspi1
#define number_reg				8

#define CSSET()					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,SET);
#define CSRESET()				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,RESET);
extern  SPI_HandleTypeDef 		spi_port;

typedef enum {
	No_Op			=0x00,
	Digit_0			=0x01,
	Digit_1			=0x02,
	Digit_2			=0x03,
	Digit_3			=0x04,
	Digit_4			=0x05,
	Digit_5			=0x06,
	Digit_6			=0x07,
	Digit_7			=0x08,
	Decode_Mode		=0x09,
	Intensity		=0x0A,
	Scan_Limit		=0x0B,
	Shutdown		=0x0C,
    Display_Test		=0x0F,
}max7219_Register;

typedef enum {
	DIGT_1			=1,
	DIGT_2			=2,
	DIGT_3			=3,
	DIGT_4			=4,
	DIGT_5			=5,
	DIGT_6			=6,
	DIGT_7			=7,
	DIGT_8			=8,
}max7219_DIGIT;

typedef enum {
	cha0			=0x00,
	cha1			=0x01,
	cha2			=0x02,
	cha3			=0x03,
	cha4			=0x04,
	cha5			=0x05,
	cha6			=0x06,
	cha7			=0x07,
	cha8			=0x08,
	cha9			=0x09,
	cha_MINUS		=0x0A,
	chaE			=0x0B,
	chaH			=0x0C,
	chaL			=0x0D,
	chaP			=0x0E,
	chaBLINK		=0x0F,
}max7219_char;


void max7219_int(uint8_t intensivity,SPI_HandleTypeDef hspi);
void max7219_SetIntensivity(uint8_t intensivity,SPI_HandleTypeDef hspi);
void max7219_Clear(SPI_HandleTypeDef hspi);
void max7219_SendData(uint8_t addr,uint8_t Data,SPI_HandleTypeDef hspi);
void max7219_TurnON(SPI_HandleTypeDef hspi);
void max7219_TurnOff(SPI_HandleTypeDef hspi);
void max7219_DecodeOn(SPI_HandleTypeDef hspi);
void max7219_DecodeOff(SPI_HandleTypeDef hspi);
void max7219_PrintDigit(max7219_DIGIT position,max7219_char chr,bool point,SPI_HandleTypeDef hspi);
max7219_DIGIT max7219_PrintITos(max7219_DIGIT position ,int  value,SPI_HandleTypeDef hspi);
max7219_DIGIT max7219_PrintNotes(max7219_DIGIT position ,uint32_t value,uint8_t n);
max7219_DIGIT max7219_PrintFTos(max7219_DIGIT position ,float value,uint8_t n);

#endif /* MAX72XX_H_ */
