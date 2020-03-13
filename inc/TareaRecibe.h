/*=============================================================================
 * Copyright (c) 2020, Ezequiel Urdaniz <urdanizezequiel@gmail.com>
 * All rights reserved.
 * Date: 2020/03/07
 * Version: 1.0
 * ===========================================================================*/

#ifndef PROGRAMS_RTOS2_TP_INC_TAREARECIBE_H
#define PROGRAMS_RTOS2_TP_INC_TAREARECIBE_H

#include "MainRTOS.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif


/*=====[Definition macros of public constants]===============================*/

#define BAUDIO	9600
#define UART_PC        UART_USB

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

char MensajeLed[6];							//Variable String LED ON
char MensajeTec[4];							//Variable String Tecla
char MensajeMsg[20];						//Variable String Miliseg
char caract_inLed;								//variable char para caracter
char caract_inTec;								//variable char para caracter
char caract_inMsg;								//variable char para caracter


char* msjLed;									//Variable Texto Led
char* msjTecla;									//Variable Texto Tecla
char* msjMsg;									//Variable Texto Msg


/*=====[Prototypes (declarations) of public functions]=======================*/


void init_UART(void); 		// Prototipo de función configurar comunicacion de EDUCIAA.

void Tarea_Recibe (void* taskParmPtr); // Prototipo de tarea recibir.


/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/



#endif /* _PROGRAMS_RTOS2_TP_INC_TAREARECIBE_H_ */
