#ifndef IO_MANAGER
#define IO_MANAGER
#include "main.h"


void HAL_GPIO_EXTI_Callback(uint16_t);
void wait(uint32_t);
void handleOutput();
void handleButtons();
void enableCooling();
void disableCooling();


#endif
