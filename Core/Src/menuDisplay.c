#include <stdbool.h>
#include <math.h>

#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "ssd1306.h"
#include "menuBitmap.h"
#include "menuDisplay.h"

extern Data data;

//Init display and remove trash.
void menuDisplay_Init(){
	ssd1306_Init();
	ssd1306_FillBuffer(menubitmap_data, 1024);
	ssd1306_UpdateScreen();
}

//Helper method for that sweet ">>>>" scrolling animation
int animationHelper(int i, int ac, int offset){
	if((i-ac+offset)%5 != 0 && (i-ac+offset)%5 != 1)
		return 1;
	return 0;
}

void menuDisplay_Update(bool animate){

	if(data.mode == POWER_OFF){
		ssd1306_SetDisplayOn(0);
		return;
	}

	ssd1306_SetDisplayOn(1);

	static uint8_t animationCounter;
	animationCounter+=animate;
	animationCounter%=5;

	char tmpBuffer[8];

	//UI layout
	ssd1306_FillBuffer(menubitmap_data, 1024);

	int decimal = (int)((fabs(data.measuredTemp) - floor(fabs(data.measuredTemp)))*10);

	int barSize = floor((float)data.currentPow / 100 * 126);


	//Current Temperature
	sprintf(tmpBuffer, "%2.0f",data.measuredTemp > 0? floor(data.measuredTemp):ceil(data.measuredTemp));
	ssd1306_SetCursor(3,4);
	ssd1306_WriteString(tmpBuffer, Font_16x26,  1);

	sprintf(tmpBuffer, "%d",decimal);
	ssd1306_SetCursor(39,4);
	ssd1306_WriteString(tmpBuffer, Font_16x26,  1);
	ssd1306_SetCursor(59,4);
	ssd1306_WriteString("C", Font_16x26,  1);

	//Target Temperature
	sprintf(tmpBuffer, "%3d", data.targetTemp);
	ssd1306_SetCursor(78,15);
	ssd1306_WriteString(tmpBuffer, Font_11x18,  1);

	ssd1306_SetCursor(114,15);
	ssd1306_WriteString("C", Font_11x18,  1);

	ssd1306_DrawRectangle(99, 30, 100, 31, 1);

	//Current Power
	sprintf(tmpBuffer, "%3d%%", data.currentPow);
	ssd1306_SetCursor(87,46);
	ssd1306_WriteString(tmpBuffer, Font_7x10,  1);

	//Power bar
	for(int i = 2; i < barSize; i++){
		ssd1306_DrawPixel(i, 58, animationHelper(i,animationCounter,3));
		ssd1306_DrawPixel(i, 59, animationHelper(i,animationCounter,2));
		ssd1306_DrawPixel(i, 60, animationHelper(i,animationCounter,1));
		ssd1306_DrawPixel(i, 61, animationHelper(i,animationCounter,2));
		ssd1306_DrawPixel(i, 62, animationHelper(i,animationCounter,3));
	}

	//Rest
	ssd1306_SetCursor(78,3);
	ssd1306_WriteString("Target", Font_7x10,  data.mode != TEMPERATURE_TARGET);
	ssd1306_SetCursor(78,35);
	ssd1306_WriteString("Power", Font_7x10,   data.mode != POWER_TARGET);

	if(strcmp(data.statusMessage, "") == 0){
		ssd1306_SetCursor(15,34);
		ssd1306_WriteString("MB 2022", Font_7x10,  1);
		ssd1306_SetCursor(15,45);
		ssd1306_WriteString("SW AGH", Font_7x10,  1);
	}else{
		ssd1306_SetCursor(15,34);
		ssd1306_WriteString(data.statusMessage, Font_6x8,  1);
	}

	//Update Screen
	ssd1306_UpdateScreen();
}
