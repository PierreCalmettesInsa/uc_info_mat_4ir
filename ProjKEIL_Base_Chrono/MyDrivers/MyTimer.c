// TOUT A FAIRE !! //

/*
 indispensable pour pouvoir adresser les registres des p�riph�riques.
 Rem : OBLIGATION d'utiliser les d�finitions utiles contenues dans ce fichier (ex : TIM_CR1_CEN, RCC_APB1ENR_TIM2EN ...)
 pour une meilleure lisibilit� du code.

 Pour les masques, utiliser �galement les d�finitions propos�e
 Rappel : pour mettre � 1  , reg = reg | Mask (ou Mask est le repr�sente le ou les bits � positionner � 1)
				  pour mettre � 0  , reg = reg&~ Mask (ou Mask est le repr�sente le ou les bits � positionner � 0)
 
*/ 
#include "stm32f103xb.h" 

void (* ptr_fct) (void);



void MyTimer_Conf(TIM_TypeDef * Timer,int Arr, int Psc)
{
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	if (Timer == TIM1)
	{
		RCC->APB1ENR|=RCC_APB2ENR_TIM1EN;
	}
		else if (Timer == TIM2)
	{
		RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;
	}
		else if (Timer == TIM3)
	{
		RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;
	}
		else if (Timer == TIM4)
	{
		RCC->APB1ENR|=RCC_APB1ENR_TIM4EN;
	}
	
	Timer -> ARR = Arr ;
	Timer -> PSC = Psc ;	
}

void MyTimer_Start(TIM_TypeDef * Timer)
{
		Timer->CR1|=TIM_CR1_CEN;
}

void MyTimer_Stop(TIM_TypeDef * Timer)
{
		Timer->CR1&= ~TIM_CR1_CEN;
}



void MyTimer_IT_Conf(TIM_TypeDef * Timer, void (*IT_function) (void),int Prio)
{
	int chanel_prio ;
	if (Timer == TIM1)
	{
		chanel_prio = 25 ;
	}
	else if (Timer == TIM2)
	{
		chanel_prio = 28;
		TIM2 -> DIER |= (1 << 6);
	}
	else if (Timer == TIM3)
	{
		chanel_prio = 29;
	}
	else if (Timer == TIM4)
	{
		chanel_prio = 30;
	}
	ptr_fct = IT_function ;
	
	NVIC -> IP[chanel_prio] = (Prio << 4) ;
		
	NVIC -> ISER[0] |= (1 << (chanel_prio));
	
}

void TIM2_IRQHandler(void)
{
	TIM2 -> SR &= ~TIM_SR_UIF;
	(*ptr_fct)();

}



void MyTimer_IT_Enable(TIM_TypeDef * Timer)
{
	Timer->DIER|=TIM_DIER_UIE;	
}



void MyTimer_IT_Disable(TIM_TypeDef * Timer)
{
		Timer->DIER&=~TIM_DIER_UIE;	
}















