/*
 *      Author: Lim Dale
 *
 *      The user need to map GPIO of SPI_CS and set GPIO level to HIGH
 *
 */

#include "MCP2515.h"
#include "main.h"

extern SPI_HandleTypeDef        hspi1;
#define SPI_CAN                 &hspi1
#define SPI_TIMEOUT             10
#define MCP2515_CS_HIGH()   HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET)
#define MCP2515_CS_LOW()    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET)

/* Prototypes */
static void SPI_Tx(uint8_t data);
static void SPI_TxBuffer(uint8_t *buffer, uint8_t length);
static uint8_t SPI_Rx(void);
static void SPI_RxBuffer(uint8_t *buffer, uint8_t length);

/*
 * Usage Functions
 * 1. Initialization Function
 * 2. Set the Modes Functions
 *
 */
/* Initialization CAN Function */
bool MCP2515_Initialize(void)
{
	MCP2515_CS_HIGH();
	uint8_t loop = 10;
	do
	{
		if (HAL_SPI_GetState(SPI_CAN) == HAL_SPI_STATE_READY)
			return true;
		loop--;
	} while (loop > 0);
	return false;
}
/* Configuration modes Function
 *
 * This function need to used Write Register and
 * then start Tx Address of CAN control register
 * with set to Configuration mode, and used Read
 * Register to check the Start Address of CAN and
 * MCP2515
 * */
bool MCP2515_SetConfigMode(void)
{
	// Write byte to CAN control register, and Configure Mode register
	MCP2515_WriteByte(MCP2515_CANCTRL, MCP2515_ConfigMode);
	// Check CAN register address&Start address of MCP2515 is set to Configuration mode or not
	uint8_t loop = 10;
	do
	{
		if ((MCP2515_ReadByte(MCP2515_CANSTAT) & CANSTAT_ADDR) == MCP2515_ConfigMode)
			return true;
		loop--;
	} while (loop > 0);
	return false;
}
/* Set Normal modes Function */
bool MCP2515_SetNormalMode(void)
{
	// Write byte to CAN control register, and Set to normal mode
	MCP2515_WriteByte(MCP2515_CANCTRL, MCP2515_NomalMode);
	// Check CAN register address&Start address of MCP2515 is set to normal mode or not
	uint8_t loop = 10;
	do
	{
		if ((MCP2515_ReadByte(MCP2515_CANSTAT) & CANSTAT_ADDR) == MCP2515_NomalMode)
			return true;
		loop--;
	} while (loop > 0);
	return false;
}
/* Set Sleep modes Function */
bool MCP2515_SetSleepMode(void)
{
	// Write byte to CAN control register, and Set to sleep mode
	MCP2515_WriteByte(MCP2515_CANCTRL, MCP2515_SleepMode);
	// Check CAN register address&Start address of MCP2515 is set to sleep mode or not
	uint8_t loop = 10;
	do
	{
		if ((MCP2515_ReadByte(MCP2515_CANSTAT) & CANSTAT_ADDR) == MCP2515_SleepMode)
			return true;
		loop--;
	} while (loop > 0);
	return false;
}
/* Reset Function */
void MCP2515_Reset(void)
{
	MCP2515_CS_LOW();
	SPI_Tx(MCP2515_RESET);
	MCP2515_CS_HIGH();
}
/* Read Byte Functions */
uint8_t MCP2515_ReadByte(uint8_t address)
{
	uint8_t retVal;
	MCP2515_CS_LOW();
	SPI_Tx(MCP2515_READ);
	SPI_Tx(address);
	retVal = SPI_Rx();
	MCP2515_CS_HIGH();
	return retVal;
}
/* Read Byte Sequence Functions */
void MCP2515_ReadRxSequence(uint8_t instruction, uint8_t *data, uint8_t length)
{
	MCP2515_CS_LOW();
	SPI_Tx(instruction);
	SPI_RxBuffer(data, length);
	MCP2515_CS_HIGH();
}
/* Write Byte Functions */
void MCP2515_WriteByte(uint8_t address, uint8_t data)
{
	MCP2515_CS_LOW();
	SPI_Tx(MCP2515_WRITE);
	SPI_Tx(address);
	SPI_Tx(data);
	MCP2515_CS_HIGH();
}
/* Write Byte Sequence Functions */
void MCP2515_WriteByteSequence(uint8_t startAddress, uint8_t endAddress, uint8_t *data)
{
	MCP2515_CS_LOW();
	SPI_Tx(MCP2515_WRITE);
	SPI_Tx(startAddress);
	SPI_TxBuffer(data, (endAddress - startAddress + 1));
	MCP2515_CS_HIGH();
}
/* Write to Buffer Functions */
void MCP2515_LoadTxSequence(uint8_t instruction, uint8_t *idReg, uint8_t dlc, uint8_t *data)
{
	MCP2515_CS_LOW();
	SPI_Tx(instruction);
	SPI_TxBuffer(idReg, 4);
	SPI_Tx(dlc);
	SPI_TxBuffer(data, dlc);
	MCP2515_CS_HIGH();
}
/* Write to butter 1 byte Functions */
void MCP2515_LoadTxBuffer(uint8_t instruction, uint8_t data)
{
	MCP2515_CS_LOW();
	SPI_Tx(instruction);
	SPI_Tx(data);
	MCP2515_CS_HIGH();
}
/* Request to Send Functions */
void MCP2515_RequestToSend(uint8_t instruction)
{
	MCP2515_CS_LOW();
	SPI_Tx(instruction);
	MCP2515_CS_HIGH();
}
/* Read Status Functions*/
uint8_t MCP2515_ReadStatus(void)
{
	uint8_t retVal;
	MCP2515_CS_LOW();
	SPI_Tx(MCP2515_READ_STATUS);
	retVal = SPI_Rx();
	MCP2515_CS_HIGH();
	return retVal;
}
/* Get status functions */
uint8_t MCP2515_GetRxStatus(void)
{
	uint8_t retVal;
	MCP2515_CS_LOW();
	SPI_Tx(MCP2515_RX_STATUS);
	retVal = SPI_Rx();
	MCP2515_CS_HIGH();
	return retVal;
}
/* Bit Modify Functions */
void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data)
{
	MCP2515_CS_LOW();
	SPI_Tx(MCP2515_BIT_MOD);
	SPI_Tx(address);
	SPI_Tx(mask);
	SPI_Tx(data);
	MCP2515_CS_HIGH();
}

static void SPI_Tx(uint8_t data)
{
	HAL_SPI_Transmit(SPI_CAN, &data, 1, SPI_TIMEOUT);
}

static void SPI_TxBuffer(uint8_t *buffer, uint8_t length)
{
	HAL_SPI_Transmit(SPI_CAN, buffer, length, SPI_TIMEOUT);
}

static uint8_t SPI_Rx(void)
{
	uint8_t retVal;
	HAL_SPI_Receive(SPI_CAN, &retVal, 1, SPI_TIMEOUT);
	return retVal;
}

static void SPI_RxBuffer(uint8_t *buffer, uint8_t length)
{
	HAL_SPI_Receive(SPI_CAN, buffer, length, SPI_TIMEOUT);
}


