/*=============================================================================
 * Copyright (c) 2019, Ezequiel Urdaniz <urdanizezequiel@gmail.com>
 * All rights reserved.
 * Date: 2019/12/18
 * Version: 1.0
 *===========================================================================*/


/*==================[inlcusiones]============================================*/


#include "MainRTOS.h"
#include "TareaRecibe.h"
#include "TareaTecla.h"


/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

portTickType TiempoTec1,TiempoTec2,TiempoTec3,TiempoTec4,xLastWakeTime;	 //variables tiempos.

uint8_t EstadoTec1 = UP;		//Variables estado tecla.
uint8_t EstadoTec2 = UP;		//Variables estado tecla.

gpioMap_t controlTecla;			//Control de Tecla.
int64_t value =0;				    //Variable Value para miliseg

BaseType_t xcontrolsendTecla;   		// Variable de control de envio Tecla
BaseType_t xcontrolsendMsg;   		   // Variable de control de envio Milisigundo

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

	//-------------TASK TECLA ANTIREBOTE --------------
void Tarea_Tecla( void* taskParmPtr ){
		//------------ Mensaje string -----------------------------------
		teclax[0]='T';					//Variable String TECx
		teclax[1]='E';
		teclax[2]='C';
		teclax[3]='x';
		teclax[4]='\0';					//El caracter nulo finaliza el string

	while( TRUE ){

		xLastWakeTime = xTaskGetTickCount();  //Cuardo inicio de ciclo.

		fsmButtonUpdate( TEC1, &controlTecla, &EstadoTec1, &TiempoTec1);  //Estado TEC1.
	 	vTaskDelay( 1 / portTICK_RATE_MS );

	 	fsmButtonUpdate( TEC2, &controlTecla, &EstadoTec2, &TiempoTec2);  //Estado TEC2.
	 	vTaskDelay( 1 / portTICK_RATE_MS );

		// ----------Enviar Msj de Cola QueueTecla y QueueMsg ----------------------------------

	 	switch (controlTecla){
		case TEC1:
			//--------------- Enviar Telca TEC1 ----------------------------------
			controlTecla=0;
			teclax[3]='1';
			for(uint8_t i=0;i<5;i++){
				xcontrolsendTecla= xQueueSendToBack(xQueueTecla, &teclax[i], 0); //Enviar a Cola el valor sin espera.
				if(xcontrolsendTecla != pdPASS){
					uartWriteString(UART_PC, "Error en enviar valor tecla" );//Error.
				}
			}
			//--------------- Enviar Miliseg TEC1----------------------------------
			value= TiempoTec1;
			str=intToString(value);		//convierte int64_t en String
			for(uint8_t j=0;str[j]!='\0';j++){
				xcontrolsendMsg= xQueueSendToBack(xQueueMsg, &str[j], 0); //Enviar a Cola el valor sin espera.
				if(xcontrolsendMsg != pdPASS){
					uartWriteString(UART_PC, "Error en enviar valor Msg" );//Error.
				}
			}
			break;

		case TEC2:
			//--------------- Enviar Telca TEC2 ----------------------------------
			teclax[3]='2';
			for(uint8_t i=0;i<5;i++){
				xcontrolsendTecla= xQueueSendToBack(xQueueTecla, &teclax[i], 0); //Enviar a Cola el valor sin espera.
				if(xcontrolsendTecla != pdPASS){
					uartWriteString(UART_PC, "Error en enviar valor tecla" );//Error.
				}
			}
			//--------------- Enviar Miliseg TEC2----------------------------------
			value= TiempoTec2;
			str=intToString(value);		//convierte int64_t en String
			for(uint8_t j=0;str[j]!='\0';j++){
				xcontrolsendMsg= xQueueSendToBack(xQueueMsg, &str[j], 0);//Enviar a Cola el valor sin espera.
				if(xcontrolsendMsg != pdPASS){
					uartWriteString(UART_PC, "Error en enviar valor Msg" );//Error.
				}
			}
			break;

		default:		//Default enviar error y clear variables
			uartWriteString(UART_PC, "Error de tecla" );  //Error
			controlTecla =0;
			break;

	 	}

		// Envio la tarea al estado bloqueado.
	 	vTaskDelayUntil( &xLastWakeTime, (80/ portTICK_RATE_MS) );
	}
}



	// ------------FUNCIÓN UPDATE ESTADO DE TECLA -------------------
void fsmButtonUpdate(gpioMap_t tecla, gpioMap_t* controlTecla, uint8_t* Estadotec, portTickType* TiempoTec){

		switch (*Estadotec){					//Switch estado de tecla
		 case UP:
	  		  if(0 == gpioRead(tecla)){				//Read tecla (0 pulsada - 1 no pulsada )
	  			*Estadotec = FALLING;				//Guardo estado tecla.
	  			*TiempoTec = xTaskGetTickCount();   //Registro tiempo.
	  		  }
	  		  break;

	  	 case FALLING:
	  		 if(0  == gpioRead(tecla)){				//Read tecla (0 pulsada - 1 no pulsada )
	  			 if (((xTaskGetTickCount()-*TiempoTec)*portTICK_RATE_MS)>=20){ //Tiempo antirebote.
	  				*Estadotec = DOWN;				//Guardo estado tecla.
	  			 }
	  		 }
	  		 else {
	  			*Estadotec = UP;					//Guardo estado tecla.
	  		 }
	  	break;

	  	 case DOWN:
	  		if(1 == gpioRead(tecla)){				//Read tecla (0 pulsada - 1 no pulsada )
	  			*Estadotec = RISING;			  	//Guardo estado tecla.
	  			*TiempoTec = xTaskGetTickCount();	//Registro tiempo.
	  		}
	  		else {//(Evento DOWN)
	  			//----------- Guardar la tecla y el tiempotec de pulsado ------.
	  			*TiempoTec=((xTaskGetTickCount()-*TiempoTec)*portTICK_RATE_MS); //Guardo el tiempo en mseg.
	  			*controlTecla = tecla;						//Guardo tecla
	  		}
	  	 break;

	  	 case RISING:
	  		 if(1  == gpioRead(tecla)){				//Read tecla (0 pulsada - 1 no pulsada )
				 if (((xTaskGetTickCount()-*TiempoTec)*portTICK_RATE_MS)>=20){ //Tiempo antirebote.
					 *Estadotec = UP;				//Guardo estado tecla.
				 }
			}
			 else {
				 *Estadotec = DOWN; 			//Guardo estado tecla.
			}
		 break;

	  	 default://Case default.
	  		*Estadotec = UP;					//Reseteo estado tecla.
	  	 break;
	  }
}


/*==================[fin del archivo]========================================*/
