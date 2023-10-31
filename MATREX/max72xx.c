/*
 * max72xx.c
 *
 *  Created on: Oct 30, 2023
 *      Author: OMAR
 */

#include "max72xx.h"

uint8_t DecodeMode=0xFF;
uint8_t Sympoles[]={
		0x6E,
		0x30,
		0x6D,
		0x79,
		0x33,
		0x6B,
		0x6F,
		0x70,
		0x7F,
		0x7B,
		0x01,
		0x00
};
void max7219_int(uint8_t intensivity,SPI_HandleTypeDef hspi){
	max7219_TurnON(hspi);
	max7219_SendData(Scan_Limit,number_reg-1,hspi);
	max7219_SetIntensivity(intensivity,hspi);
	max7219_Clear(hspi);
}

void max7219_SetIntensivity(uint8_t intensivity,SPI_HandleTypeDef hspi){
	if(intensivity>0x0F){
		return;
	}
	max7219_SendData(Intensity,intensivity,hspi);
}
void max7219_Clear(SPI_HandleTypeDef hspi){
	uint8_t clear =0x00;
	if(Decode_Mode==0xFF){
		clear=chaBLINK;

	}
	for (int var = 0; var < 8; ++var) {
		max7219_SendData(var+1,clear,hspi);
	}
}
void max7219_SendData(uint8_t addr,uint8_t Data,SPI_HandleTypeDef hspi){
	CSSET();
	HAL_SPI_Transmit(&hspi, &addr, 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(&hspi, &Data, 1, HAL_MAX_DELAY);
	CSRESET();
}
void max7219_TurnON(SPI_HandleTypeDef hspi){
	max7219_SendData(Shutdown, 0x01,hspi);
}
void max7219_TurnOff(SPI_HandleTypeDef hspi){
	max7219_SendData(Shutdown, 0x00,hspi);
}
void max7219_DecodeOn(SPI_HandleTypeDef hspi){
	DecodeMode=0xFF;
	max7219_SendData(Decode_Mode, DecodeMode,hspi);
}
void max7219_DecodeOff(SPI_HandleTypeDef hspi){
	DecodeMode=0x00;
	max7219_SendData(Decode_Mode, DecodeMode,hspi);
}
void max7219_PrintDigit(max7219_DIGIT position,max7219_char chr,bool point,SPI_HandleTypeDef hspi){
	if(position>number_reg){
		return;
	}
	if (point){
		if(DecodeMode==0x00){
			max7219_SendData(position,Sympoles[chr]|(1<<7),hspi);
		}
		if(DecodeMode==0xFF){
			max7219_SendData(position,chr|(1<<7),hspi);
		}

	}else{
		if(DecodeMode==0x00){
			max7219_SendData(position,Sympoles[chr],hspi);
		}
		if(DecodeMode==0xFF){
			max7219_SendData(position,chr,hspi);
		}
	}
}
max7219_DIGIT max7219_PrintITos(max7219_DIGIT position ,int  value,SPI_HandleTypeDef hspi){
	max7219_SendData(Decode_Mode, 0xFF,hspi);
	int32_t i=1;
	if(value<0){
		if(position>0){
			max7219_SendData(position,cha_MINUS,hspi);
			position--;
		}
		value=-value;
	}
	while((value/i)>9){
		i*=10;
	}
	if(position>0){
		max7219_SendData(position,value/i,hspi);
		position--;
	}
	i/=10;
	while(i>0){
		if(position>0){
			max7219_SendData(position,(value%(i*10))/i,hspi);
			position--;
		}
		i/=10;
	}
	max7219_SendData(Decode_Mode, DecodeMode,hspi);
	return position;
}
max7219_DIGIT max7219_PrintNotes(max7219_DIGIT position ,uint32_t value,uint8_t n);
max7219_DIGIT max7219_PrintFTos(max7219_DIGIT position ,float value,uint8_t n);
