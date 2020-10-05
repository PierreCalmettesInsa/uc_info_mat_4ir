#include "UART.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_usart.h" 




void Usart_Conf(USART_TypeDef * Usart)
{
	if (Usart == USART1 )
	{
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
		LL_GPIO_InitTypeDef pin9 ;
		pin9.Pin = LL_GPIO_PIN_9 ;
		pin9.Mode = LL_GPIO_MODE_ALTERNATE;
		pin9.Speed = LL_GPIO_SPEED_FREQ_LOW;
		pin9.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		pin9.Pull = LL_GPIO_PULL_DOWN;
		LL_GPIO_Init(GPIOA,&pin9);
	}
	else if (Usart == USART2)
	{

		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
		LL_GPIO_InitTypeDef pin2 ;
		pin2.Pin = LL_GPIO_PIN_2 ;
		pin2.Mode = LL_GPIO_MODE_ALTERNATE;
		pin2.Speed = LL_GPIO_SPEED_FREQ_LOW;
		pin2.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		pin2.Pull = LL_GPIO_PULL_DOWN;
		LL_GPIO_Init(GPIOA,&pin2);
		
	}
	else if (Usart == USART3)
	{
		
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
		LL_GPIO_InitTypeDef pin10 ;
		pin10.Pin = LL_GPIO_PIN_10 ;
		pin10.Mode = LL_GPIO_MODE_ALTERNATE;
		pin10.Speed = LL_GPIO_SPEED_FREQ_LOW;
		pin10.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		pin10.Pull = LL_GPIO_PULL_DOWN;
		LL_GPIO_Init(GPIOB,&pin10);
	}
	
	
	LL_USART_InitTypeDef usart ;
	usart.BaudRate = 9600 ;
	usart.DataWidth =LL_USART_DATAWIDTH_8B;
	usart.StopBits = LL_USART_STOPBITS_1;
	usart.Parity = LL_USART_PARITY_NONE;
	usart.TransferDirection = LL_USART_DIRECTION_TX_RX ;
	usart.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	
	LL_USART_Init(Usart,&usart);
	LL_USART_Enable(Usart);
	

	
}



void send(char data,USART_TypeDef * Usart)
{
	LL_USART_TransmitData8(Usart,data);
	while (!LL_USART_IsActiveFlag_TXE(Usart)){};
}













