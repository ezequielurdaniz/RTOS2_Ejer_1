/*=============================================================================
 * Copyright (c) 2020, Ezequiel Urdaniz <urdanizezequiel@gmail.com>
 * All rights reserved.
 * Date: 2020/03/07
 * Version: 1.0
 * ===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "MainRTOS.h"
#include "TareaRecibe.h"
#include "TareaLed.h"
#include "string.h"


/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

BaseType_t xcontrolsendl;   		// Variable de control de envio.


/*==================[definiciones de datos externos]=========================*/

DEBUG_PRINT_ENABLE;  //Para configurar los mensajes por monitor


/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

//----------- TASK LED - TAREA A -----------------------

void Tarea_Led (void* taskParmPtr){

	// ----------- Tarea periodica cada 500 ms ----------------------
	portTickType xPeriodicity =  500 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	//------------ Mensaje string -----------------------------------
	LED_ON[0]= 'L';						//Variable String LED ON
	LED_ON[1]= 'E';
	LED_ON[2]= 'D';
	LED_ON[3]= '_';
	LED_ON[4]= 'O';
	LED_ON[5]= 'N';
	LED_ON[6]='\0';						//El caracter nulo finaliza el string

	while(TRUE){

		// --------- Led ON/OFF --------------------------------------

		gpioToggle(LEDG);					 //Toggle ON/OFF Led periodicamente.

		if(gpioRead(LEDG)==ON){

			// ----------Cola de trabajo ----------------------------------

			for (uint8_t i=0; i<7; i++){
				//Enviar a Cola 1 valor sin espera.
				xcontrolsendl = xQueueSendToBack(xQueueLed, &LED_ON[i], 0);
				if (xcontrolsendl != pdPASS) {
					//No se pudo escribir en la cola porque estaba llena
					uartWriteString(UART_PC, "Error en enviar valor" );		//Error.
				}
			}
		}
		//----- Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
		vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
	}
}

/*==============================[fin del archivo]========================================*/
