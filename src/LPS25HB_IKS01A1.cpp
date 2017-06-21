/*
	A simple library for arduino to communicate with LPS25HB on the X-NUCLEO-IKS01A1 board.

	Author:zhixinzhao
	Email:techzzx@foxmail.com
*/

#include "LPS25HB_IKS01A1.h"
/*
	Constructor
*/
LPS25HB::LPS25HB(uint8_t i2cAddr)
{
	_i2cAddr = i2cAddr;
}

/*
	LPS25HB sensor check
*/
bool LPS25HB::deviceCheck()
{
	return (LPS25HB_WHO_AM_I_VALUE == i2cReadByte(LPS25HB_WHO_AM_I));
}

/*
	LPS25HB sensor power up
*/
bool LPS25HB::powerUp()
{
	uint8_t data = 0;
	data |= LPS25HB_PD;
	data |= LPS25HB_BDU;
	data |= LPS25HB_ODR_7HZ;
	return i2cWriteByte(LPS25HB_CTRL_REG1, data);
}

/*
	LPS25HB sensor set resolution
*/
bool LPS25HB::setResolution()
{
	uint8_t data = 0;
	data |= LPS25HB_AVGP_512;
	data |= LPS25HB_AVGT_64;
	return i2cWriteByte(LPS25HB_RES_CONF, data);
}

/*
	LPS25HB sensor init
*/
bool LPS25HB::begin()
{
	if(deviceCheck())
	{
		if(powerUp())
		{
			if(setResolution())
			{
				return true;
			}
		}
	}

	return false;
}

/*
	Return the value of pressure , unit : mbar
*/
const double LPS25HB::readPressure()
{
	double pressure = 0.0;
	int32_t pressOut = 0;
	uint8_t dataReady = 0;

	dataReady = i2cReadByte(LPS25HB_STATUS_REG);

	while(!(dataReady & LPS25HB_PRESS_READY))
		dataReady = i2cReadByte(LPS25HB_STATUS_REG); //loop until pressure data is ready

	pressOut  = i2cReadByte(LPS25HB_PRESS_OUT_XL);
	pressOut |= (int32_t)i2cReadByte(LPS25HB_PRESS_OUT_L) << 8;
	pressOut |= (int32_t)i2cReadByte(LPS25HB_PRESS_OUT_H) << 16;

	pressure = pressOut / 4096.0;

	return pressure;
}

/*
	Return the temperature , unit :  °C
*/
const double LPS25HB::readTemperature()
{
	double temperature = 0.0;
	int16_t Temp_Out;
	uint8_t dataReady;

	dataReady = i2cReadByte(LPS25HB_STATUS_REG);

	while(!(dataReady & LPS25HB_TEMP_READY))
		dataReady = i2cReadByte(LPS25HB_STATUS_REG); //loop until temperature data is ready

	Temp_Out = i2cReadByte(LPS25HB_TEMP_OUT_L);
	Temp_Out = i2cReadByte(LPS25HB_TEMP_OUT_H) << 8;

	temperature = 42.5 + Temp_Out / 480.0; //offset : 42.5

	return temperature;
}


/* -------------------------------------------------------------- */

/*
	Read a single byte from specific register in LPS25HB
*/
uint8_t LPS25HB::i2cReadByte(uint8_t registerAddr)
{
	Wire.beginTransmission(_i2cAddr);
	Wire.write(registerAddr);

	if(0 == Wire.endTransmission(false))
	{
		Wire.requestFrom(_i2cAddr, (uint8_t)1);
		//Attention:program might hung in there
		while(!Wire.available());	//Wait for data
		
		return Wire.read();
	}
}

/*
	Write a single byte to specific register in LPS25HB
*/
bool LPS25HB::i2cWriteByte(uint8_t registerAddr, uint8_t data)
{
	Wire.beginTransmission(_i2cAddr);
	Wire.write(registerAddr);
	Wire.write(data);

	return (0 == Wire.endTransmission());
}