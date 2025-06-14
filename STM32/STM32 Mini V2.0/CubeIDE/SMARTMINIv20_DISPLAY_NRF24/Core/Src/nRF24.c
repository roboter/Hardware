/*
 * nRF24.c
 *
 *  Created on: Jun 21, 2023
 *      Author: singularengineer
 */
#include "main.h"

#include "nRF24.h"

nRF24Def *NRFmodule;
uint32_t ticker = 0;

void NRF_Init(nRF24Def *nrf)
{
    NRFmodule = nrf;

    CE_LOW();
    CSn_HIGH();
}

void CSn_LOW()
{
	Delay_us(500);
    HAL_GPIO_WritePin(NRFmodule->CSn_Port, NRFmodule->CSn_Pin, GPIO_PIN_RESET);
    Delay_us(500);
}

void CSn_HIGH()
{
	Delay_us(500);
	HAL_GPIO_WritePin(NRFmodule->CSn_Port, NRFmodule->CSn_Pin, GPIO_PIN_SET);
	Delay_us(500);
}

void CE_LOW()
{
	Delay_us(500);
	HAL_GPIO_WritePin(NRFmodule->CE_Port, NRFmodule->CEn_Pin, GPIO_PIN_RESET);
	Delay_us(500);
}

void CE_HIGH()
{
	Delay_us(500);
	HAL_GPIO_WritePin(NRFmodule->CE_Port, NRFmodule->CEn_Pin, GPIO_PIN_SET);
	Delay_us(500);
}

uint8_t ReadReg(uint8_t reg)
{
	reg |= R_REGISTER;
	uint8_t val = 0;

    CSn_LOW();
    HAL_SPI_Transmit(NRFmodule->spi, &reg, 1, 100);
    HAL_SPI_Receive(NRFmodule->spi, &val, 1, 100);
    CSn_HIGH();

    return val;
}

void WriteReg(uint8_t reg, uint8_t *data, uint8_t length)
{
    reg |= W_REGISTER;

    CSn_LOW();
    HAL_SPI_Transmit(NRFmodule->spi, &reg, 1, 100);
    HAL_SPI_Transmit(NRFmodule->spi, data, length, 100);
    CSn_HIGH();
}

void NRF_Config(char *name, uint8_t channel, uint8_t payloadsize)
{

	CSn_HIGH();
	Delay_us(10000);

	uint8_t nrf_config = (uint8_t)(PWR_UP | EN_CRC);
    WriteReg(NRF_CONFIG, &nrf_config, 1); // Enable Power and CRC and waith for 1.5ms
    Delay_us(5000);

    uint8_t nrf_en_aa = ACK_DISABLE;
    WriteReg(EN_AA, &nrf_en_aa, 1); // Disable auto acknowledge

    WriteReg(RF_CH, &channel, 1); // set channel number/frequency

    WriteReg(RX_ADDR_P0, (uint8_t *)name, 5); // set RX pipe0 name
    WriteReg(TX_ADDR, (uint8_t *)name, 5); // set TX pipe0 name

    WriteReg(RX_PW_P0, &payloadsize, 1); //set pipe0 payload size
    CE_HIGH();

}

void NRF_TX_Mode()
{
	CE_LOW();
    uint8_t config = ReadReg(NRF_CONFIG); //read Config register before switching bits
    config |= PWR_UP;
    config &= PRIM_RX_TX; // set bit 0 to 0
    WriteReg(NRF_CONFIG, &config, 1);
    CE_HIGH();
    Delay_us(20);
}

void NRF_RX_Mode()
{
    uint8_t config = ReadReg(NRF_CONFIG); //read Config register before switching bits
    config |= PWR_UP;
    config |= PRIM_RX_RX; // set bit 0 to 1
    WriteReg(NRF_CONFIG, &config, 1);
    CE_HIGH();
    Delay_us(150);
    //CE_LOW();
}

void NRF_Transmit(char *data)
{
    uint8_t w_tx_reg = W_TX_PAYLOAD;
    CSn_LOW();
    HAL_SPI_Transmit(NRFmodule->spi, &w_tx_reg, 1, 100);
    HAL_SPI_Transmit(NRFmodule->spi, (uint8_t*)data, NRFmodule->payloadsize , 100);
    CSn_HIGH();
    Delay_us(10);

    CE_HIGH();
    Delay_us(20);
    CE_LOW();
}

void NRF_ReadData(char *data)
{
    uint8_t r_rx_reg = R_RX_PAYLOAD;
    CSn_LOW();
    HAL_SPI_Transmit(NRFmodule->spi, &r_rx_reg, 1, 100);
    HAL_SPI_Receive(NRFmodule->spi, (uint8_t*)data, NRFmodule->payloadsize, 1000);
    CSn_HIGH();
}

bool NRF_Data_Available()
{
    uint8_t Reg_FIFO = ReadReg(FIFO_STATUS);
    return !(Reg_FIFO & 0x01);
}

