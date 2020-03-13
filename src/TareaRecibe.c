/*=============================================================================
 * Copyright (c) 2020, Ezequiel Urdaniz <urdanizezequiel@gmail.com>
 * All rights reserved.
 * Date: 2020/03/07
 * Version: 1.0
 * ===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "TareaRecibe.h"
#include "string.h"
/*==================[definiciones y macros]==================================*/
//*==================[definiciones de datos internos]==========================*/

	BaseType_t xcontrolreciLed;   				// Variable de control de envio Led.
	BaseType_t xcontrolreciTec;   				// Variable de control de envio Tec.
	BaseType_t xcontrolreciMsg;   				// Variable de control de envio Miliseg.
	bool_t EstadoMsj1=FALSE;						//Variable de estado Led.
	bool_t EstadoMsj2=FALSE;						//Variable de estado Tecla.
	bool_t EstadoMsj3=FALSE;						//Variable de estado Msg.
	uint8_t ind1 = 0;							//Variable de indice Led
	uint8_t ind2 = 0;							//Variable de indice Tec
	uint8_t ind3 = 0;							//Variable de indice Miliseg
	TickType_t xTicksToWait = 0;


/*==================[definiciones de datos externos]=========================*/

DEBUG_PRINT_ENABLE;  //Para configurar los mensajes por monitor

/*==================[funcion principal]======================================*/

// ------------------- FUNCIÓN de CONFIG de UART  -------------------

void init_UART(void){

	 // Inicializar UART_USB para conectar a la PC
	 uartConfig( UART_PC, BAUDIO );
	 uartWriteString( UART_PC, "UART_PC configurada.\r\n" );

}


	//-------------TASK RECIBIR COLAS --------------
void Tarea_Recibe (void* taskParmPtr){

	while(TRUE){

		//-------------- Recibir Msj de Cola QueueLed ----------------------------------

		xcontrolreciLed = xQueueReceive(xQueueLed, &caract_inLed, xTicksToWait);

		if(xcontrolreciLed == pdPASS){		//Si hay dato en la cola.
			MensajeLed[ind1]=caract_inLed;			//Guardo el caracter
			if(MensajeLed[ind1]!= '\0'){			//Si es caracter no es nulo
				ind1++;							//incremento indice
				EstadoMsj1=FALSE;				//Estado de Msj no completo
			}
			else{
				ind1= 0;							//Clear indice
				EstadoMsj1=TRUE;					//Estado de Msj completo
			}
			if(EstadoMsj1){							//Completo el Msj, envio por uart
				uartWriteString(UART_PC,MensajeLed);	//Envio String
				EstadoMsj1=FALSE;					//EstadoMsj no completo.
				ind1=0;
			}
		}

		//-------------- Recibir Msj de Cola QueueTecla  ----------------------------------

		xcontrolreciTec = xQueueReceive(xQueueTecla, &caract_inTec, xTicksToWait);
		if(xcontrolreciTec == pdPASS){		//Si hay dato en la cola.
			MensajeTec[ind2]=caract_inLed;			//Guardo el caracter
			if(MensajeTec[ind2]!= '\0'){			//Si es caracter no es nulo
				ind2++;							//incremento indice
				EstadoMsj2=FALSE;				//Estado de Msj no completo
			}
			else{
				ind2= 0;							//Clear indice
				EstadoMsj2=TRUE;					//Estado de Msj completo
			}
			if(EstadoMsj2){							//Completo el Msj, envio por uart
				uartWriteString(UART_PC,MensajeTec);	//Envio String
				EstadoMsj2=FALSE;					//EstadoMsj no completo.
				ind2=0;
			}

		}

		//-------------- Recibir Msj de Cola QueueMsg ----------------------------------
		xcontrolreciMsg = xQueueReceive(xQueueMsg, &caract_inMsg, xTicksToWait);
		if(xcontrolreciMsg == pdPASS){		//Si hay dato en la cola.
			MensajeMsg[ind3]=caract_inMsg;			//Guardo el caracter
			if(MensajeMsg[ind3]!= '\0'){			//Si es caracter no es nulo
				ind3++;							//incremento indice
				EstadoMsj3=FALSE;				//Estado de Msj no completo
			}
			else{
				ind3= 0;							//Clear indice
				EstadoMsj3=TRUE;					//Estado de Msj completo
			}
			if(EstadoMsj3){							//Completo el Msj, envio por uart
				uartWriteString(UART_PC,MensajeMsg);	//Envio String
				EstadoMsj3=FALSE;					//EstadoMsj no completo.
				ind3=0;
			}

		}

 		vTaskDelay( 5/ portTICK_RATE_MS ); 		//Estado Blocked para liberacion de recurso.
	}
}







/*==================[fin del archivo]========================================*/

