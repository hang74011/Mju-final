#include "led.h"
#include <fcntl.h> 
static unsigned int ledValue = 0;
static unsigned int state=0;
static int fd = 0;

int ledOnOff (int ledNum)
{
//int i=1;
//i=i<<ledNum;
//ledValue = ledValue& (~i);
ledValue = ledNum;
//if(onoff !=0) ledValue |= i;
write(fd, &ledValue, 4);
}
int ledLibInit(void)
{
fd=open("/dev/periled", O_WRONLY);
ledValue = 0;
state =0;
}

int ledLibExit(void)
{
//ledValue = 0;
//ledOnOff (0);
close(fd);
}
