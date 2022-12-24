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


void toggleFans(bool state){
	HAL_GPIO_WritePin(FAN_OUT_PORT, FAN_OUT_PIN, state);
	HAL_GPIO_WritePin(FAN_IN_PORT, FAN_IN_PIN, state);
}


void clampedIncrement(int* modifiedValue, int addedValue, int max, int min){
	*modifiedValue = *modifiedValue + addedValue;
	*modifiedValue = *modifiedValue > max? max: *modifiedValue;
	*modifiedValue = *modifiedValue < min? min: *modifiedValue;
}

void clampedAssign(int* modifiedValue, int newValue, int max, int min){
	*modifiedValue = newValue;
	*modifiedValue = *modifiedValue > max? max: *modifiedValue;
	*modifiedValue = *modifiedValue < min? min: *modifiedValue;
}

void handleButtons(){
	static uint32_t pressCooldown;
	if(pressCooldown < uwTick){
		pressCooldown = uwTick + 500;
		switch(data.mode){
			case TEMPERATURE_TARGET:
				data.mode = POWER_TARGET;
				break;
			case POWER_TARGET:
				data.integral = 0;
				data.mode = TEMPERATURE_TARGET;
				break;
			case POWER_OFF:
			default:
				break;
		}
	}
}

void changeTargetValues(uint8_t dir){
	switch(data.mode){
				case TEMPERATURE_TARGET:
					clampedIncrement(&data.targetTemp, dir?5:-5, TEMPERATURE_MAX, TEMPERATURE_MIN);
					break;
				case POWER_TARGET:
					clampedIncrement(&data.currentPow, dir?5:-5, POWER_MAX, POWER_MIN);
					break;
				case POWER_OFF:
				default:
					break;
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


//Triggered by TIM3 timer.
void handleOutput(){
static float previous;
	switch(data.mode){
		case POWER_TARGET:;
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, data.currentPow * 655);
			break;
		case TEMPERATURE_TARGET:;
			float e;
			e = data.measuredTemp - data.targetTemp/10.0  ;
			data.integral += e;
			float derivative = e - previous;
			previous = e;
			float u = (data.Kp * e) + (data.Ki * data.integral) + (data.Kd *derivative);
			clampedAssign(&data.currentPow, u, POWER_MAX, POWER_MIN);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, data.currentPow * 655);
		case POWER_OFF:
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0);
			break;
	}

}

void enableCooling(){
	data.statusMessage = "";
	data.mode = TEMPERATURE_TARGET;
	toggleFans(1);
}

void disableCooling(){
	data.statusMessage = "Power off";
	data.mode = POWER_OFF;
	toggleFans(0);
}

//Encoder and button callbacks
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

if(GPIO_Pin == GPIO_PIN_8) // Encoder
	handleEncoderTurn();
if(GPIO_Pin == GPIO_PIN_9)
	handleButtons();
}
