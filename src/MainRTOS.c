/*=============================================================================
 * Copyright (c) 2020, Ezequiel Urdaniz <urdanizezequiel@gmail.com>
 * All rights reserved.
 * Date: 2020/03/07
 * Version: 1.0
 * ===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/


#include "MainRTOS.h"
#include "TareaLed.h"
#include "TareaRecibe.h"
#include "TareaTecla.h"
#include "queue.h"


/*=====[Definition macros of private constants]==============================*/

//Mensaje_t mensaje[CANT];			//mensajes de estructuras

/*=====[Definitions of extern global variables]==============================*/

DEBUG_PRINT_ENABLE;  //Configurar mensajes de consola

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/


int main( void ){

		// ---------- CONFIGURACIONES ------------------------------
		boardConfig();			// Init & config CIAA

		init_UART();			// Init UART

		//--------------- CREACION COLAS -----------------------------
		xQueueLed = xQueueCreate(1, sizeof(char)); //Cola de 1 valor char
		xQueueTecla = xQueueCreate(1, sizeof(char)); //Cola de 1 valor char
		xQueueMsg = xQueueCreate(1, sizeof(char)); //Cola de 1 valor char


		if (xQueueLed != NULL || xQueueTecla != NULL || xQueueMsg != NULL) {

		// --------------CREACIÓN de TAREAS --------------------------
			xTaskCreate(
				Tarea_Led,                     	// Funcion de la tarea Led
				(const char *)"Tarea A",     	// Nombre de la tarea como String
				configMINIMAL_STACK_SIZE*2, 	// Cantidad de stack de la tarea
				0,                          	// Parametros de tarea
			    tskIDLE_PRIORITY+1,         	// Prioridad de la tarea
			    0                           	// Puntero a la tarea creada en el sistema
			);

			xTaskCreate(
				Tarea_Tecla,                     // Funcion de la tarea tecla
				(const char *)"Tarea B",     	// Nombre de la tarea.
			    configMINIMAL_STACK_SIZE*2,		// Cantidad de stack.
			    0,                         		// Parametros de tarea.
			    tskIDLE_PRIORITY+1,        		// Prioridad de la tarea.
			    0                          		// Puntero a la tarea.
			);

			xTaskCreate(
				Tarea_Recibe,                    // Funcion de la tarea recibir
				(const char *)"Tarea C",     	// Nombre de la tarea como String
				configMINIMAL_STACK_SIZE*2, 	// Cantidad de stack de la tarea
				0,                          	// Parametros de tarea
			    tskIDLE_PRIORITY+1,         	// Prioridad de la tarea
			    0                           	// Puntero a la tarea creada en el sistema
			);



			//-------------- INCIAR SCHEDDULER -------------------------

				 vTaskStartScheduler();	//Inicializo el SO.
			}
		else {

			gpioWrite( LEDR, ON );  // No pudo iniciar el scheduler.

			}

			// ------------- REPETIR POR SIEMPRE --------------------------
		while( TRUE ){
				   //Sin Accion.
			}

		return 0;
	}
