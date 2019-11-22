#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/ioctl.h> 
#include <sys/mman.h>

#define  INPUT_DEVICE_LIST	"/dev/input/event"

#define  SYS_PATH	"S: Sysfs="
#define  BUTTON_NAME	"ecube-button"

#define  LINE_FEED	0x0A

#define  MAX_BUFF	200
int main(int argc, char *argv[])
{

	char 	inputfileName[MAX_BUFF+1];
	int		readSize,inputIndex;
	struct input_event  stEvent;
	if (argc != 2)
	{
		printf("Usage : buttontest  <input Number>\n");
		printf("       Firstly read the '/proc/bus/input/devices' file to check <input Number> \n");
		printf("       >cat /proc/bus/input/devices\n");
		
		return 1;
	}
	inputIndex = atoi(argv[1]);

	sprintf(inputfileName,"%s%d",INPUT_DEVICE_LIST,inputIndex);
	printf("read button event:%s\n",inputfileName);

buttonLibInit();

buttonThFunc();

buttonLibExit();	
}
