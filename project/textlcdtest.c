#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "textlcd.h"
#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

int main(int argc , char **argv)
{
	
	ledtextwrite("1","success");
	ledtextwrite("2","Next");	
	sleep(2);
	ledtextwrite("1","");
	ledtextwrite("2","start");
	
	return 0;
}
