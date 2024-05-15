/*
 *      Author: Lim Dale
 *
 *      The user need to map GPIO of SPI_CS and set GPIO level to HIGH
 *
 */

#ifndef __MCP2515_H
#define	__MCP2515_H


#include "stm32l1xx_hal.h"
#include "stdbool.h"
/* MCP2515 SPI Instruction Set */
// Reset Instruction
#define MCP2515_RESET           0xC0 // 1100 0000, Resets internal registers to the default state, sets Configuration mode.
// Read Instruction
#define MCP2515_READ            0x03 // 0000 0011, Reads data from the register beginning at selected address.
// Read Rx Buffer Instruction "10010nm0"
#define MCP2515_READ_RXB0SIDH   0x90 // 10010000, n = 0, m = 0
#define MCP2515_READ_RXB0D0     0x92 // 10010010, n = 0, m = 1
#define MCP2515_READ_RXB1SIDH   0x94 // 10010100, n = 1, m = 0
#define MCP2515_READ_RXB1D0     0x96 // 10010110, n = 1, m = 1
// Write Instruction
#define MCP2515_WRITE           0x02 // 0000 0010, Writes data to the register beginning at the selected address.
// LOAD TX BUFFER Instruction "0100 0abc"
#define MCP2515_LOAD_TXB0SIDH   0x40    /* TX0 ID location, 0100 0000: a = 0, b = 0, c = 0*/
#define MCP2515_LOAD_TXB0D0     0x41    /* TX0 Data location, 0100 0001: a = 0, b = 0, c = 1 */
#define MCP2515_LOAD_TXB1SIDH   0x42    /* TX1 ID location, 0100 0010: a = 0, b = 1, c = 0 */
#define MCP2515_LOAD_TXB1D0     0x43    /* TX1 Data location, 0100 0011: a = 0, b = 1, c = 1 */
#define MCP2515_LOAD_TXB2SIDH   0x44    /* TX2 ID location, 0100 0100: a = 1, b = 0, c = 0 */
#define MCP2515_LOAD_TXB2D0     0x45    /* TX2 Data location, 0100 0101: a = 0, b = 0, c = 0 */
// Request-to-Send (RTS) Instruction "1000 0nnn"
#define MCP2515_RTS_TX0         0x81 // Request-to-Send for TXBO
#define MCP2515_RTS_TX1         0x82 // Request-to-Send for TXB1
#define MCP2515_RTS_TX2         0x84 // Request-to-Send for TXB2
#define MCP2515_RTS_ALL         0x87
// READ STATUS Instruction
#define MCP2515_READ_STATUS     0xA0 // Quick polling command that reads several status bits for transmit and receive functions
// RX STATUS Instruction
#define MCP2515_RX_STATUS       0xB0 // Quick polling command that indicates filter match and message type (standard, extended and/or remote) of received message.
// BIT MODIFY Instruction
#define MCP2515_BIT_MOD         0x05 // Allows the user to set or clear individual bits in a particular register.

