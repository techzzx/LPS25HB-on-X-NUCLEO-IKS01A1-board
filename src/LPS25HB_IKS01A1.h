/*
	A simple library for arduino to communicate with LPS25HB on the X-NUCLEO-IKS01A1 board.

	Author:zhixinzhao
	Email:techzzx@foxmail.com
*/

#ifndef LPS25HB_IKS01A1_H
#define LPS25HB_IKS01A1_H

#include <arduino.h>
#include <Wire.h>

#define LPS25HB_I2CAddr	0b1011101	//LPS25HB i2c slave address 0x5D

/*
	Register mapping
*/
#define LPS25HB_REF_P_XL 		0x08 	//Reference pressure LSB part
#define LPS25HB_REF_P_L  		0x09 	//Reference pressure middle part
#define LPS25HB_REF_P_H  		0x0A 	//Reference pressure MSB part
#define LPS25HB_WHO_AM_I 		0x0F 	//Device who am I register
#define LPS25HB_RES_CONF 		0x10 	//Pressure and Temperature resolution 
#define LPS25HB_CTRL_REG1		0x20 	//Control register 1
#define LPS25HB_CTRL_REG2		0x21 	//Control register 2
#define LPS25HB_CTRL_REG3		0x22 	//Control register 3
#define LPS25HB_CTRL_REG4		0x23 	//Control register 4
#define LPS25HB_INTERRUPT_CFG	0x24 	//Interrupt configuration
#define LPS25HB_INT_SOURCE		0x25 	//Interrupt source , is cleared by reading it
#define LPS25HB_STATUS_REG		0x27 	//Status register , update every ODR cycle , regardless of BDU
#define LPS25HB_PRESS_OUT_XL	0x28 	//Pressure output value LSB part
#define LPS25HB_PRESS_OUT_L 	0x29 	//Pressure output value middle part
#define LPS25HB_PRESS_OUT_H		0x2A 	//Pressure output value MSB part
#define LPS25HB_TEMP_OUT_L		0x2B 	//Temperature output value LSB part
#define LPS25HB_TEMP_OUT_H		0x2C 	//Temperature output value MSB part
#define LPS25HB_FIFO_CTRL		0x2E 	//FIFO control
#define LPS25HB_FIFO_STATUS		0x2F 	//FIFO status
#define LPS25HB_THS_P_L			0x30 	//Pressure threshold LSB part
#define LPS25HB_THS_P_H			0x31 	//Pressure threshold MSB part
#define LPS25HB_RPDS_L			0x39 	//Pressure offset LSB part
#define LPS25HB_RPDS_H			0x3A 	//Pressure offset MSB part

#define LPS25HB_WHO_AM_I_VALUE  0xBD 	//Indicate the LPS25HB sensor

/*
	Resolution config
*/

/* Temperature resolution */
#define LPS25HB_AVGT_8		0b00
#define LPS25HB_AVGT_16 	0b01
#define LPS25HB_AVGT_32 	0b10
#define LPS25HB_AVGT_64 	0b11 		// default 

/* Pressure resolution */
#define LPS25HB_AVGP_8 		0b0000
#define LPS25HB_AVGP_16		0b0100
#define LPS25HB_AVGP_128	0b1000
#define LPS25HB_AVGP_512	0b1100 		// default 

/*
	CTRL_REG1 config
*/
#define LPS25HB_PD			0b10000000	//power control
#define LPS25HB_BDU			0b100 		//block data update control
#define LPS25HB_ODR_ONE		0b0000000 	//Output Data Rate : one-shot
#define LPS25HB_ODR_1HZ 	0b0010000 	//Output Data Rate : 1 HZ
#define LPS25HB_ODR_7HZ		0b0100000 	//Output Data Rate : 7 HZ
#define LPS25HB_ODR_12_5HZ	0b0110000 	//Output Data Rate : 12.5 HZ
#define LPS25HB_ODR_25HZ 	0b1000000 	//Output Data Rate : 25 HZ

/*
	CTRL_REG2 config
*/
#define LPS25HB_BOOT		0b10000000	//Reboot memeory content , the bit is self-cleared when the Boot is complete
#define LPS25HB_FIFO_EN		0b1000000 	//FIFO enable
#define LPS25HB_SWRESET 	0b100 		//Software Reset , the bit is self-cleared when the reset is completed
#define LPS25HB_ONE_SHOT	0b1 		//One-shot mode enable

/*
	CTRL_REG3 config - Interrupt control
*/
#define LPS25HB_INT_H_L 	0b10000000	//Interupt active low
#define	LPS25HB_DATA_SIGNAL 0b00 		//Data-ready signal Interrupt
#define LPS25HB_PRESS_HIGH	0b01 		//Output pressure higher than press threshold
#define LPS25HB_PRESS_LOW	0b10        //Output pressure lower than press threshold
#define LPS25HB_HIGH_lOW	0b11 		//Output pressure Higher or lower than press threshold

/*
	CTRL_REG4 config - Interrupt configuration
*/
#define LPS25HB_F_EMPTY 	0b1000 		//Enable FIFO empty flag on INT_DRDY pin
#define LPS25HB_F_FTH 		0b0100 		//Enable FIFO threshold status on INT_DRDY pin
#define LPS25HB_F_OVR 		0b0010 		//Enable FIFO overrun Interrupt on INT_DRDY pin
#define LPS25HB_DRDY		0b0001 		//Enable Data-ready signal on INT_DRDY pin

/*
	Interrupt config
*/
#define LPS25HB_LIR			0b100 		//Interrupt request latched
#define LPS25HB_PL_E 		0b010 		//Enable interrupt request when pressure value lower than threshold
#define LPS25HB_PH_E 		0b001 		//Enable interrupt request when pressure value higher than threshold

/*
	Status register
*/
#define LPS25HB_PRESS_READY	0b10 
#define LPS25HB_TEMP_READY	0b01

class LPS25HB
{
public:
	LPS25HB(uint8_t i2cAddr = LPS25HB_I2CAddr);
	bool deviceCheck(void);
	bool powerUp(void);
	bool setResolution(void);
	bool begin(void);

	const double readPressure(void);
	const double readTemperature(void);

private:
	uint8_t _i2cAddr;
	uint8_t i2cReadByte(uint8_t register);
	bool i2cWriteByte(uint8_t register, uint8_t data);
};

#endif	//#ifndef LPS25HB_IKS01A1_H