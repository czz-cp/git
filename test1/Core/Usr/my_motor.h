#ifndef __MY_MOTOR_H
#define __MY_MOTOR_H

#include "main.h"

/* 定义在main.h中，不用重复定义
#define Motor1_dir_Pin GPIO_PIN_14
#define Motor1_dir_GPIO_Port GPIOD
#define Motor2_dir_Pin GPIO_PIN_15
#define Motor2_dir_GPIO_Port GPIOD
*/

#define MOTOR_PWM_MAX               160
#define MOTOR_PWM_MIN               -160
#define MOTOR_SPEED_MAX		        10.0f	 	//电机最大转速(m/s) (0.017,8.04)
#define PI					        3.141593f   //π
#define MOTOR_CONTROL_CYCLE	        0.01f    	//电机控制周期T：10ms

typedef struct 
{
	float ReductionRatio ;					    //电机减速比
	float EncoderLine ; 						//编码器线数=光栅数16*4
	float DiameterWheel;						//轮子直径：mm
	bool CloseLoop;							    //开环模式
	uint16_t Counter;							//线程计数器
}MotorStruct;

extern MotorStruct motorStr;

void MOTOR_Init(void);
void MOTOR_Set(int Motor1,int Motor2);
//void MOTOR_ControlLoop(float speed);
//void MOTOR_Timer(void);

#endif