/*=============================================================================
 * Copyright (c) 2020, Ezequiel Urdaniz <urdanizezequiel@gmail.com>
 * All rights reserved.
 * Date: 2020/03/07
 * Version: 1.0
 * ===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#ifndef PROGRAMS_RTOS2_TP_INC_TAREALED_H
#define PROGRAMS_RTOS2_TP_INC_TAREALED_H


/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

char LED_ON[6];							//variable char para caracter
char caract_out;

/*=====[Prototypes (declarations) of public functions]=======================*/

void Tarea_Led (void* taskParmPtr);  // Prototipo de tarea LED.

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/




#endif /* __PROGRAMS_RTOS2_TP_INC_TAREALED_H_ */
