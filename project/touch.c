#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <pthread.h>

#define EVENT_DEVICE    "/dev/input/event4"
#define EVENT_TYPE      EV_ABS
#define EVENT_CODE_X    ABS_X
#define EVENT_CODE_Y    ABS_Y

int fd;

/* TODO: Close fd on SIGINT (Ctrl-C), if it's open */

int main(int argc, char *argv[])
{
	touchInit();
    struct input_event ev;
    char name[256] = "Unknown";

    if ((getuid ()) != 0) {
        fprintf(stderr, "You are not root! This may not work...\n");
        return EXIT_SUCCESS;
    }

    /* Print Device Name */
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);
    printf("Reading from:\n");
    printf("device file = %s\n", EVENT_DEVICE);
    printf("device name = %s\n", name);

    for (;;) {
        const size_t ev_size = sizeof(struct input_event);
        ssize_t size;

        /* TODO: use select() */

        size = read(fd, &ev, ev_size);
        if (size < ev_size) {
            fprintf(stderr, "Error size when reading\n");
            goto err;
        }

       /* if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X
                      || ev.code == EVENT_CODE_Y)) {*/
         if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X))
        {
            //printf("%s = %d\n", ev.code == EVENT_CODE_X ? "X" : "Y", ev.value);
            printf("X의 좌표 = %d\n", ev.value);
		}
		if(ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_Y))
		{
			printf("Y의 좌표 = %d\n", ev.value);
		}
		}

    return EXIT_SUCCESS;

err:
touchExit();
    return EXIT_FAILURE;
}

int touchInit(void)		/* Open Device */
{
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
