#include <stdbool.h>
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "ssd1306.h"
#include "menuBitmap.h"
#include "menuDisplay.h"

static MenuData menuData = {"","",""};
extern Data data;


void menuDisplay_Init(){

	ssd1306_Init();
	ssd1306_FillBuffer(menubitmap_data, 1024);
	ssd1306_UpdateScreen();

}


int animationHelper(int i, int ac, int offset){
	if((i-ac+offset)%5 != 0)
		return 1;
	return 0;
}

void menuDisplay_Update(){
	static uint8_t animationCounter;
	animationCounter+=1;
	animationCounter%=5;

	ssd1306_FillBuffer(menubitmap_data, 1024);
	sprintf(menuData.readTemp, "%2d",(int)floor(data.measuredTemp));
	sprintf(menuData.readTempDecimal, "%1.0f",(data.measuredTemp - (int)floor(data.measuredTemp))*10);
	sprintf(menuData.targetTemp, "%3d", data.targetTemp);
	sprintf(menuData.currentPow, "%3d%%", data.currentPow);
	int barSize = floor((float)data.currentPow / 100 * 126);


	//Current Temperature
	ssd1306_SetCursor(3,4);
	ssd1306_WriteString(menuData.readTemp, Font_16x26,  1);

	ssd1306_SetCursor(39,4);
	ssd1306_WriteString(menuData.readTempDecimal, Font_16x26,  1);
	ssd1306_SetCursor(59,4);
	ssd1306_WriteString("C", Font_16x26,  1);

	//Target Temperature
	ssd1306_SetCursor(78,15);
	ssd1306_WriteString(menuData.targetTemp, Font_11x18,  1);

	ssd1306_SetCursor(114,15);
	ssd1306_WriteString("C", Font_11x18,  1);

	ssd1306_DrawRectangle(99, 30, 100, 31, 1);

	//Current Power
	ssd1306_SetCursor(87,46);
	ssd1306_WriteString(menuData.currentPow, Font_7x10,  1);

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
	ssd1306_WriteString("Target", Font_7x10,  data.targetMode!=0);
	ssd1306_SetCursor(78,35);
	ssd1306_WriteString("Power", Font_7x10,   data.targetMode!=1);



	ssd1306_SetCursor(15,34);
	ssd1306_WriteString("MB 2022", Font_7x10,  1);
	ssd1306_SetCursor(15,45);
	ssd1306_WriteString("SW AGH", Font_7x10,  1);

	//Update Screen
	ssd1306_UpdateScreen();
}
