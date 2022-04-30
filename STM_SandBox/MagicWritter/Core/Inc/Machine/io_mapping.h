/*
 * io_mapping.h
 *
 *  Created on: Apr 9, 2022
 *      Author: szerpadiaz
 */

#ifndef INC_MACHINE_IO_MAPPING_H_
#define INC_MACHINE_IO_MAPPING_H_

#define USER_LED_PIN  GPIO_PIN_13
#define USER_LED_PORT GPIOG

#define USER_BUTTON_PIN  GPIO_PIN_0
#define USER_BUTTON_PORT GPIOA
#define USER_BUTTON_IRQn 6

#define USARTx                           USART1
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()
#define USARTx_TX_PIN                    GPIO_PIN_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF7_USART1
#define USARTx_RX_PIN                    GPIO_PIN_10
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_AF                     GPIO_AF7_USART1


#endif /* INC_MACHINE_IO_MAPPING_H_ */
