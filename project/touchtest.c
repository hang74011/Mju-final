#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include "touch.h"

int main(int argc, char *argv[])
{
	touchInit();
	touchFunc();
	touchExit();
}
