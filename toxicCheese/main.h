/*
 * =====================================================================================
 *
 *       Filename:  main.h
 *
 *    Description:  header for main.h
 *
 *        Version:  1.0
 *        Created:  19/07/17 14:51:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Viktor Horsmanheimo
 *   Organization:  
 *
 * =====================================================================================
 */

enum addresses {

	WHO_AM_I = 0x0F,
	AV_CONF = 0x10,
	CTRL_REG1 = 0x20,
	CTRL_REG2 = 0x21,
	CTRL_REG3 = 0x22,
	STATUS_REG = 0x27,
	HUMIDITY_OUT_L = 0x28,
	HUMIDITY_OUT_H = 0x29, 
	TEMP_OUT_L = 0x2A,
	TEMP_OUT_H = 0x2B,
	H0_T0_OUT_L = 0x36,
	H0_T0_OUT_H = 0x37,
	H1_T0_OUT_L = 0x3A,
	H1_T0_OUT_H = 0x3B

};