/* Mode of Operations */
#define MCP2515_ConfigMode 		0x80 // Set Configuration mode
#define MCP2515_NomalMode 		0x00 // Set Normal Mode
#define MCP2515_SleepMode		0x20 // Set Sleep mode
#define MCP2515_LoopBackMode	0x40 // Set Loop Back mode
#define MCP2515_ListenMode		0x60 // Set Listen-Only mode
/* CAN REGISTER Address */
#define CANSTAT_ADDR			0xE0 //  CAN STATUS REGISTER (ADDRESS: XEh)
/* MCP251 CAN CONTROLLER REGISTER MAP */
// CAN control register row 1
#define MCP2515_RXF0SIDH	0x00 // 0000 0000
#define MCP2515_RXF0SIDL	0x01 // 0000 0001
#define MCP2515_RXF0EID8	0x02 // 0000 0010
#define MCP2515_RXF0EID0	0x03 // 0000 0011
#define MCP2515_RXF1SIDH	0x04 // 0000 0100
#define MCP2515_RXF1SIDL	0x05 // 0000 0101
#define MCP2515_RXF1EID8	0x06 // 0000 0110
#define MCP2515_RXF1EID0	0x07 // 0000 0111
#define MCP2515_RXF2SIDH	0x08 // 0000 1000
#define MCP2515_RXF2SIDL	0x09 // 0000 1001
#define MCP2515_RXF2EID8	0x0A // 0000 1010
#define MCP2515_RXF2EID0	0x0B // 0000 1011
#define MCP2515_CANSTAT		0x0E // 0000 1110
#define MCP2515_CANCTRL		0x0F // 0000 1111
// CAN control register row 2
#define MCP2515_RXF3SIDH	0x10 // 0001 0000
#define MCP2515_RXF3SIDL	0x11 // 0001 0001
#define MCP2515_RXF3EID8	0x12 // 0001 0010
#define MCP2515_RXF3EID0	0x13 // 0001 0011
#define MCP2515_RXF4SIDH	0x14 // 0001 0100
#define MCP2515_RXF4SIDL	0x15 // 0001 0101
#define MCP2515_RXF4EID8	0x16 // 0001 0110
#define MCP2515_RXF4EID0	0x17 // 0001 0111
#define MCP2515_RXF5SIDH	0x18 // 0001 1000
#define MCP2515_RXF5SIDL	0x19 // 0001 1001
#define MCP2515_RXF5EID8	0x1A // 0001 1010
#define MCP2515_RXF5EID0	0x1B // 0001 1011
#define MCP2515_TEC			0x1C // 0001 1100
#define MCP2515_REC			0x1D // 0001 1101
// CAN control register row 3
#define MCP2515_RXM0SIDH	0x20 // 0010 0000
#define MCP2515_RXM0SIDL	0x21 // 0010 0001
#define MCP2515_RXM0EID8	0x22 // 0010 0010
#define MCP2515_RXM0EID0	0x23 // 0010 0011
#define MCP2515_RXM1SIDH	0x24 // 0010 0100
#define MCP2515_RXM1SIDL	0x25 // 0010 0101
#define MCP2515_RXM1EID8	0x26 // 0010 0110
#define MCP2515_RXM1EID0	0x27 // 0010 0111
#define MCP2515_CNF3		0x28 // 0010 1000
#define MCP2515_CNF2		0x29 // 0010 1001
#define MCP2515_CNF1		0x2A // 0010 1010
#define MCP2515_CANINTE		0x2B // 0010 1011
#define MCP2515_CANINTF		0x2C // 0010 1100
#define MCP2515_EFLG		0x2D // 0010 1101
// CAN control register row 4
#define MCP2515_TXB0CTRL	0x30 // 0011 0000
#define MCP2515_TXB1CTRL	0x40 // 0100 0000
#define MCP2515_TXB2CTRL	0x50 // 0101 0000
#define MCP2515_RXB0CTRL	0x60 // 0110 0000
#define MCP2515_RXB0SIDH	0x61 // 0110 0001
#define MCP2515_RXB1CTRL	0x70 // 0111 0000
#define MCP2515_RXB1SIDH	0x71 // 0111 0001

/* Defines for Rx Status */
#define MSG_IN_RXB0             0x01 // status receive message from B0
#define MSG_IN_RXB1             0x02 // status receive message from B1
#define MSG_IN_BOTH_BUFFERS     0x03 // status receive message from B0&B1

typedef union
{
	struct
	{
		unsigned RX0IF :1; // Receive Buffer 0 Full Interrupt Flag bit
		unsigned RX1IF :1; // Receive Buffer 1 Full Interrupt Flag bit
		unsigned TXB0REQ :1; // Request message of TXB0
		unsigned TX0IF :1; // Transmit Buffer 0 Full Interrupt Flag bit
		unsigned TXB1REQ :1; // Request message of TXB1
		unsigned TX1IF :1; // Transmit Buffer 1 Full Interrupt Flag bit
		unsigned TXB2REQ :1; // Request message of  TXB2
		unsigned TX2IF :1; // Transmit Buffer 2 Full Interrupt Flag bit
	};
	uint8_t ctrl_status;
} ctrl_status_t;

typedef union
{
	struct
	{
		unsigned filter :3;
		unsigned msgType :2;
		unsigned unusedBit :1;
		unsigned rxBuffer :2;
	};
	uint8_t ctrl_rx_status;
} ctrl_rx_status_t;

typedef union
{
	struct
	{
		unsigned EWARN :1; // Error Warning Flag bit
		unsigned RXWAR :1; // Receive Error Warning Flag bit
		unsigned TXWAR :1; // Transmit Error Warning Flag bit
		unsigned RXEP :1; // Receive Error-Passive Flag bit
		unsigned TXEP :1; // Transmit Error-Passive Flag bit
		unsigned TXBO :1; // Bus-Off Error Flag bit
		unsigned RX0OVR :1; // Receive Buffer 0 Overflow Flag bit
		unsigned RX1OVR :1; // Receive Buffer 1 Overflow Flag bit
	};
	uint8_t error_flag_reg;
} ctrl_error_status_t;

