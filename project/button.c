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
#include <sys/msg.h>
#include "button.h"

static pthread_t buttonTh_id;
//static pthread_t buttonTh_r_id;
static int fd=0,fp = 0;
static void *buttonThFunc(void* arg);
//static void* buttonThFunc_r(void* arg);
static int msgID ;
//static int readsize=0;

int buttonLibInit(void)
{
fd=open (BUTTON_DRIVER_NAME, O_RDONLY);
msgID = msgget (MESSAGE_ID, IPC_CREAT|0666); //1122

pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
//pthread_create(&buttonTh_r_id, NULL, &buttonThFunc_r, NULL);
	if ( fd == -1 )
	{
		printf("%s file read error.\n",BUTTON_DRIVER_NAME);
		return 1;
	}
	
}
int buttonLibExit(void)
{
pthread_cancel(buttonTh_id);
	close(fd);
}

static void* buttonThFunc(void* arg)
{    
	BUTTON_MSG_T msgTx;
	msgTx.messageNum = 1;
	struct input_event stEvent;
	while (1)
	{
		read(fd, &stEvent, sizeof (stEvent));
		
		printf ("Event Occur!\r\n");
		if ( ( stEvent.type == EV_KEY) )
		{
			msgTx.keyInput = stEvent.code;
			msgTx.pressed = stEvent.value;
			msgsnd(msgID, &msgTx, sizeof(msgTx) - sizeof(long int), 0);
		}
    }
}
/*static void* buttonThFunc_r(void* arg)
{
	BUTTON_MSG_R msgRx;
	msgRx.messageNum = 1;

	while(1)
	{
msgRx.keyOutput=0;
		int returnvalue=0;
		usleep(100);
	returnvalue=msgrcv(msgID,&msgRx,sizeof(int), 0,0);

	if (returnvalue==-1) 
	printf("실패");
	
	switch(msgRx.keyOutput)
{
case KEY_VOLUMEUP: printf("EV_KEY(Volume up key):"); break;
case KEY_HOME: printf("EV_KEY(Home key):"); break;
case KEY_SEARCH: printf("EV_KEY(Search key):"); break;
case KEY_BACK: printf("EV_KEY(Back key):"); break;
case KEY_MENU: printf("EV_KEY(Menu key):"); break;
case KEY_VOLUMEDOWN:printf("EV_KEY(Volume down key):");break;
default:;break;
}
}

	}*/



