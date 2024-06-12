/*
 * obd2.c
 *
 *  Created on: Jun 12, 2024
 *      Author: Admin
 */

// include
#include "CAN_SPI.h"
#include "obd2.h"
#include "main.h"

//

//
void obd2_SendFrame(uint16_t addr, uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6, uint8_t byte7)
{
	uCAN_MSG txMessage;
	txMessage.frame.idType = 0x00; // std id
	txMessage.frame.id = addr;
	txMessage.frame.dlc = 8;
	txMessage.frame.data0 = byte0;
	txMessage.frame.data1 = byte1;
	txMessage.frame.data2 = byte2;
	txMessage.frame.data3 = byte3;
	txMessage.frame.data4 = byte4;
	txMessage.frame.data5 = byte5;
	txMessage.frame.data6 = byte6;
	txMessage.frame.data7 = byte7;

	CANSPI_Transmit(&txMessage);

}
//
void obd2_Request()
{
	static uint8_t num = 0;
	obd2_SendFrame(CanID_request, 0x02, 0x01, params[num++], 0x55, 0x55, 0x55, 0x55, 0x55);
	num = (num == GET_SizeData(params)) ? 0 : num;
}
