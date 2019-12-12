#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <linux/input.h>
#include <pthread.h>
#include "touch.h"

int main(int argc, char *argv[])
{
	int x,y;
	int i = 0;
	int zx[20] = {0};
	int zy[20] = {0};
	int messageID = msgget(MESSAGE_ID, IPC_CREAT|0666);
	TOUCH_MSG_T rxMsg;
	touchInit();
	touchFunc();
	while(1)
	{
		msgrcv(messageID, &rxMsg, sizeof(rxMsg)-sizeof(long int), 0, 0);
		for(i = 0; i<20; i++)
		{
	
			zx[i] = rxMsg.touchX;
			zy[i] = rxMsg.touchY;
			msgrcv(messageID, &rxMsg, sizeof(rxMsg)-sizeof(long int), 0, IPC_NOWAIT);
			usleep(10000);
		}
		printf("%d	%d\n", zx[0], zy[0]);
		/*msgrcv(messageID, &rxMsg, sizeof(rxMsg)-sizeof(long int), 0, 0);
		x = rxMsg.touchX;
		y = rxMsg.touchY;
		printf("%d	%d\n", x, y);
		msgrcv(messageID, &rxMsg, sizeof(rxMsg)-sizeof(long int), 0, IPC_NOWAIT);
		if(x-rxMsg.touchX == -1 || x-rxMsg.touchX == 1)
		{
			printf("%d	%d\n", x, y);
		}
		else
		{
			printf("%d	%d\n", rxMsg.touchX, rxMsg.touchY);
		}*/
		
		
		
	}
	touchExit();
}
