/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
#include "stm32l0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usr_general.h"

#define _POWER_BUTTON_IRQ             EXTI->PR & EXTI_PR_PIF0              //EXTI->PR &EXTI_PR_PIF0
#define _POWER_PIN_0()                HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)
#define _POWER_PIN_1()                HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)
#define _POWER_BUTTON_ICLR()          EXTI->PR |= EXTI_PR_PIF0

#define _BUTTON_PRESS_STATE           1

extern uint8_t g_button1PressedOkFlg1;
extern uint8_t g_button2PressedOkFlg2;

extern uint8_t g_pressedOccuredFlg1;
extern uint8_t g_pressedOccuredFlg2;

extern uint32_t g_button1PressedTimeCnt;
extern uint32_t g_button2PressedTimeCnt;

extern S_INITIAL_VALUE m_sInitialParameter;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles RCC and CRS global interrupt.
  */
void RCC_CRS_IRQHandler(void)
{
  /* USER CODE BEGIN RCC_CRS_IRQn 0 */

  /* USER CODE END RCC_CRS_IRQn 0 */
  /* USER CODE BEGIN RCC_CRS_IRQn 1 */

  /* USER CODE END RCC_CRS_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 0 and line 1 interrupts.
  */
void EXTI0_1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_1_IRQn 0 */
  if(EXTI->PR & EXTI_PR_PIF0)
  {
    if(HAL_GPIO_ReadPin(m_sInitialParameter.pButton1Port, m_sInitialParameter.button1Pin) == g_button1PressedOkFlg1)
    {
      g_pressedOccuredFlg1 = 1;
    }
    else
    {
      g_pressedOccuredFlg1 = 0;
    }
    EXTI->PR |= EXTI_PR_PIF0;
  }
  
  if(EXTI->PR & EXTI_PR_PIF1)
  {
    if(HAL_GPIO_ReadPin(m_sInitialParameter.pButton2Port, m_sInitialParameter.button2Pin) == g_button2PressedOkFlg2)
    {
      g_pressedOccuredFlg2 = 1;
    }
    else
    {
      g_pressedOccuredFlg2 = 0;
    }
    EXTI->PR |= EXTI_PR_PIF1;
  }

  /* USER CODE END EXTI0_1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI0_1_IRQn 1 */

  /* USER CODE END EXTI0_1_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM2)
  {
    if(g_pressedOccuredFlg1)
    { 
      g_button1PressedTimeCnt++;
      if(g_button1PressedTimeCnt >= 50)
      {
        g_button1PressedOkFlg1 = 1;
        g_pressedOccuredFlg1 = 0;
      }
    }
    else
    {
      g_button1PressedTimeCnt = 0;
    }


    if(g_pressedOccuredFlg2)
    {
      g_button2PressedTimeCnt++;
      if(g_button2PressedTimeCnt >= 50)
      {
        g_button2PressedOkFlg2 = 1;
        g_pressedOccuredFlg2 = 0; 
      }
    }
    else
    {
      g_button2PressedTimeCnt = 0;
    }
  }
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
