#include "my_motor.h"

MotorStruct motorStr;

void MOTOR_Init(void){
    // Initialize GPIO pins for motor control
    MOTOR_Set(0, 0);

    //电机模型初始化
    motorStr.EncoderLine = 512.0f; 							//编码器线数=光栅数16*4				
    motorStr.ReductionRatio = 2.7f;							//电机减速比								
    motorStr.DiameterWheel = 0.064f;//64cm					//轮子直径:m
   // motorStr.CloseLoop = true;                              //默认闭环模式
}

/**
* @brief        电机输出PWM设置
* @param        pwm：MOTOR_MOTOR_PWM_MIN - MOTOR_MOTOR_PWM_MAX
* @ref          
* @author       
* @note         
**/
void MOTOR_Set(int Motor1,int Motor2){

    if(Motor1 <0)
	{
		if(Motor1 <MOTOR_PWM_MIN - 1) Motor1 =MOTOR_PWM_MIN - 1;
        HAL_GPIO_WritePin(Motor1_dir_GPIO_Port, Motor1_dir_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, (100+Motor1));
	}
	else 
	{
		if(Motor1 >MOTOR_PWM_MAX - 1) Motor1 = MOTOR_PWM_MAX - 1;
        HAL_GPIO_WritePin(Motor1_dir_GPIO_Port, Motor1_dir_Pin, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1,Motor1);
	}

	if(Motor2<0)
	{
        if(Motor2 <MOTOR_PWM_MIN - 1) Motor2=MOTOR_PWM_MIN - 1;
        HAL_GPIO_WritePin(Motor2_dir_GPIO_Port, Motor2_dir_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, (100+Motor2));
	}
	else
	{
        if(Motor2 >MOTOR_PWM_MAX - 1) Motor2 =MOTOR_PWM_MAX - 1;
        HAL_GPIO_WritePin(Motor2_dir_GPIO_Port, Motor2_dir_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, Motor2);
	}
}


/**
* @brief        电机闭环速控
* @param        speed：速度m/s
* @ref          
* @author         
* @note         
**/
/*
void MOTOR_ControlLoop(float speed)
{	
    if(speed > MOTOR_SPEED_MAX)
        speed = MOTOR_SPEED_MAX;
    else if(speed < -MOTOR_SPEED_MAX)
        speed = -MOTOR_SPEED_MAX;
    
    pidStr.vi_Ref = (float)(speed*MOTOR_CONTROL_CYCLE / motorStr.DiameterWheel / PI * motorStr.EncoderLine * 4.0f * motorStr.ReductionRatio);
    
    MOTOR_SetPwmValue(PID_MoveCalculate(&pidStr));
}*/


/**
* @brief        电机控制线程
* @param        
* @ref          
* @author       Leo
* @note         
**/
/*
void MOTOR_Timer(void)
{
    motorStr.Counter++;
    if(motorStr.Counter >= 10)							    //速控:10ms
    {
        ENCODER_RevSample();								//编码器采样

        if(icarStr.sprintEnable || usbStr.connected)        //通信连接或电机测试才开启闭环（保护+省电）
        {
            if(motorStr.CloseLoop)
            {
                MOTOR_ControlLoop(icarStr.SpeedSet);		//闭环速控
            }
            else//开环百分比控制
            {
                if(icarStr.SpeedSet > 100)
                    icarStr.SpeedSet = 100;
                else if(icarStr.SpeedSet < -100)
                    icarStr.SpeedSet = -100;
                signed int speedRate = MOTOR_PWM_MAX/100.f*icarStr.SpeedSet; //开环：百分比%
                
                MOTOR_SetPwmValue(speedRate);		//开环速控
            }
        }
        else
        {
            MOTOR_SetPwmValue(0);
        }
       
        motorStr.Counter = 0;
    }
}*/