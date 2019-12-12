#ifndef _TOUCH_H_
#define _TOUCH_H_

#define MESSAGE_ID1 1234

typedef struct
{
	long int messageNum;
	int touchX;
	int touchY;
} TOUCH_MSG_T;


int touchInit(void);
int touchFunc(void);
int touchExit(void);

#endif 
