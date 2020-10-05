

#include "stm32f103xb.h" 


/**
	* @brief  Configure USART. 
  * @note   A lancer avant toute autre fonction.
  * @retval None
  */
void Usart_Conf(USART_TypeDef * Usart);


void send(char data,USART_TypeDef * Usart);
