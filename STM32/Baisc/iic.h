#ifndef _IIC_H_
#define _IIC_H_

#include "sys.h"

#define IICPORT GPIOB
#define IIC_SCL GPIO_Pin_6
#define IIC_SDA GPIO_Pin_7

#define HostAddress 0xc0
#define BusSpeed 200000	 //总线速度  <400000

void IIC_init(void);
void IIC_sendBuffer(u8 maddr,u8 taddr,u8* data);
void IIC_sendByte(u8 maddr,u8 taddr,u8 data);
void IIC_readBuffer(u8 SlaveAddr,u8 readAddr,u8* pBuffer,u16 NumByteToRead);
u8 IIC_readByte(u8 SlaveAddr,u8 readAddr);


#endif
