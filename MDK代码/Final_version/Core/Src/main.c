/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "smg.h"
#include "delay.h"
#include "motor.h"
#include "ultrasonic.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// �ṹ�嶨��
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// ����
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// �궨��
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// ˽�б���
static uint8_t LEFT_SENSOR = 0;
static uint8_t MIDDLE_SENSOR = 0;
static uint8_t RIGHT_SENSOR = 0;

static uint8_t Main_switch = 0;
static uint8_t Speed_gear = 0;
static uint8_t horn = 0;
static uint8_t Forward_key = 0;
static uint8_t Backward_key = 0;
static uint8_t Left_key = 0;
static uint8_t Right_key = 0;

extern uint8_t smg_num[];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
// ˽�к���ԭ��
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t distance;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	SMG_Init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	Ultrasonic_Init();
		/*	�������������ߣ����죩*/
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_Delay(30);
		CAR_STOP();
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);
		/*	ģʽ	*/
		if(HAL_GPIO_ReadPin(Main_switch_GPIO_Port,Main_switch_Pin)==GPIO_PIN_SET)
			Main_switch = 1;
		else
		{
			Main_switch = 0;
		}
		
		/*	ң�ؿ��ش򿪣�ʹ��С����&8266����	*/
		if(Main_switch)
		{
			/* ʶ������״̬	*/
			if(HAL_GPIO_ReadPin(Speed_gear_GPIO_Port,Speed_gear_Pin)==GPIO_PIN_SET)
				Speed_gear = 1;
			else
				Speed_gear = 0;
			if(HAL_GPIO_ReadPin(Forward_key_GPIO_Port,Forward_key_Pin)==GPIO_PIN_SET)
				Forward_key = 1;
			else
				Forward_key = 0;
			if(HAL_GPIO_ReadPin(Backward_key_GPIO_Port,Backward_key_Pin)==GPIO_PIN_SET)
				Backward_key = 1;
			else
				Backward_key = 0;
			if(HAL_GPIO_ReadPin(Left_key_GPIO_Port,Left_key_Pin)==GPIO_PIN_SET)
				Left_key = 1;
			else
				Left_key = 0;
			if(HAL_GPIO_ReadPin(Right_key_GPIO_Port,Right_key_Pin)==GPIO_PIN_SET)
				Right_key = 1;
			else
				Right_key = 0;
			
			/*	״̬����		*/
			if(Forward_key)
			{
				/*
					* Speed_gear = 1:����ǰ��
					*
					*
				*/
				if(Speed_gear)
				{
					LEFT_WHEEL_CTRL(HIGH_SPEED,NONE_SPEED);
					RIGHT_WHEEL_CTRL(HIGH_SPEED,NONE_SPEED);
				}
				else
				{
					LEFT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
					RIGHT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
				}
			}
			if(Backward_key)
			{
				/*
					* Speed_gear = 1:���ٵ���
					*
					*
				*/
				if(Speed_gear)
				{
					LEFT_WHEEL_CTRL(NONE_SPEED,HIGH_SPEED);
					RIGHT_WHEEL_CTRL(NONE_SPEED,HIGH_SPEED);
				}
				else   
				{
					LEFT_WHEEL_CTRL(NONE_SPEED,MIDDLE_SPEED);
					RIGHT_WHEEL_CTRL(NONE_SPEED,MIDDLE_SPEED);
				}
			}
			if(Left_key)
			{
				/*�������ǰ�������*/
				if(Forward_key || Backward_key)
				{
					if(Speed_gear)
					{
						LEFT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
					}
					else
					{
						LEFT_WHEEL_CTRL(LOW_SPEED,NONE_SPEED);
					}
				}
				else
					/*ԭ��ת��*/
				{
					LEFT_WHEEL_CTRL(NONE_SPEED,NONE_SPEED);
					RIGHT_WHEEL_CTRL(LOW_SPEED,NONE_SPEED);
				}
			}
			if(Right_key)
			{
				/*�������ǰ�������*/
				if(Forward_key || Backward_key)
				{
					if(Speed_gear)
					{
						RIGHT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
					}
					else
					{
						RIGHT_WHEEL_CTRL(LOW_SPEED,NONE_SPEED);
					}
				}
				else
					/*ԭ��ת��*/
				{
					LEFT_WHEEL_CTRL(LOW_SPEED,NONE_SPEED);
					RIGHT_WHEEL_CTRL(NONE_SPEED,NONE_SPEED);
				}
			}
		}
		else
		{
			/*	ѭ��ģʽ	*/
				/*	״̬����		*/
			//HAL_Delay(150);
			LEFT_SENSOR = 0;
			MIDDLE_SENSOR = 0;
			RIGHT_SENSOR = 0;
			
				/*	״̬�ж�		*/
			if(HAL_GPIO_ReadPin(IN1_GPIO_Port,IN1_Pin) == SET)
			{
				HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);
				RIGHT_SENSOR = 1;
			}
			if(HAL_GPIO_ReadPin(IN2_GPIO_Port,IN2_Pin) == SET)
			{
				HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
				MIDDLE_SENSOR = 1;
			}
			if(HAL_GPIO_ReadPin(IN3_GPIO_Port,IN3_Pin) == SET)
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
				LEFT_SENSOR = 1;
			}
			
				/*	��������ʾ����	*/
			distance = Measure_distance();
			LED_Display(distance);
			if(distance <= 200)
			{
				HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin,GPIO_PIN_RESET);
				continue;
			}
			else
			{
				HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin,GPIO_PIN_SET);
			}
				/*	���⴫�����¼�����		*/
			if(LEFT_SENSOR && MIDDLE_SENSOR && RIGHT_SENSOR)
			{
				/*	
					* ȫ������
					* =>ʮ�� | T�� | ����
					* ==>����������ʻ
				*/
				LOW_SPEED_RUN();
				continue;
			}
			if(LEFT_SENSOR && MIDDLE_SENSOR)
			{
				/*	
					* ���д�����
					* =>��� | ��ֱ��
					* ==>���ֵ��ٺ��ˣ����ֵ��ٵ�������
				*/
				LEFT_WHEEL_CTRL(NONE_SPEED,LOW_SPEED);
				RIGHT_WHEEL_CTRL(LOW_SPEED,NONE_SPEED);
				continue;
			}
			if(MIDDLE_SENSOR && RIGHT_SENSOR)
			{
				/*	
					* ���Ҵ�����
					* =>��� | ��ֱ��
					* ==>���ֵ��ٵ����������ֵ��ٺ���
				*/
				LEFT_WHEEL_CTRL(LOW_SPEED,NONE_SPEED);
				RIGHT_WHEEL_CTRL(NONE_SPEED,LOW_SPEED);
				continue;
			}
			if(LEFT_SENSOR && RIGHT_SENSOR)
			{
				/*	
					* ���Ҵ�����
					* =>����·��
					* ==>���ֵ��ٺ��ˣ��������ٵ����������������ߣ�
				*/
				LEFT_WHEEL_CTRL(NONE_SPEED,LOW_SPEED);
				RIGHT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
				continue;
			}
			if(LEFT_SENSOR)
			{
				/*	
					* �󴥺���
					* =>���������ƫ
					* ==>���ֵ��ٺ��ˣ��������ٵ�������
				*/
				LEFT_WHEEL_CTRL(NONE_SPEED,LOW_SPEED);
				RIGHT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
				continue;
			}
			if(MIDDLE_SENSOR)
			{
				/*	
					* �д�����
					* =>ֱ��
					* ==>���ֵ���ǰ��
				*/
				LOW_SPEED_RUN();
				continue;
			}
			if(RIGHT_SENSOR)
			{
				/*	
					* �Ҵ�����
					* =>���������ƫ
					* ==>�������ٵ����������ֵ��ٺ���
				*/
				LEFT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
				RIGHT_WHEEL_CTRL(NONE_SPEED,LOW_SPEED);
				continue;
			}
			if(LEFT_SENSOR == 0 && MIDDLE_SENSOR == 0 && RIGHT_SENSOR == 0)
			{
				/*	
					* ȫ���źŶ�ʧ
					* =>T�� | ���
					* ==>�������ٵ��������������ٺ���
				*/
				LEFT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
				RIGHT_WHEEL_CTRL(NONE_SPEED,MIDDLE_SPEED);
				continue;
			}
		}
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// �����źŻص�����
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == horn_Pin)
	{
		HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin,GPIO_PIN_RESET); //BEEP�������ͣ��죬 ��ͬBEEP=0;
        HAL_Delay(600);       
		HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin,GPIO_PIN_SET);   //BEEP�������ߣ����죬��ͬBEEP=1;
        HAL_Delay(600);		
		HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin,GPIO_PIN_RESET); //BEEP�������ͣ��죬 ��ͬBEEP=0;
        HAL_Delay(600);       
		HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin,GPIO_PIN_SET);   //BEEP�������ߣ����죬��ͬBEEP=1;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
