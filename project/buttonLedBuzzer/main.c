#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <linux/input.h>


#include "led.h"
#include "buzzer.h"
#include "button.h"


int main (void)
{
	printf ("Buzzer Piano!\r\n");
	if (ledInit()== 0)
	{
		printf ("LED init Failed!\r\n");
		return 0;
	}
	if (buzzerInit() == 0)
	{
		printf ("Buzzer init Failed!\r\n");
		return 0;
	}
	if (buttonInit() == 0)
	{
		printf ("Button init Failed!\r\n");
		return 0;
	}
	int messageID = msgget (MESSAGE_ID, IPC_CREAT|0666);	//To Receive Message from Library.
	BUTTON_MSG_T rxMsg;

	while (1)
	{
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		printf ("ReceivedMessage:%d-%d",rxMsg.keyInput, rxMsg.pressed);
		//rxMsg.pressed == 0 -> Really Pressed.
		int scale = 0;
		switch(rxMsg.keyInput)
		{
			case KEY_HOME: 
				printf("Volume up key):");
				scale = 0; 
			break;
			case KEY_BACK: 
				printf("Home key):"); 
				scale = 1;
			break;
			case KEY_SEARCH: 
				printf("Search key):"); 
				scale = 2;
			break;
			case KEY_MENU: 
				printf("Back key):");
				scale = 3;
			break;
			case KEY_VOLUMEUP: 
				printf("Menu key):"); 
				scale = 4;
			break;
			case KEY_VOLUMEDOWN:
				printf("Volume down key):");
				scale = 5;
			break;
		}

		if (rxMsg.pressed != 0)
		{
			ledOnOff(scale, 1);
			buzzerPlaySong(scale);
		}
		else
		{
			ledOnOff(scale, 0);
			buzzerStopSong();			
		}
		
	}

	ledExit();
	buzzerExit();
	buttonExit();
	return 1;
}