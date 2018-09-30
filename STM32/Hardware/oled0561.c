#include "oled0561.h"
#include "iic.h"
#include "oleddata.h"

void OLED_display_off(void){
   u8 buff[3] = {
       0xae,	    //关显示
	   0x8d,0x10    //VCC电源
   };
   IIC_sendBuffer(OLED0561_ADDR,CON,buff,3);
}

void OLED_init(void) {
   OLED_display_off();
   OLED_display_clear();
   OLED_display_on();
}

void OLED_display_clear(void) {
	u8 i,j;
	for(i=0xb0;i<0xb8;i++) {
	  IIC_sendByte(OLED0561_ADDR,CON,i);    
	  IIC_sendByte(OLED0561_ADDR,CON,0x10);    //起始页的高4位
	  IIC_sendByte(OLED0561_ADDR,CON,0x00);	   //起始页的低4位
	  for(j=0;j<132;j++) {
	     IIC_sendByte(OLED0561_ADDR,DAT,0x00);
	  }
	}
}

void OLED_display_on(void) {
	u8 buff[28] = {
	0xae,              //0xae:关闭显示;oxaf:打开显示
	0x00,0x10,         //开始地址（双字节）
	0xd5,0x80,         //显示时钟频率
	0xa8,0x3f,         //复用率
	0xd3,0x00,         //显示偏移
	0xb0,              //写入页位置（0xb0 - 0xb7）
	0x40,              //显示开始线
	0x8d,0x14,         //VCC电源
	0xa1,              //设置段重新映射
	0xc8,              //COM输出
	0xda,0x12,         //COM输出方式
	0x81,0xff,         //对比度   0xff最高255
	0xd9,0xf1,         //充电周期
	0xdb,0x30,         //VCC电压寻址设置
	0x20,0x00,		   //水平寻址设置
	0xa4,              //水平显示   0xa5:整体点亮
	0xa6,              //正常显示   0xa7:反显
	0xaf               //打开显示 
	};
	IIC_sendBuffer(OLED0561_ADDR,CON,buff,28);
}

//X 取值 [0-128]
//y 取值 [0-7]
void OLED_display8x16(u8 x,u8 y,u8 ind){
  u8 i,j;
  x+=2; //OLED 屏驱动芯片是从0x02开始作为最左一列
  for(i=0;i<2;i++) {
  	IIC_sendByte(OLED0561_ADDR,CON,0xb0+y);    
	IIC_sendByte(OLED0561_ADDR,CON,x/16 + 0x10);    //起始页的高4位
	IIC_sendByte(OLED0561_ADDR,CON,x%16);
	for(j=0;j<8;j++) {
	   IIC_sendByte(OLED0561_ADDR,DAT,ASCIITAB[ind-0x20][8*i+j]);
	}
	y++;
  }
}

void OLED_display8x16_str(u8 row,u8 *str) {
  u8 r=0;
  while(*str != '\0') {
    OLED_display8x16(r*8,row,*str++);
	r++;
  }

}

void OLED_display16x16(u8 x,u8 y,u16 ind) {
  u8 i,j;
  x+=2; //OLED 屏驱动芯片是从0x02开始作为最左一列
  for(i=0;i<2;i++) {
  	IIC_sendByte(OLED0561_ADDR,CON,0xb0+y);    
	IIC_sendByte(OLED0561_ADDR,CON,x/16 + 0x10);    //起始页的高4位
	IIC_sendByte(OLED0561_ADDR,CON,x%16);
	for(j=0;j<16;j++) {
	   IIC_sendByte(OLED0561_ADDR,DAT,CHINESETAB[ind][16*i+j]);
	}
	y++;
  }
}

void OLED_display128x64(const unsigned char img[1024]) {
  u8 i,j;
  for(i=0;i<8;i++) {
	IIC_sendByte(OLED0561_ADDR,CON,0xb0+i);
	IIC_sendByte(OLED0561_ADDR,CON,0x10);    //起始页的高4位
	IIC_sendByte(OLED0561_ADDR,CON,0x02);
    for(j=0;j<128;j++) {
	  IIC_sendByte(OLED0561_ADDR,DAT,img[i*128+j]);		
    }
  }
}






