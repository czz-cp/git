#include "my_usb.h"

UsbStruct usbStr;

void USB_Init(void){
    //USB数据初始化
    usbStr.receiveFinished = true;
    usbStr.receiveStart = false;
    usbStr.transmitFinished = false;
}

/**
* @brief        发送一个字节数据
* @param        
* @ref          
* @author       
* @note         
**/
void USB_TransmitByte(uint8_t data)
{
    USART1->SR;           
    HAL_UART_Transmit_DMA(&huart1, (uint8_t *)&data, sizeof(data));	
    while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//等待发送结束
}


/**
* @brief        发送数据给上位机 
* @param        
* @ref          
* @author       
* @note         
**/
void USB_Transmit_To(){
    if(usbStr.receiveFinished){
    //帧头
        USB_TransmitByte(USB_FRAME_HEAD);
    //发送编码器count
        /*char buf1[8] = {0};
        for(int i = 0; i < 8; i++){
            buf1[i] = (encoderStr.EncoderValue1 >> (7 - i));
        }
        char buf2[8] = {0};
        for(int i = 0; i < 8;i++){
            buf2[i] = (encoderStr.EncoderValue2 >> (7 - i));
        }
        int flag = 8;
        for(int i = 0;i < 16;i++){
            while(flag){
                USB_TransmitByte(buf1[i]);
                flag--;
            }
            USB_TransmitByte(buf2[i-8]);
        }*/
        uint8_t ev1 = (uint8_t)encoderStr.EncoderValue1;
        uint8_t ev2 = (uint8_t)encoderStr.EncoderValue2;
        USB_TransmitByte(ev1);
        USB_TransmitByte(ev2);
        //标记接收完成
        usbStr.transmitFinished = true;
    }
}


/**
* @brief        dma中断的回调函数 
* @param        huart: 串口号
* @ref          
* @author       
* @note         
**/
void User_UART_RxCpltCallback(void){

if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE) != RESET){
    usbStr.receiveFinished = false;
    HAL_StatusTypeDef Uart1Res;
    uint8_t recvbuf = 0;
    Uart1Res = HAL_UART_Receive_DMA(&huart1,(uint8_t*)&recvbuf,1);
    if(Uart1Res ==  HAL_OK){
        //检测帧头
        if(recvbuf == USB_FRAME_HEAD && !usbStr.receiveStart){
            usbStr.receiveStart = true;
            usbStr.receiveBuff[0] = Uart1Res;
            usbStr.receiveIndex = 1;
        }
        else if(usbStr.receiveIndex == 2){	//接收帧长度
            usbStr.receiveBuff[usbStr.receiveIndex] = Uart1Res;
            usbStr.receiveIndex++;
            
            if(Uart1Res > USB_FRAME_LENMAX || Uart1Res < USB_FRAME_LENMIN){//帧长错误
                usbStr.receiveIndex = 0;
                usbStr.receiveStart = false;
            }
        }
        else if(usbStr.receiveStart && usbStr.receiveIndex < USB_FRAME_LENMAX){
            usbStr.receiveBuff[usbStr.receiveIndex] = Uart1Res;
            usbStr.receiveIndex++;
        }
    }
    //接收完毕
    if(usbStr.receiveIndex == USB_FRAME_OK){
        uint8_t check = 0;
        uint8_t length = USB_FRAME_LENMIN;

    //校验
        length = USB_FRAME_OK;
        for(int i=0;i<length-1;i++) check += usbStr.receiveBuff[i];
        //校验OK
        if(check == usbStr.receiveBuff[usbStr.receiveIndex]){
            memcpy(usbStr.receiveBuffFinished,usbStr.receiveBuff,USB_FRAME_LENMAX);	
            usbStr.receiveFinished = true;
            uint32_t motor1 = (uint32_t)usbStr.receiveBuffFinished[1];
            uint32_t motor2 = (uint32_t)usbStr.receiveBuffFinished[2];
            MOTOR_Set(motor1,motor2);
            Bint16_Union bint16_Union;
            bint16_Union.U8_Buff[0] = usbStr.receiveBuffFinished[3];
            bint16_Union.U8_Buff[1] = usbStr.receiveBuffFinished[4];
            signed int servo = (signed int)(bint16_Union.U16);
            SERVO_SetPwmValueCorrect(servo);
        }
        
        usbStr.receiveIndex = 0;
    } 
    }
    usbStr.receiveFinished = true;
}

