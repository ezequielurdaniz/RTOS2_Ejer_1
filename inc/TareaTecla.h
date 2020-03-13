/*=============================================================================
 * Copyright (c) 2020, Ezequiel Urdaniz <urdanizezequiel@gmail.com>
 * All rights reserved.
 * Date: 2020/03/07
 * Version: 1.0
 * ===========================================================================*/

#ifndef PROGRAMS_RTOS2_TP_INC_TECLA_H_
#define PROGRAMS_RTOS2_TP_INC_TECLA_H_

#include "MainRTOS.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif


/*=====[Definition macros of public constants]===============================*/

char teclax[5];							//variable char para caracter
char * str;

//---- Definición de estado de TECLA --------------

#define UP      1
#define FALLING 2
#define DOWN	3
#define RISING  4

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

/*=====[Prototypes (declarations) of public functions]=======================*/


void fsmButtonUpdate(gpioMap_t tecla,			// Prototipo de función estado de tecla.
					gpioMap_t* controlTecla,
					uint8_t* Estadotec,
					portTickType* TiempoTec);

void Tarea_Tecla( void* taskParmPtr ); 				// Prototipo de tarea tecla antirebote.


/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/



#endif /* __PROGRAMS_RTOS2_TP_INC_TECLA_H___ */
