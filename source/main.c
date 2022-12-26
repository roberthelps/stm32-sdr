/*============================================================================*/

/*============================================================================*/
#include "stm32f1xx_hal.h"
#include "system_stm32f1xx.h"
#include "si5351.h"

/*----------------------------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/*----------------------------------------------------------------------------*/
static void Error_Handler(void)
{
	while (1);
}

/*----------------------------------------------------------------------------*/
static void I2C1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_RCC_AFIO_CLK_ENABLE();

	__HAL_RCC_GPIOB_CLK_ENABLE();

	/**I2C1 GPIO Configuration    
	PB8     ------> I2C1_SCL
	PB9     ------> I2C1_SDA 
	*/
	GPIO_InitStruct.Pin   = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode  = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	__HAL_AFIO_REMAP_I2C1_ENABLE();

	__HAL_RCC_I2C1_CLK_ENABLE();


	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		Error_Handler();
	}
}

/*----------------------------------------------------------------------------*/
static void GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// PC.13 - LED
	GPIO_InitStruct.Pin   = GPIO_PIN_13;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

/*----------------------------------------------------------------------------*/
static void si5351_init(void)
{
	const int32_t correction = 10000;//978;
	si5351_Init(correction);

//	si5351_SetupCLK0(28000000, SI5351_DRIVE_STRENGTH_4MA);
//	si5351_SetupCLK2(144000000, SI5351_DRIVE_STRENGTH_4MA);

	si5351PLLConfig_t pll_conf;
	si5351OutputConfig_t out_conf;

	si5351_CalcIQ(100e6, &pll_conf, &out_conf);
	si5351_SetupOutput(0, SI5351_PLL_A, SI5351_DRIVE_STRENGTH_4MA, &out_conf, 0);
	si5351_SetupOutput(1, SI5351_PLL_A, SI5351_DRIVE_STRENGTH_4MA, &out_conf, out_conf.div);
	si5351_SetupPLL(SI5351_PLL_A, &pll_conf);

	si5351_EnableOutputs((1 << 0) | (1 << 1));
}


/*----------------------------------------------------------------------------*/
void main(void)
{
	SystemCoreClockUpdate();
	HAL_Init();

	I2C1_Init();
	GPIO_Init();

	si5351_init();
	uint32_t timeout = 0;

	while(1) {

		if (uwTick > timeout) {
			timeout = uwTick + 1000;
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}
	}
}

/*----------------------------------------------------------------------------*/