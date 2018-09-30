#include "stm32f10x.h"
#include "delay.h"
#include "relay.h"
#include "touchkey.h"

int main (void){
  TOUCH_KEY_init();
  Relay_init();
  while(1){
    if(!GPIO_ReadInputDataBit(GPIOA,TOUCHKEY_A)) {
	  setRelay1(Bit_SET); 
	}
	if(!GPIO_ReadInputDataBit(GPIOA,TOUCHKEY_B)) {
	  setRelay1(Bit_RESET);
	}
	if(!GPIO_ReadInputDataBit(GPIOA,TOUCHKEY_C)) {
	  setRelay2(Bit_SET);
	}
	if(!GPIO_ReadInputDataBit(GPIOA,TOUCHKEY_D)) {
	  setRelay2(Bit_RESET);
	}	
  }	
}
