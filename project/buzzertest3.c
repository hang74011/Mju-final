
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
#include "buzzer.h"

int main(int argc , char **argv)
{
	 buzzerLibInit();
	 sleep(1);
	 buzzerLibOnBuz(1);
	 sleep(1);
	 buzzerLibOnBuz(2);
	 sleep(1);
	 buzzerLibOnBuz(3);
	 sleep(1);
	 buzzerLibOnBuz(4);
	 sleep(1);
	 buzzerLibOnBuz(5);
	 sleep(1);
	 buzzerLibOnBuz(6);
	 sleep(1);
	 buzzerLibOnBuz(7);
	 sleep(1);
	 buzzerLibOnBuz(8);
	 sleep(1);
	buzzerLibOffBuz();
	 return 0;
	 
	 }


