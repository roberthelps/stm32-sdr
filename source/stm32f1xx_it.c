/*----------------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/*----------------------------------------------------------------------------*/
void NMI_Handler(void)
{
}

/*----------------------------------------------------------------------------*/
void HardFault_Handler(void)
{
	while (1);
}

/*----------------------------------------------------------------------------*/
void MemManage_Handler(void)
{
	while (1);
}

/*----------------------------------------------------------------------------*/
void BusFault_Handler(void)
{
	while (1);
}

/*----------------------------------------------------------------------------*/
void UsageFault_Handler(void)
{
	while (1);
}

/*----------------------------------------------------------------------------*/
void SVC_Handler(void)
{
}

/*----------------------------------------------------------------------------*/
void DebugMon_Handler(void)
{
}

/*----------------------------------------------------------------------------*/
void PendSV_Handler(void)
{
}

/*----------------------------------------------------------------------------*/
void SysTick_Handler(void)
{
	HAL_IncTick();
}

/******************************************************************************/
/*                 STM32F1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f1xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles external lines 10 to 15 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
//  HAL_GPIO_EXTI_IRQHandler(USER_BUTTON_PIN);
}


/**
  * @brief  This function handles ADC interrupt request.
  * @param  None
  * @retval None
  */
void ADCx_IRQHandler(void)
{
//  HAL_ADC_IRQHandler(&AdcHandle);
}

/**
* @brief  This function handles DMA interrupt request.
* @param  None
* @retval None
*/
void ADCx_DMA_IRQHandler(void)
{
//  HAL_DMA_IRQHandler(AdcHandle.DMA_Handle);
}


