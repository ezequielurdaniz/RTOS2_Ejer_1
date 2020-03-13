/*=============================================================================
 * Copyright (c) 2020, Ezequiel Urdaniz <urdanizezequiel@gmail.com>
 * All rights reserved.
 * Date: 2020/03/07
 * Version: 1.0
 * ===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef PROGRAMS_RTOS2_TP_INC_MAINRTOS_H
#define PROGRAMS_RTOS2_TP_INC_MAINRTOS_H

/*=====[Inclusions of public function dependencies]==========================*/

#include "stdint.h"
#include "stddef.h"
#include "sapi.h"			// sAPI header
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"			//Api de control de tareas y temporización
#include "semphr.h"			//Api de sincronización (sem y mutex)

/*=====[C++ - begin]=========================================================*/


#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/
QueueHandle_t xQueueLed, xQueueTecla, xQueueMsg; // Variable de tipo QueueHandle_t para almacenar la cola al que acceden las tareas


/*=====[Prototypes (declarations) of public functions]=======================*/

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* _PROGRAMS_RTOS2_TP_INC_MAINRTOS_H_ */
