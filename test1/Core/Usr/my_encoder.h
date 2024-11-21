#ifndef __MY_ENCODER_H
#define __MY_ENCODER_H

#include "main.h"
/*
#define Encoder1_dir_Pin GPIO_PIN_11
#define Encoder1_dir_GPIO_Port GPIOC
#define Encoder2_dir_Pin GPIO_PIN_12
#define Encoder2_dir_GPIO_Port GPIOC
E1:tim1_ch1_gpioe9
E2:tim2_ch1_gpioa15
*/

typedef struct 
{
    signed int EncoderValue1;				    //编码器1实时速度
    signed int EncoderValue2;				    //编码器2实时速度
    //float MotorSpeed1;                          //电机1速度
    //float MotorSpeed2;                          //电机2速度
}EncoderStruct;

extern EncoderStruct encoderStr;

void ENCODER_Init(void);
void ENCODER_RevSample(void);

#endif