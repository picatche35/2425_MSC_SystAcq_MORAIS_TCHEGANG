/*
 * motor.c
 *
 *  Created on: Nov 21, 2024
 *      Author: eugen
 */
/**
 * @file	: motor.c
 * @brief	: Motor control
 */

#include "motor.h"
#include "main.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim1;
extern ADC_HandleTypeDef hadc1;
extern uint8_t uartTxBuffer[UART_TX_BUFFER_SIZE];
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_adc1;

motor_t motor;

void motor_speed(int speed)
{
	if (speed > 8499)
	{
		speed = 8499;
	}
	if (speed < 0)
	{
		speed = 0;
	}

	motor.speed = speed;

	if(motor.last_speed < motor.speed)
	{
		for(int i=motor.last_speed; i<=motor.speed; i++)
		{
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, i);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 8499-i);
			HAL_Delay(2);
		}
	}
	else if(motor.last_speed > motor.speed)
	{
		for(int i=motor.last_speed; i>=motor.speed; i--)
		{
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, i);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 8499-i);
			HAL_Delay(2);
		}
	}

	motor.last_speed = motor.speed;

}

void motor_on()
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
}

void motor_off()
{
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);

	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
}

void motor_start()
{
	/** Règle le rapport cyclique à 50% **/
	motor_on();
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 4250);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 4250);
	motor.last_speed = 4250;
}

void measure_current()
{
	/** Récupère la valeur du courant sur l'adc 1 **/
	HAL_DMA_Start_IT(&hdma_adc1, SrcAddress, DstAddress, 32);
	HAL_ADC_Start(&hadc1);
	float current = HAL_ADC_GetValue(&hadc1);
	/** Sensitivity S = 50 mV/A **/
	/**
	 * @brief Tension d'alimentation de la carte = 3.3V
	 * @brief Résolution 12 bits = 4096 valeurs
	 * @brief Offset = 1.65 V
	 */
	current = (current*3.3)/4096;
	current = (current-1.65)/0.05;

	sprintf(uartTxBuffer, "Current : %f A\r\n", current);
	HAL_UART_Transmit(&huart2, uartTxBuffer, sizeof(uartTxBuffer), HAL_MAX_DELAY);

}
