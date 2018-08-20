#include "usart.h"
#include "stdarg.h"

void USART1_init(u32 speed) {
GPIO_InitTypeDef usartPinConfig;
USART_InitTypeDef	usartConfig;
NVIC_InitTypeDef nvicConfig;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
//初始化USART1_TX端口
usartPinConfig.GPIO_Pin = GPIO_Pin_9;
usartPinConfig.GPIO_Speed	= GPIO_Speed_50MHz;
usartPinConfig.GPIO_Mode = GPIO_Mode_AF_PP;
GPIO_Init(GPIOA,&usartPinConfig);
//初始化USART1_RX端口
usartPinConfig.GPIO_Pin = GPIO_Pin_10;
usartPinConfig.GPIO_Mode = GPIO_Mode_IN_FLOATING;
GPIO_Init(GPIOA,&usartPinConfig);
nvicConfig.NVIC_IRQChannel = USART1_IRQn;
nvicConfig.NVIC_IRQChannelPreemptionPriority = 3;
nvicConfig.NVIC_IRQChannelSubPriority = 3;
nvicConfig.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&nvicConfig);
usartConfig.USART_BaudRate =  speed;
usartConfig.USART_WordLength = USART_WordLength_8b;
usartConfig.USART_StopBits = USART_StopBits_1;
usartConfig.USART_Parity = USART_Parity_No;
usartConfig.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
usartConfig.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
USART_Init(USART1,&usartConfig);
USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
USART_Cmd(USART1,ENABLE);
}

void USART1_send_char(u8 data) {
   USART_SendData(USART1,data);
   while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
}

void USART1_printf (char *fmt, ...){ 
	char buffer[USART_REC_LEN+1];
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART_REC_LEN+1, fmt, arg_ptr);
	while ((i < USART_REC_LEN) && (i < strlen(buffer))){
		USART1_send_char((u8) buffer[i++]);
	}
	va_end(arg_ptr);
}
