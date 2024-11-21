#include "my_timer.h"

//1ms
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim->Instance == TIM2){
        CENODER_RevSample();
        USB_Transmit_To();
    }
}

