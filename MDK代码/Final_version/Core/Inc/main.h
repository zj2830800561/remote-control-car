/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Forward_key_Pin GPIO_PIN_13
#define Forward_key_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_2
#define LED3_GPIO_Port GPIOC
#define LED4_Pin GPIO_PIN_3
#define LED4_GPIO_Port GPIOC
#define Right_key_Pin GPIO_PIN_6
#define Right_key_GPIO_Port GPIOA
#define Left_key_Pin GPIO_PIN_7
#define Left_key_GPIO_Port GPIOA
#define horn_Pin GPIO_PIN_2
#define horn_GPIO_Port GPIOB
#define horn_EXTI_IRQn EXTI2_IRQn
#define Backward_key_Pin GPIO_PIN_10
#define Backward_key_GPIO_Port GPIOB
#define IN1_Pin GPIO_PIN_8
#define IN1_GPIO_Port GPIOC
#define IN2_Pin GPIO_PIN_9
#define IN2_GPIO_Port GPIOC
#define IN3_Pin GPIO_PIN_8
#define IN3_GPIO_Port GPIOA
#define echo_Pin GPIO_PIN_9
#define echo_GPIO_Port GPIOA
#define trig_Pin GPIO_PIN_10
#define trig_GPIO_Port GPIOA
#define IN4_Pin GPIO_PIN_15
#define IN4_GPIO_Port GPIOA
#define Speed_gear_Pin GPIO_PIN_2
#define Speed_gear_GPIO_Port GPIOD
#define Beep_Pin GPIO_PIN_8
#define Beep_GPIO_Port GPIOB
#define Main_switch_Pin GPIO_PIN_9
#define Main_switch_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
