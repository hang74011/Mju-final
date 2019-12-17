#include <stdio.h> //함수가 포함되어있는 헤더파일
#include <stdlib.h>//함수가 포함되어있는 헤더파일
#include <unistd.h>//함수가 포함되어있는 헤더파일
#include <fcntl.h>//함수가 포함되어있는 헤더파일
#include <sys/ioctl.h>//함수가 포함되어있는 헤더파일
#include <sys/msg.h>//함수가 포함되어있는 헤더파일
#include <linux/input.h>//함수가 포함되어있는 헤더파일
#include <pthread.h>//함수가 포함되어있는 헤더파일
#include "touch.h"//함수가 포함되어있는 헤더파일

int main(int argc, char *argv[])
{
	int x,y; //변수선언
	int i = 0;//변수선언
	int zx[20] = {0};//변수선언
	int zy[20] = {0};//변수선언
	int messageID = msgget(MESSAGE_ID, IPC_CREAT|0666);//변수선언
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
