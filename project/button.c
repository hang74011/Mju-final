#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>
#include "button.h"
static pthread_t buttonTh_id;
static int fd = 0;
//static void* buttonThFunc(void*);
static msgID = 0;
static int readsize=0;
//static void* buttonThFunc(void*arg)
int buttonLibInit(void)
{
fd=open (BUTTON_DRIVER_NAME, O_RDONLY);
msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
//pthread_create(&buttonTh_id, NULL, &buttonThFunc, NULL);
	if ( fd == -1 )
	{
		printf("%s file read error.\n",BUTTON_DRIVER_NAME);
		return 1;
	}
}
int buttonLibExit(void)
{
//pthread_cancel(buttonTh_id);
close(fd);
}


void buttonThFunc(void)
{
BUTTON_MSG_T msgTx;
msgTx.messageNum = 1;
struct input_event stEvent; 
while (1)
	{
		readsize = read(fd, &stEvent , sizeof(stEvent));
		if (readsize != sizeof(stEvent))
		{
			continue;
		}
//		printf("type:%d, code:%d, value:%d\n", stEvent.type, stEvent.code, stEvent.value);
		if ( stEvent.type == EV_KEY)
		{
			printf("EV_KEY(");
			switch(stEvent.code)
			{
				case KEY_VOLUMEUP:
				printf("Volume up key):");
				break;
				case KEY_HOME:
				printf("Home key):");
				break;
				case KEY_SEARCH:
				printf("Search key):");
				break;
				case KEY_BACK:
				printf("Back key):");
				break;
				case KEY_MENU:
				printf("Menu key):");
				break;
				case KEY_VOLUMEDOWN:
				printf("Volume down key):");
				break;
			}
			if ( stEvent.value )
			{
				printf("pressed\n");
			}
			else
			{
				printf("released\n");
			}
		}
		else // EV_SYN
		{
			// do notthing
		}
	}
                                                                                   //{
                                                                              //read(fd, &stEvent, sizeof (stEvent));
                                                                             //if ( ( stEvent.type == EV_KEY) && ( stEvent.value == 0) )
                                                                             //{
                                                                             //msgTx.keyInput = stEvent.code;
                                                                             //msgsnd(messageID, &msgTx, sizeof(int), 0);
                                                                             //}
                                                                             //}

}



