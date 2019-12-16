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

void* touchThFunc(void *args)			//touch 함수 쓰레드 발생.
{
	struct input_event ev;
	while(1)			//무한루프를 돌면서 터치값을 받음
	{
		const size_t ev_size = sizeof(struct input_event);
			ssize_t size;
			
			size = read(fd, &ev, ev_size);
			
			if (size < ev_size)
			{
				fprintf(stderr, "Error size when reading\n");
				goto err;
			}
			
			if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X || ev.code == EVENT_CODE_Y))		//이벤트 값이 x나 y일 경우
			{
				if(ev.code==EVENT_CODE_X)		//x좌표의 값을 변수 x에 지정한다.
				{
					x = ev.value;
					a = 3;
				}
				if(ev.code==EVENT_CODE_Y)		//y좌표의 값을 변수 y에 지정한다.
				{
					y = ev.value;
					a +=7;
				}
			}
		if( a == 10)		//좌표값의 순서가 x,y일 경우에만 메세지를 보냄.
									//이때 y,x의 순서로 값이 들어오는 경우에는 필터링.
									//내가 원하는 값만 보낼수 있도록 지정한다.
		{
			 TOUCH_MSG_T msgTx;
			msgTx.messageNum = 1;
			printf("\tRAWDATA x좌표 = %d	y좌표 = %d\n", x, y);		//현재 출력되는 x좌표, y좌표
			msgTx.touchX = x;																	//x좌표의 값을 메세지를 통해 보낸다
			msgTx.touchY = y;																	//y좌표의 값을 메세지를 통해 보낸다.
			msgsnd(msgID, &msgTx, sizeof(msgTx)-sizeof(long int), 0);	//메세지를 보냄
			a = 0;																						//a의 값을 초기화시켜준다.
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

int touchExit(void)		//Exit Device
{
	pthread_cancel(touchTh_id);	//쓰레드 삭제
	close(fd);
}
