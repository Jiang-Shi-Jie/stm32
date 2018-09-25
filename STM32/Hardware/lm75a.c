#include "lm75a.h"

/**
返回三个字节
第一个字节为正负号
第二个字节为整数部分
第三个字节为小数部分
例如  30.32 = 1,30,32
*/
void LM75A_read(u8 *Tempbuffer) {
	u8 buf[2];
    u8 t=0,a=0;   
    IIC_readBuffer(LM75A_ADDR,0x00,buf,2);
	t = buf[0];
	*Tempbuffer = 0;
	if(t & 0x80){
		*Tempbuffer = 1;
		t = ~t;
		t++;
	}
	if(t & 0x01){ a=a+1; }
	if(t & 0x02){ a=a+2; }
	if(t & 0x04){ a=a+4; }
	if(t & 0x08){ a=a+8; }
	if(t & 0x10){ a=a+16; }
	if(t & 0x20){ a=a+32; }
	if(t & 0x40){ a=a+64; }
	Tempbuffer++;
	*Tempbuffer = a;
	a = 0;
	t = buf[1];
	if(t & 0x20){ a=a+12; }
	if(t & 0x40){ a=a+25; }
	if(t & 0x80){ a=a+50; }
	Tempbuffer++;
	*Tempbuffer = a;  
}

void LM75A_POWERDOWN(void){
	IIC_sendByte(LM75A_ADDR,0x01,0x01);
}

