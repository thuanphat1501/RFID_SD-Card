#include "servo.h"

/* TIM2 Configuration for PWM */
void TIM2_Config(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    /* Enable TIM2 and GPIOA clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* Configure GPIOA Pin 0 as Alternate Function Push Pull */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* TIM2 Configuration */
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;           // 20 ms period (50 Hz)
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;           // Prescaler value to get 1 MHz timer clock
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1000;                   // Default pulse width
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    /* Enable TIM2 Preload register on CCR1 */
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

    /* Enable TIM2 counter */
    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_PWM_Config(uint16_t pulse) {
    /* Set the Capture Compare Register value */
    TIM_SetCompare1(TIM2, pulse);
}

/* Delay function */
void Delay(uint32_t milliseconds) {
    uint32_t delay = milliseconds * 1000;
    while (delay--) {
        __NOP();
    }
}

void MoveServoTo90Degrees(void) {
    uint16_t initialPulse = 1000; // 1ms pulse width (0 degrees)
    uint16_t finalPulse = 2000;   // 2ms pulse width (180 degrees)
    uint16_t targetPulse = 1500;  // 1.5ms pulse width (90 degrees)
    uint16_t steps = 50;
    uint16_t stepDelay = 10;      // Total delay will be steps * stepDelay = 500ms
    uint16_t stepSize = (targetPulse - initialPulse) / steps;

    for (uint16_t pulse = initialPulse; pulse <= targetPulse; pulse += stepSize) {
        TIM2_PWM_Config(pulse);
        Delay(stepDelay);
    }
}

void MoveServoBackTo0Degrees(void) {
    uint16_t targetPulse = 1000; // 1ms pulse width (0 degrees)
    uint16_t initialPulse = 1500; // 1.5ms pulse width (90 degrees)
    uint16_t steps = 50;
    uint16_t stepDelay = 10;      // Total delay will be steps * stepDelay = 500ms
    uint16_t stepSize = (initialPulse - targetPulse) / steps;

    for (uint16_t pulse = initialPulse; pulse >= targetPulse; pulse -= stepSize) {
        TIM2_PWM_Config(pulse);
        Delay(stepDelay);
    }
}

void MoveServoTo180Degrees(void) {
    uint16_t initialPulse = 1000; // 1ms pulse width (0 degrees)
    uint16_t finalPulse = 2000;   // 2ms pulse width (180 degrees)
    uint16_t steps = 50;
    uint16_t stepDelay = 10;      // Total delay will be steps * stepDelay = 500ms
    uint16_t stepSize = (finalPulse - initialPulse) / steps;

    for (uint16_t pulse = initialPulse; pulse <= finalPulse; pulse += stepSize) {
        TIM2_PWM_Config(pulse);
        Delay(stepDelay);
    }
}
