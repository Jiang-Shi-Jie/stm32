#include "relay.h"

void Relay_init(void){
  GPIO_InitTypeDef gpiobConfig;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //开启AFIO重映射时钟
  gpiobConfig.GPIO_Pin = RELAY1|RELAY2;
  gpiobConfig.GPIO_Mode = GPIO_Mode_Out_PP;
  gpiobConfig.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(RELAYPORT,&gpiobConfig);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);   //禁用JTAG
  GPIO_ResetBits(RELAYPORT,RELAY1 | RELAY2);   //关闭继电器
}

void setRelay1(BitAction BitVal){
   GPIO_WriteBit(RELAYPORT,RELAY1,BitVal);
}

void setRelay2(BitAction BitVal){
   GPIO_WriteBit(RELAYPORT,RELAY2,BitVal);
}
