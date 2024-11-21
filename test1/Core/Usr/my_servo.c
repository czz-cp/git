#include "my_servo.h"

ServoStruct servoStr;
/**
* @brief        舵机init
* @param        
* @ref          
* @author       
* @note         
**/
void SERVO_Init(void){
    SERVO_SetPwmValue(servoStr.thresholdMiddle);
}


/**
* @brief        舵机输出PWM设置（矫正后）
* @param        pwm:SERVO_PWM_MIN - SERVO_PWM_MAX
* @ref          
* @author       
* @note         
**/
uint16_t pwm_Servo = 0;
void SERVO_SetPwmValueCorrect(signed int pwm){   
    pwm = 3000 - pwm;  //左→右
    
    pwm -= servoStr.thresholdMiddle-SERVO_PWM_MIDDLE; //中值补偿
	
	uint16_t pwmMax = 3000 - servoStr.thresholdLeft;
	uint16_t pwmMin = 3000 - servoStr.thresholdRight;
	if(pwm < pwmMin)
        pwm = pwmMin;
    else if(pwm > pwmMax)
        pwm = pwmMax;
	
	pwm_Servo = pwm;
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
}

/**
* @brief        舵机输出PWM设置
* @param        pwm：-20000~20000
* @ref          
* @author       Leo
* @note         
**/
void SERVO_SetPwmValue(signed int pwm)
{   
    pwm = 3000 - pwm;  //左→右
        
    if(pwm < SERVO_PWM_MIN)
        pwm = SERVO_PWM_MIN;
    else if(pwm > SERVO_PWM_MAX)
        pwm = SERVO_PWM_MAX;
 
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
}

/**
* @brief       舵机角度控制 
* @param        
* @ref          
* @author       
* @note         
**/
/*uint16_t ServoPwm = 1500;
void SERVO_AngleControl(float angle)
{
	uint16_t pwm = 1500;
	angle = -angle;
	if(angle > SERVO_ANGLE_MAX)
		angle = SERVO_ANGLE_MAX;
	else if(angle < -SERVO_ANGLE_MAX)
		angle = -SERVO_ANGLE_MAX;
	
	if(angle >= 0)  //右转
		pwm = (float)angle/SERVO_ANGLE_MAX * (SERVO_PWM_MAX_R-servoStr.thresholdMiddle) + servoStr.thresholdMiddle;		//绝对角度计算
	else if(angle < 0)  	//左转
		pwm = (float)angle/SERVO_ANGLE_MAX * (servoStr.thresholdMiddle - SERVO_PWM_MAX_L) + servoStr.thresholdMiddle;		//绝对角度计算
	
	ServoPwm = pwm;
	SERVO_SetPwmValue(pwm);
}*/