#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <pthread.h>
#include <sys/msg.h>
#include "touch.h"

#define EVENT_DEVICE    "/dev/input/event4"
#define EVENT_TYPE      EV_ABS
#define EVENT_CODE_X    ABS_X
#define EVENT_CODE_Y    ABS_Y

pthread_t touchTh_id;
int fd;
int a,b,c,x,y,k = 0;
static int msgID;

void* touchThFunc(void *args)
{
	struct input_event ev;
	while(1)
	{
		const size_t ev_size = sizeof(struct input_event);
			ssize_t size;
			
			size = read(fd, &ev, ev_size);
			
			if (size < ev_size)
			{
				fprintf(stderr, "Error size when reading\n");
				goto err;
			}
			
			if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X || ev.code == EVENT_CODE_Y))
			{
				if(ev.code==EVENT_CODE_X)
				{
					x = ev.value;
					a = 3;
				}
				if(ev.code==EVENT_CODE_Y)
				{
					y = ev.value;
					a +=7;
				}
			}
		if( a == 10)
		{
			 TOUCH_MSG_T msgTx;
			msgTx.messageNum = 1;
			printf("\tRAWDATA x좌표 = %d	y좌표 = %d\n", x, y);
			msgTx.touchX = x;
			msgTx.touchY = y;
			msgsnd(msgID, &msgTx, sizeof(msgTx)-sizeof(long int), 0);
			a = 0;
			b = 0;
		}
	}
	err:
	return 0;
}

int touchFunc(void)
{
    char name[256] = "Unknown";

    /* Print Device Name */
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);
    printf("Reading from:\n");
    printf("device file = %s\n", EVENT_DEVICE);
    printf("device name = %s\n", name);
    
	return 0;
}

int touchInit(void)		// Open Device 
{
	if ((getuid ()) != 0) {
		fprintf(stderr, "You are not root! This may not work...\n");
        return EXIT_SUCCESS;
    }
	fd = open(EVENT_DEVICE, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "%s is not a vaild device\n", EVENT_DEVICE);
		return EXIT_FAILURE;
    }
    msgID = msgget(MESSAGE_IDT, IPC_CREAT|0666); //1234
    pthread_create(&touchTh_id, NULL, &touchThFunc, NULL);
}

int touchExit(void)		
{
	pthread_cancel(touchTh_id);
	close(fd);
}
