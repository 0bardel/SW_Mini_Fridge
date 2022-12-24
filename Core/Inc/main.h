/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include <stdbool.h>

/*
 *Operation modes
 */

enum operationMode{
	POWER_OFF = 0,
	TEMPERATURE_TARGET = 1,
	POWER_TARGET = 2
};

/*
 * GPIO Pins definitions
 */

#define PELTIER_PIN GPIO_PIN_3
#define FAN_OUT_PIN GPIO_PIN_6
#define FAN_IN_PIN GPIO_PIN_5

#define BUTTON_ENCODER_PIN GPIO_PIN_12
#define BUTTON_POWER_PIN GPIO_PIN_13
#define BUTTON_INTERRUPT_TRIGGER_PIN GPIO_PIN_9

#define ENCODER_A_PIN GPIO_PIN_8
#define ENCODER_B_PIN GPIO_PIN_15


/*
 * Ports of the GPIO Pins
 */

#define PELTIER_PORT GPIOB
#define FAN_OUT_PORT GPIOB
#define FAN_IN_PORT GPIOB

#define BUTTON_ENCODER_PORT GPIOB
#define BUTTON_POWER_PORT GPIOB
#define BUTTON_INTERRUPT_TRIGGER_PORT GPIOA

#define ENCODER_A_PORT GPIOA
#define ENCODER_B_PORT GPIOB


/*
 * Power and temperature ranges
 */
#define POWER_MAX 100
#define POWER_MIN 0

	//targetTemp is expressed in 0.1C increments
#define TEMPERATURE_MAX 200
#define TEMPERATURE_MIN -100



/*
 * Data model
 */

typedef struct Data{

	float Kp;
	float Ki;
	float Kd;
	float integral;

	float measuredTemp;
	int targetTemp;
	int currentPow;

	enum operationMode mode;
	char* statusMessage;

} Data;


void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
