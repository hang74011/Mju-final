#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnd.h"
int main(int argc , char **argv)
{
	char fin;
	int sum=0;
	sleep(1);
	fnd(0,sum);
	for(int i=0; i<7;i++)
	{
		printf("s or f\n");
		sleep(1);
		fin=getchar();
		sleep(1);
		
		if(fin=='s')
		{
			sum=sum+1000;
			fnd( MODE_STATIC_DIS,sum);
			getchar();
		}
		else if(fin=='f')
		{
			sum=sum-500;
	      fnd( MODE_STATIC_DIS,sum);
	      getchar();
		}
		else
		{;}
		
	printf("%d\n",sum);
}
	return 0;
}
