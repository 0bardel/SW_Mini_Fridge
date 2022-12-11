#ifndef MENU_DISPLAY
#define MENU_DISPLAY


typedef struct MenuData{
	char readTemp[8];
	char targetTemp[8];
	char readTempDecimal[8];
	char currentPow[8];
} MenuData;


void menuDisplay_Init();
void menuDisplay_Update();

#endif
