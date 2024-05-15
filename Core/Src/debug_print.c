/*
 * debug_print.c
 *
 *  Created on: May 3, 2024
 *      Author: Lim Dale
 */


//			char frame[60]; // Make it large enough to hold the combined string
//			sprintf(frame, "ID:%04X, DLC:%X, Data:", rxMessage.frame.id, rxMessage.frame.dlc);
//			switch(rxMessage.frame.dlc) {
//			    case 1:
//			        sprintf(frame + strlen(frame), " %02X", rxMessage.frame.data0);
//			        break;
//			    case 2:
//			        sprintf(frame + strlen(frame), " %02X %02X", rxMessage.frame.data0, rxMessage.frame.data1);
//			        break;
//			    case 3:
//			        sprintf(frame + strlen(frame), " %02X %02X %02X", rxMessage.frame.data0, rxMessage.frame.data1, rxMessage.frame.data2);
//			        break;
//			    case 4:
//			        sprintf(frame + strlen(frame), " %02X %02X %02X %02X", rxMessage.frame.data0, rxMessage.frame.data1, rxMessage.frame.data2, rxMessage.frame.data3);
//			        break;
//			    case 5:
//			        sprintf(frame + strlen(frame), " %02X %02X %02X %02X %02X", rxMessage.frame.data0, rxMessage.frame.data1, rxMessage.frame.data2, rxMessage.frame.data3, rxMessage.frame.data4);
//			        break;
//			    case 6:
//			        sprintf(frame + strlen(frame), " %02X %02X %02X %02X %02X %02X", rxMessage.frame.data0, rxMessage.frame.data1, rxMessage.frame.data2, rxMessage.frame.data3, rxMessage.frame.data4, rxMessage.frame.data5);
//			        break;
//			    case 7:
//			        sprintf(frame + strlen(frame), " %02X %02X %02 X%02X %02X %02X %02X", rxMessage.frame.data0, rxMessage.frame.data1, rxMessage.frame.data2, rxMessage.frame.data3, rxMessage.frame.data4, rxMessage.frame.data5, rxMessage.frame.data6);
//			        break;
//			    case 8:
//			        sprintf(frame + strlen(frame), " %02X %02X %02X %02X %02X %02X %02X %02X", rxMessage.frame.data0, rxMessage.frame.data1, rxMessage.frame.data2, rxMessage.frame.data3, rxMessage.frame.data4, rxMessage.frame.data5, rxMessage.frame.data6, rxMessage.frame.data7);
//			        break;
//			}
//			sprintf(frame + strlen(frame), "\r\n");
//			HAL_UART_Transmit(&huart2, (uint8_t *)frame, strlen(frame), HAL_MAX_DELAY);


