#include "ioManager.h"
#include <stdbool.h>
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "menuDisplay.h"

extern Data data;

void wait(uint32_t time){
uint32_t target = uwTick + time;
while(uwTick < target);
};

void handleButtons(){
	static uint32_t pressCooldown;
	if(pressCooldown < uwTick){
		pressCooldown = uwTick + 500;
		data.targetMode = !data.targetMode;
	}
}

void changeTargetValues(uint8_t dir){
	data.measuredTemp +=dir?1.3:-1.3;
	if(data.targetMode == 0){
		data.targetTemp += dir?5:-5;
	}else{
		data.currentPow += dir?5:-5;
	}
}

void handleEncoderTurn(){
	static bool lastTurn;
	static bool sameDirTurnFlag;
	static bool a0; // previous A state
	static bool b0; // previous B state
	  bool a = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
	  bool b = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
	  if (a != a0) {              // A changed
	    a0 = a;
	    if (b != b0) {
	      b0 = b;
	      if((lastTurn != (a==b) )|| (sameDirTurnFlag == 1)){
	    	  sameDirTurnFlag = 0;
	    	  lastTurn = a==b;
	    	  changeTargetValues(a==b);
	      }else{
	    	  sameDirTurnFlag = 1;
	      }


	    }
	  }
}


//Encoder and button callbacks
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

if(GPIO_Pin == GPIO_PIN_8) // Encoder
	handleEncoderTurn();
if(GPIO_Pin == GPIO_PIN_9)
	handleButtons();
}
