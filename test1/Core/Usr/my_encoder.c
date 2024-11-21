#include "my_encoder.h"

EncoderStruct encoderStr;

void ENCODER_Init(void){
    //模型初始化
    encoderStr.EncoderValue1 = 0;
    encoderStr.EncoderValue2 = 0;
    //encoderStr.MotorSpeed1  = 0;
    //encoderStr.MotorSpeed2 = 0;
}

void ENCODER_RevSample(void) {
    encoderStr.EncoderValue1 = __HAL_TIM_GetCounter(&htim1);
    TIM1->CNT = 0;
    if(encoderStr.EncoderValue1 > 2499) encoderStr.EncoderValue1 = 4999 - encoderStr.EncoderValue1;
    encoderStr.EncoderValue2 = __HAL_TIM_GetCounter(&htim2);
    TIM2->CNT = 0;
    if(encoderStr.EncoderValue2 > 2499) encoderStr.EncoderValue2 = 4999 - encoderStr.EncoderValue2;
}