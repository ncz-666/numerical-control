
#include "../Drivers/SYSTEM/sys/sys.h"
#include "../Drivers/BSP/PWM/pwm.h"
#include "../Drivers/BSP/KEY/key.h"
#include "../Drivers/BSP/OLED/OLED.h"  
int main(void)
{
    HAL_Init();
        sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */

//    SystemClock_Config();   // 你工程里可能叫别的名，按你项目一的来
    tim3_init();         // 启动PWM，占空比50%
//    PWM_Init();
    key_init();
    OLED_Init();
OLED_Clear();
OLED_ShowString(0, 0, "Duty:", OLED_8X16);
    
//    uint8_t key=key_scan(0);
    uint16_t  tip=500;
//    
//    while(1)
//    {
//        uint8_t key=key_scan(0);
////        uint16_t  tip=500;
//        if(key==1){
//          if(tip<1000){
//              tip=tip+100;
//          }
//        }
//        else if(key==2){
//            if(tip >= 100){
//              tip=tip-100;
//            }
//        }
//        __HAL_TIM_SET_COMPARE(&tim3, TIM_CHANNEL_1, tip); 
//        
//    OLED_ShowNum(56, 0, tip / 10, 3, OLED_8X16);   // 显示占空比百分数
//    OLED_ShowFloatNum(0, 2, tip / 1000.0f * 3.3f, 1, 2, OLED_8X16);  // 显示平均电压
//    OLED_Update();
//    }
float v_target = 3.2f;    /* 目标电压 */

while (1)
{
    uint8_t key = key_scan(0);
    if (key == 1) {
        if (v_target < 3.2f)  v_target += 0.1f;   /* 上限3.2 */
    }
    else if (key == 2) {
if (v_target > 2.75f)  v_target -= 0.1f;
    }

uint16_t duty = (uint16_t)((3.714f - v_target) / 0.000971f + 0.5f);
    __HAL_TIM_SET_COMPARE(&tim3, TIM_CHANNEL_1, duty);

    OLED_ShowString(0, 0, "Set:", OLED_8X16);
    OLED_ShowFloatNum(40, 0, v_target, 1, 2, OLED_8X16);
    OLED_Update();
}

}


