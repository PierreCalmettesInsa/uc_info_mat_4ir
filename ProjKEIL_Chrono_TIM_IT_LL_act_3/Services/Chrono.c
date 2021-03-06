// A COMPLETER

/*
Service permettant de chornom�trer jusqu'� 59mn 59s 99 1/100
Utilise un timer au choix (TIMER1 � TIMER4).
Utilise la lib MyTimers.h /.c
*/



#include "Chrono.h"
#include "MyTimer.h"
#include "UART.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 


// variable priv�e de type Time qui m�morise la dur�e mesur�e
static Time Chrono_Time; // rem : static rend la visibilit� de la variable Chrono_Time limit�e � ce fichier 

// variable priv�e qui m�morise pour le module le timer utilis� par le module
static TIM_TypeDef * Chrono_Timer=TIM1; // init par d�faut au cas o� l'utilisateur ne lance pas Chrono_Conf avant toute autre fct.

// d�claration callback appel� toute les 10ms
void Chrono_Task_10ms(void);

void Chrono_Conf_io(void){
	
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
	
	LL_GPIO_InitTypeDef pin8 ;
	pin8.Pin = LL_GPIO_PIN_8 ;
	pin8.Mode = LL_GPIO_MODE_FLOATING;
	pin8.Speed = LL_GPIO_SPEED_FREQ_LOW;
	pin8.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin8.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOC,&pin8);
	
	LL_GPIO_InitTypeDef pin10 ;
	pin10.Pin = LL_GPIO_PIN_10 ;
	pin10.Mode = LL_GPIO_MODE_OUTPUT;
	pin10.OutputType = LL_GPIO_OUTPUT_PUSHPULL ;
	pin10.Pull = LL_GPIO_PULL_DOWN;
	pin10.Speed = LL_GPIO_SPEED_FREQ_LOW;
	LL_GPIO_Init(GPIOC,&pin10);
	
	LL_GPIO_InitTypeDef pin13 ;
	pin13.Pin = LL_GPIO_PIN_13 ;
	pin13.Mode = LL_GPIO_MODE_FLOATING;
	pin13.Speed = LL_GPIO_SPEED_FREQ_LOW;
	pin13.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin13.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOC,&pin13);
	
	
	
	
	
}





/**
	* @brief  Configure le chronom�tre. 
  * @note   A lancer avant toute autre fonction.
	* @param  Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void Chrono_Conf(TIM_TypeDef * Timer)
{
	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
	
	// Fixation du Timer
	Chrono_Timer=Timer;

	// R�glage Timer pour un d�bordement � 10ms
	MyTimer_Conf(Chrono_Timer,999, 719);
	
	// R�glage interruption du Timer avec callback : Chrono_Task_10ms()
	MyTimer_IT_Conf(Chrono_Timer, Chrono_Task_10ms,3);
	
	Chrono_Conf_io();
	
		// Validation IT
	MyTimer_IT_Enable(Chrono_Timer);
	
	
}


/**
	* @brief  D�marre le chronom�tre. 
  * @note   si la dur�e d�passe 59mn 59sec 99 Hund, elle est remise � z�ro et repart
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Start(void)
{
	MyTimer_Start(Chrono_Timer);
}


/**
	* @brief  Arr�te le chronom�tre. 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Stop(void)
{
	MyTimer_Stop(Chrono_Timer);
}


/**
	* @brief  Remet le chronom�tre � 0 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Reset(void)
{
  // Arr�t Chrono
	MyTimer_Stop(Chrono_Timer);

	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
}


/**
	* @brief  Renvoie l'adresse de la variable Time priv�e g�r�e dans le module Chrono.c
  * @note   
	* @param  Aucun
  * @retval adresse de la variable Time
  */
Time * Chrono_Read(void)
{
	return &Chrono_Time;
}

void Chrono_Background(void)
{
	if (LL_GPIO_IsInputPinSet(GPIOC,PinStart)){
			Chrono_Stop();
	}
	else
	{
		Chrono_Start();
	}
	
	if (!LL_GPIO_IsInputPinSet(GPIOC,LL_GPIO_PIN_13)){
		Chrono_Reset();
	}
	
	
}




/**
	* @brief  incr�mente la variable priv�e Chron_Time modulo 60mn 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Task_10ms(void)
{ 
	Chrono_Time.Hund++;
	if (Chrono_Time.Hund==100)
	{
		LL_GPIO_TogglePin(GPIOC,PinLED);
		Chrono_Time.Sec++;
		Chrono_Time.Hund=0;
	}
	if (Chrono_Time.Sec==60)
	{
		Chrono_Time.Min++;
		Chrono_Time.Sec=0;
	}
	if (Chrono_Time.Min==60)
	{
		Chrono_Time.Hund=0;
	}
	
	send(Chrono_Time.Hund,USART2);

	
}
















