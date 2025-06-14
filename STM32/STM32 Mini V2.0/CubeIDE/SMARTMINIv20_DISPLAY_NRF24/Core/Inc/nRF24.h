/*
 * nRF24.h
 *
 *  Created on: Jun 21, 2023
 *      Author: singularengineer
 */

#ifndef __NRF24_H_
#define __NRF24_H_

#ifdef __cplusplus
extern "C" {
#endif


#define NRF_CONFIG  0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define NRF_STATUS  0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17
#define DYNPD       0x1C
#define FEATURE     0x1D

/* Instruction */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define RF24_NOP      0xFF

/* Bit Mask*/
#define PWR_UP      0x02
#define EN_CRC      0x08
#define ACK_DISABLE 0x00
#define PRIM_RX_RX  0x01
#define PRIM_RX_TX  0xFE

/* Structs */
typedef struct _NRF24Def{
	SPI_HandleTypeDef *spi;
	GPIO_TypeDef *CSn_Port;
	uint16_t CSn_Pin;
	GPIO_TypeDef *CE_Port;
	uint16_t CEn_Pin;
	uint8_t payloadsize;
}nRF24Def;

/* Functions */
void NRF_Init( nRF24Def *nrf);
void CSn_LOW();
void CSn_HIGH();
void CE_LOW();
void CE_HIGH();

uint8_t ReadReg(uint8_t reg);
void WriteReg(uint8_t reg, uint8_t *data, uint8_t length);
void NRF_Config(char *name, uint8_t channel, uint8_t payloadsize);
void NRF_TX_Mode();
void NRF_RX_Mode();
void NRF_Transmit(char *data);
void NRF_ReadData(char *data);
bool NRF_Data_Available();



#ifdef __cplusplus
}
#endif

#endif /* INC_NRF24_H_ */
