/*
 * obd2.h
 *
 *  Created on: Jun 12, 2024
 *      Author: Dale Lim
 *
 *  In this driver used for testing OBD2 in service/mode 1,
 *  in this mode is show current data
 *  reference of pid:
 *  [1]: https://en.wikipedia.org/wiki/OBD-II_PIDs#Service_01
 *  [2]: https://www.csselectronics.com/pages/obd-ii-pid-examples
 *
 */

#ifndef INC_OBD2_H_
#define INC_OBD2_H_
// Includes
#include "main.h"
#include "CAN_SPI.h"
// determine size of data
#define GET_SizeData(arr) 	(sizeof(arr)/sizeof((arr)[0]))


// CAN Id Request and Reponse
// The "id" field is 7DF, which for OBD2 reflects a "request" message (while e.g. 7E8 reflects a "response" message)
#define CanID_request		0x7DF
#define CanID_reponse		0x7E8


// define the the PIDs for service/mode 1 of obd
#define pid_eng_load 		0x04 // calculate engine load
#define pid_eng_coolTemp 	0x05 // engine coolant temperature
#define pid_fuel_pressure 	0x0A // fuel pressure
#define pid_eng_speed 		0x0C // engine speed
#define pid_speed 			0x0D // vehicle speed
#define pid_eng_timeStart 	0x1F // run time since engine start
#define pid_fuel_level		0x2F // fuel Tank Level Input
#define pid_disTravel		0x30 // Distance traveled since codes cleared

static int16_t params[] =
{
		pid_eng_load,
		pid_eng_coolTemp,
		pid_fuel_pressure,
		pid_eng_speed,
		pid_speed,
		pid_eng_timeStart,
		pid_fuel_level,
		pid_disTravel
};

// CAN frame request
// |CAN request 0x7DF|Type show current data:0|Length:2|PID: |+3(0x55)|
// If you wish to query Engine RPM data in an OBD2 context, you'll need to set the "data" field to 02 01 0C 55 55 55 55 55.
void obd2_SendFrame(uint16_t addr, uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6, uint8_t byte7);
void obd2_Request();

#endif /* INC_OBD2_H_ */
