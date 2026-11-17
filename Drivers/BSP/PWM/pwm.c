#include "../Drivers/BSP/PWM/pwm.h"
TIM_HandleTypeDef tim3;
void tim3_init(void){
    __HAL_RCC_TIM3_CLK_ENABLE();  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /* 配置PA6为复用推挽，让TIM3接管 */
    GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.Pin   = GPIO_PIN_6;      /* PA6 */
    gpio_init_struct.Mode  = GPIO_MODE_AF_PP; /* 复用推挽：由定时器控制，不是普通IO */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);

    
    tim3.Instance=TIM3;
    tim3.Init.Prescaler=72-1;
    tim3.Init.Period=1000-1;
    tim3.Init.CounterMode=TIM_COUNTERMODE_UP;
    tim3.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&tim3);

    TIM_OC_InitTypeDef tim3_oc;
    tim3_oc.OCMode=TIM_OCMODE_PWM1;
    tim3_oc.Pulse=700;
    tim3_oc.OCPolarity=TIM_OCPOLARITY_HIGH;
    tim3_oc.OCFastMode=TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&tim3, &tim3_oc, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&tim3, TIM_CHANNEL_1);
}
//    
//TIM_HandleTypeDef htim3;   /* 全局句柄 */

//void PWM_Init(void)
//{
//    /* 第1步：开时钟（你已写） */
//    __HAL_RCC_TIM3_CLK_ENABLE();
//    __HAL_RCC_GPIOA_CLK_ENABLE();

//    /* 第2步：PA6复用推挽 */
//    GPIO_InitTypeDef gpio_init_struct;
//    gpio_init_struct.Pin   = GPIO_PIN_6;
//    gpio_init_struct.Mode  = GPIO_MODE_AF_PP;
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(GPIOA, &gpio_init_struct);

//    /* 第3步：TIM3配置1kHz */
//    htim3.Instance = TIM3;
//    htim3.Init.Prescaler     = 72 - 1;
//    htim3.Init.Period        = 1000 - 1;
//    htim3.Init.CounterMode   = TIM_COUNTERMODE_UP;
//    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//    HAL_TIM_PWM_Init(&htim3);

//    /* 第4步：通道1占空比50% + 启动 */
//    TIM_OC_InitTypeDef oc_init_struct;
//    oc_init_struct.OCMode     = TIM_OCMODE_PWM1;
//    oc_init_struct.Pulse      = 500;
//    oc_init_struct.OCPolarity = TIM_OCPOLARITY_HIGH;
//    oc_init_struct.OCFastMode = TIM_OCFAST_DISABLE;
//    HAL_TIM_PWM_ConfigChannel(&htim3, &oc_init_struct, TIM_CHANNEL_1);
//    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
//}


