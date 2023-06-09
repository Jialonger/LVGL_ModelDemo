#include "i2c.h"


//GPIO引脚的初始化由用户完成
//GPIO设置为开漏输出
//8 9
#define SCL			PBout(6)			//SCL引脚
#define SDA			PBout(7)			//SDA引脚
#define READ_SDA	PBin(7)

#define delay()	delay_us(1)//__asm("nop")

void I2C_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA时钟

	//GPIOF9,F10初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;//LED2对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//开漏
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO

}

//发送一个起始信号
bool I2C_Start()
{
	SDA = 1;
	delay();
	if(!READ_SDA)		//检测引脚是否正确初始化
		return false;
	SCL = 1;
	delay();
	SDA = 0;
	delay();
	if(READ_SDA)		//检测引脚是否正确初始化
		return false;	
	SCL = 0;
	delay();
	return true;		//起始信号发送成功
}


//发送一个停止信号
void I2C_Stop()
{
	SDA = 0;
	delay();
	SCL = 1;
	delay();
	SDA = 1;
	delay();	
}

//发送一个字节信息
void I2C_SendByte(uint8_t data)
{
	uint8_t count;
	for(count=0;count<8;count++)
	{
		if(data&0x80)//发送一位数据
			SDA = 1;
		else
			SDA = 0;
		delay();
		SCL = 1;	//目标采样一位数据
		delay();
		SCL = 0;
		data <<= 1;
		delay();
	}
}


//接受一个字节信息
unsigned char I2C_ReadByte()
{
	uint8_t data,count;
	for(count=0;count<8;count++)
	{
		delay();
		data <<= 1;
		SCL = 1;
		delay();
		if(READ_SDA)	//采样一位数据
			data++;
		SCL = 0;
		
	}
	delay();
	return data;
}

//返回true正确应答，返回false错误应答
bool I2C_WaitAck()
{
	uint8_t count;
	SDA = 1; 	//释放SDA总线
	SCL = 1;	//采样应答信号
	delay();	//等待信号稳定
	for(count=0;count<50;count++)
	{
		if(!READ_SDA)	//如果检测到应答信号
		{
			SCL = 0;
			return true;
		}
	}
	delay();
	return false;	
}

//发送一个应答信号
void I2C_Ack()
{
	SDA = 0;
	delay();
	SCL = 1;
	delay();
	SCL = 0;
	SDA = 1;//释放SDA总线（必须加上这句）
	delay();
}

//发送一个非应答
void I2C_NAck()
{
	SDA = 1;
	delay();
	SCL = 1;
	delay();
	SCL = 0;
	delay();	
}

bool I2c_WriteByte(unsigned char slave_addr, unsigned char reg_addr,unsigned char const dat)
{
	if(I2C_Start())
	{
		I2C_SendByte(slave_addr<<1);//发送设备地址
		if(I2C_WaitAck()==false)	//如果错误应答
		{
			I2C_Stop();
			return false;
		}
		I2C_SendByte(reg_addr);		//发送目标寄存器地址，方向为写
		I2C_WaitAck();				//由于前面已检测过应答信号，此处不重复检测
		I2C_Stop();
		return true;
	}
	return false;
}

int i2c_write(unsigned char slave_addr, unsigned char reg_addr,unsigned char length, unsigned char const *data)
{
	uint8_t count;
	if(I2C_Start())
	{
		I2C_SendByte(slave_addr<<1);//发送设备地址
		if(I2C_WaitAck()==false)	//如果错误应答
		{
			I2C_Stop();
			return 1;
		}
		I2C_SendByte(reg_addr);		//发送目标寄存器地址，方向为写
		I2C_WaitAck();				//由于前面已检测过应答信号，此处不重复检测
		for(count=0;count<length;count++)
		{
			I2C_SendByte(data[count]);	//发送数据
			if(I2C_WaitAck()==false)	//如果目标设备停止接收
			{
				I2C_Stop();
				return 0;
			}
		}
		I2C_Stop();
		return 0;
	}
	return 1;
}


int i2c_read(unsigned char slave_addr, unsigned char reg_addr,unsigned char length, unsigned char *data)
{
	if(I2C_Start())
	{
		I2C_SendByte(slave_addr<<1);//发送设备地址，方向为写
		if(I2C_WaitAck()==false)	//如果错误应答
		{
			I2C_Stop();
			return 1;
		}
		I2C_SendByte(reg_addr);		//发送目标寄存器地址，方向为写
		I2C_WaitAck();				//由于前面已检测过应答信号，此处不重复检测
		I2C_Start();				//重新发送起始信号，改变数据传输方向
		I2C_SendByte((slave_addr<<1)+1);	//发送设备地址，方向为读
		I2C_WaitAck();
		for(;length>0;length--)
		{
			*data = I2C_ReadByte();
			if(length==1)
				I2C_NAck();
			else
				I2C_Ack();
			data++;
		}
		I2C_Stop();
		return 0;
	}
	return 1;
}