typedef union
{
	struct
	{
		uint8_t RXBnSIDH; // RECEIVE BUFFER n STANDARD IDENTIFIER REGISTER HIGH
		uint8_t RXBnSIDL; // RECEIVE BUFFER n STANDARD IDENTIFIER REGISTER LOW
		uint8_t RXBnEID8; // RECEIVE BUFFER n EXTENDED IDENTIFIER REGISTER HIGH
		uint8_t RXBnEID0; // RECEIVE BUFFER n EXTENDED IDENTIFIER REGISTER LOW
		uint8_t RXBnDLC; // RECEIVE BUFFER n DATA LENGTH CODE REGISTER
		uint8_t RXBnD0; // RECEIVE BUFFER n DATA BYTE 0 REGISTER
		uint8_t RXBnD1; // RECEIVE BUFFER n DATA BYTE 1 REGISTER
		uint8_t RXBnD2; // RECEIVE BUFFER n DATA BYTE 2 REGISTER
		uint8_t RXBnD3; // RECEIVE BUFFER n DATA BYTE 3 REGISTER
		uint8_t RXBnD4; // RECEIVE BUFFER n DATA BYTE 4 REGISTER
		uint8_t RXBnD5; // RECEIVE BUFFER n DATA BYTE 5 REGISTER
		uint8_t RXBnD6; // RECEIVE BUFFER n DATA BYTE 6 REGISTER
		uint8_t RXBnD7; // RECEIVE BUFFER n DATA BYTE 7 REGISTER
	};
	uint8_t rx_reg_array[13];
} rx_reg_t;

/* MCP2515 Registers */
/*
 * 	Messages received in the MAB are initially
	applied to the mask and filters of RXB0. In
	addition, only one filter match occurs (e.g.,
	if the message matches both RXF0 and
	RXF2, the match will be for RXF0 and the
	message will be moved into RXB0).
 */

// Acceptance Filter
/* MCP2515 Registers */
typedef struct
{
	uint8_t RXF0SIDH;
	uint8_t RXF0SIDL;
	uint8_t RXF0EID8;
	uint8_t RXF0EID0;
} RXF0;

typedef struct
{
	uint8_t RXF1SIDH;
	uint8_t RXF1SIDL;
	uint8_t RXF1EID8;
	uint8_t RXF1EID0;
} RXF1;

typedef struct
{
	uint8_t RXF2SIDH;
	uint8_t RXF2SIDL;
	uint8_t RXF2EID8;
	uint8_t RXF2EID0;
} RXF2;

typedef struct
{
	uint8_t RXF3SIDH;
	uint8_t RXF3SIDL;
	uint8_t RXF3EID8;
	uint8_t RXF3EID0;
} RXF3;

typedef struct
{
	uint8_t RXF4SIDH;
	uint8_t RXF4SIDL;
	uint8_t RXF4EID8;
	uint8_t RXF4EID0;
} RXF4;

typedef struct
{
	uint8_t RXF5SIDH;
	uint8_t RXF5SIDL;
	uint8_t RXF5EID8;
	uint8_t RXF5EID0;
} RXF5;
// Acceptance Mask
typedef struct
{
	uint8_t RXM0SIDH;
	uint8_t RXM0SIDL;
	uint8_t RXM0EID8;
	uint8_t RXM0EID0;
} RXM0;

typedef struct
{
	uint8_t RXM1SIDH;
	uint8_t RXM1SIDL;
	uint8_t RXM1EID8;
	uint8_t RXM1EID0;
} RXM1;
// ID register
typedef struct
{
	uint8_t tempSIDH;  // standard ID REGISTER HIGH
	uint8_t tempSIDL; // standard ID REGISTER LOW
	uint8_t tempEID8; // extended ID REGISTER HIGH
	uint8_t tempEID0; // extended ID REGISTER LOW
} id_reg_t;

/* Usage Functions */
bool MCP2515_Initialize(void);
bool MCP2515_SetConfigMode(void);
bool MCP2515_SetNormalMode(void);
bool MCP2515_SetSleepMode(void);
void MCP2515_Reset(void);
uint8_t MCP2515_ReadByte(uint8_t address);
void MCP2515_ReadRxSequence(uint8_t instruction, uint8_t *data, uint8_t length);
void MCP2515_WriteByte(uint8_t address, uint8_t data);
void MCP2515_WriteByteSequence(uint8_t startAddress, uint8_t endAddress, uint8_t *data);
void MCP2515_LoadTxSequence(uint8_t instruction, uint8_t *idReg, uint8_t dlc, uint8_t *data);
void MCP2515_LoadTxBuffer(uint8_t instruction, uint8_t data);
void MCP2515_RequestToSend(uint8_t instruction);
uint8_t MCP2515_ReadStatus(void);
uint8_t MCP2515_GetRxStatus(void);
void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data);

#endif
