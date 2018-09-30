#include "oled0561.h"
#include "iic.h"
#include "oleddata.h"

void OLED_display_off(void){
   u8 buff[3] = {
       0xae,	    //����ʾ
	   0x8d,0x10    //VCC��Դ
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
	  IIC_sendByte(OLED0561_ADDR,CON,0x10);    //��ʼҳ�ĸ�4λ
	  IIC_sendByte(OLED0561_ADDR,CON,0x00);	   //��ʼҳ�ĵ�4λ
	  for(j=0;j<132;j++) {
	     IIC_sendByte(OLED0561_ADDR,DAT,0x00);
	  }
	}
}

void OLED_display_on(void) {
	u8 buff[28] = {
	0xae,              //0xae:�ر���ʾ;oxaf:����ʾ
	0x00,0x10,         //��ʼ��ַ��˫�ֽڣ�
	0xd5,0x80,         //��ʾʱ��Ƶ��
	0xa8,0x3f,         //������
	0xd3,0x00,         //��ʾƫ��
	0xb0,              //д��ҳλ�ã�0xb0 - 0xb7��
	0x40,              //��ʾ��ʼ��
	0x8d,0x14,         //VCC��Դ
	0xa1,              //���ö�����ӳ��
	0xc8,              //COM���
	0xda,0x12,         //COM�����ʽ
	0x81,0xff,         //�Աȶ�   0xff���255
	0xd9,0xf1,         //�������
	0xdb,0x30,         //VCC��ѹѰַ����
	0x20,0x00,		   //ˮƽѰַ����
	0xa4,              //ˮƽ��ʾ   0xa5:�������
	0xa6,              //������ʾ   0xa7:����
	0xaf               //����ʾ 
	};
	IIC_sendBuffer(OLED0561_ADDR,CON,buff,28);
}

//X ȡֵ [0-128]
//y ȡֵ [0-7]
void OLED_display8x16(u8 x,u8 y,u8 ind){
  u8 i,j;
  x+=2; //OLED ������оƬ�Ǵ�0x02��ʼ��Ϊ����һ��
  for(i=0;i<2;i++) {
  	IIC_sendByte(OLED0561_ADDR,CON,0xb0+y);    
	IIC_sendByte(OLED0561_ADDR,CON,x/16 + 0x10);    //��ʼҳ�ĸ�4λ
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
  x+=2; //OLED ������оƬ�Ǵ�0x02��ʼ��Ϊ����һ��
  for(i=0;i<2;i++) {
  	IIC_sendByte(OLED0561_ADDR,CON,0xb0+y);    
	IIC_sendByte(OLED0561_ADDR,CON,x/16 + 0x10);    //��ʼҳ�ĸ�4λ
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
	IIC_sendByte(OLED0561_ADDR,CON,0x10);    //��ʼҳ�ĸ�4λ
	IIC_sendByte(OLED0561_ADDR,CON,0x02);
    for(j=0;j<128;j++) {
	  IIC_sendByte(OLED0561_ADDR,DAT,img[i*128+j]);		
    }
  }
}






