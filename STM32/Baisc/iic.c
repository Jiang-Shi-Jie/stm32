#include "iic.h"

void IIC_init(void) {
	//��ʼ���˿�
	I2C_InitTypeDef iicConfig;
	GPIO_InitTypeDef gpioConfig;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	gpioConfig.GPIO_Pin = IIC_SCL | IIC_SDA;
	gpioConfig.GPIO_Mode = GPIO_Mode_AF_OD;
	gpioConfig.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IICPORT,&gpioConfig);
	iicConfig.I2C_Mode = I2C_Mode_I2C;   //IICģʽ
	iicConfig.I2C_DutyCycle = I2C_DutyCycle_2;
	iicConfig.I2C_OwnAddress1 = HostAddress;  //������ַ
	iicConfig.I2C_Ack = I2C_Ack_Enable;  //����Ӧ��
	iicConfig.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	iicConfig.I2C_ClockSpeed = BusSpeed;
	I2C_Init(I2C1,&iicConfig);
	I2C_Cmd(I2C1,ENABLE);   //ʹ��IIC
}

void IIC_sendBuffer(u8 maddr,u8 taddr,u8* data,u16 len) {
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1, maddr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2C1, taddr);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	while(len--){
	  	I2C_SendData(I2C1,*data);
		data++;
		while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
	I2C_GenerateSTOP(I2C1,ENABLE);
}

//iic���߷���һ���ֽ�  maddr ����ַ  taddr Ŀ���ַ   data����
void IIC_sendByte(u8 maddr,u8 taddr,u8 data) {
	I2C_GenerateSTART(I2C1, ENABLE);  //���� I2Cx ���� START ����
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1, maddr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2C1, taddr);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1, data);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(I2C1, ENABLE);  
}

void IIC_readBuffer(u8 SlaveAddr,u8 readAddr,u8* pBuffer,u16 NumByteToRead){
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1,ENABLE);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_Cmd(I2C1,ENABLE);
	I2C_SendData(I2C1,readAddr);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTART(I2C1,ENABLE);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1,SlaveAddr,I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	while(NumByteToRead){
		if(NumByteToRead == 1){
			I2C_AcknowledgeConfig(I2C1,DISABLE);
			I2C_GenerateSTOP(I2C1,ENABLE);
		}
		if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)){
			*pBuffer = I2C_ReceiveData(I2C1);
			pBuffer++;
			NumByteToRead--;
		}
	}
	I2C_AcknowledgeConfig(I2C1,ENABLE);
}
u8 IIC_readByte(u8 SlaveAddr,u8 readAddr){
	u8 result;
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1,ENABLE);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter); 
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_Cmd(I2C1,ENABLE);
	I2C_SendData(I2C1,readAddr);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTART(I2C1,ENABLE);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	I2C_AcknowledgeConfig(I2C1,DISABLE);
	I2C_GenerateSTOP(I2C1,ENABLE);
	result = I2C_ReceiveData(I2C1);
	return result;
}


 

