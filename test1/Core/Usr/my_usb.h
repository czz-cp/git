#ifndef  __MY_USB_H
#define  __MY_USB_H

#include "main.h"

#define USB_FRAME_HEAD				 0x42				 //USB通信序列帧头
#define USB_FRAME_LENMIN  			 4					 //USB通信序列字节最短长度
#define USB_FRAME_LENMAX			 30					 //USB通信序列字节最长长度
#define USB_FRAME_OK                 6                   //USBOK

typedef struct 
{
	bool receiveStart;									    //数据接收开始
	uint8_t receiveIndex;									//接收序列
	bool receiveFinished;									//数据队列接收并校验完成
	uint8_t receiveBuff[USB_FRAME_LENMAX];	                //USB接收队列：临时接收
	uint8_t receiveBuffFinished[USB_FRAME_LENMAX];	        //USB接收队列：校验成功
	uint16_t counter;										//计数器
    uint16_t counterDrop;                                   //掉线计数器    
    uint16_t counterSend;                                   //自检数据发送计数器
    bool connected;                                         //上位机通信连接状态
    bool inspectorEnable;                                   //智能汽车自检软件连接使能
    bool transmitFinished;                                   //数据队列发送成功
}UsbStruct;

extern UsbStruct usbStr;

void USB_Init(void);
void User_UART_RxCpltCallback(void);

#endif 
