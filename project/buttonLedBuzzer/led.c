#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "led.h"

#define LED_DRIVER_NAME		"/dev/periled"

static int fd = 0;
static int ledStatus = 0;

int ledInit(void)
{
	fd = open(LED_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		printf("driver (//dev//cnled) open error.\n");
		return 0;
	}
	ledOffAll();
	return 1;
}
int ledOnOff(int ledNum, int OnOff)
{
	int i=1;
	i= i<< ledNum;
	ledStatus = ledStatus & (~i);
	if (OnOff) ledStatus = ledStatus | i;
	write(fd, &ledStatus,4);
	return 1;
}
int ledOnAll(void)
{
	ledStatus=0xFFFFFFFF;
	write(fd,&ledStatus,4);
}
int ledOffAll(void)
{
	ledStatus=0x0;
	write(fd,&ledStatus,4);
}
int ledExit(void)
{
	ledOffAll();
	close(fd);
}