#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <pthread.h>
#include "touch.h"

#define EVENT_DEVICE    "/dev/input/event4"
#define EVENT_TYPE      EV_ABS
#define EVENT_CODE_X    ABS_X
#define EVENT_CODE_Y    ABS_Y

int fd;
int a,b,c,x,y = 0;

int touchFunc(void)
{
	 struct input_event ev;
    char name[256] = "Unknown";

    /* Print Device Name */
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);
    printf("Reading from:\n");
    printf("device file = %s\n", EVENT_DEVICE);
    printf("device name = %s\n", name);
    
    for (;;) 
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
					a = 10;
				}
				if(ev.code==EVENT_CODE_Y)
				{
					y = ev.value;
					b = 10;
				}
				//printf("%s = %d\n", ev.code == EVENT_CODE_X ? "X" : "Y", ev.value);
				if(a+b == 20)
				{
					printf("x좌표 = %d	y좌표 = %d\n", x, y);
					a = 0;
					b = 0;
				}
			}
		}
	err:
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
}

int touchExit(void)		
{
	close(fd);
}
