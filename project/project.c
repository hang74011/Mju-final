#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnd.h"
#include "textlcd.h"
#include "buzzer.h"
#include "led.h"
#include "button.h"
#include "libBitmap.h"
#include "touch.h"
#include <pthread.h>
#include <sys/ipc.h>
#include <linux/input.h>
#include <sys/msg.h>
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>
#include <time.h>

//#define  INPUT_DEVICE_LIST	"/dev/input/event"
//#define  SYS_PATH	"S: Sysfs="
//#define  BUTTON_NAME	"ecube-button"
//#define  LINE_FEED	0x0A
//#define  MAX_BUFF	200

#define MAX_SCALE_STEP 8
//#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"


#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

#define FND_DRIVER_NAME		"/dev/perifnd"

#define LED_DRIVER_NAME "/dev/periled"
//char gBuzzerBaseSysDir[128]; ///sys/bus/platform/devices/peribuzzer.XX 가 결정됨

pthread_t TOUCHTH_ID;

int zx[20] = {0};
int zy[20] = {0};

const int musicScale[MAX_SCALE_STEP] =
{
262, /*do*/ 294,330,349,392,440,494, /* si */ 523
};

void* TOUCHFUNC(void *args)
{
	touchInit();
	int messageID1 = msgget(MESSAGE_ID1, IPC_CREAT|0666);	
	TOUCH_MSG_T rxMSG;
	while(1)
	{
		msgrcv(messageID1, &rxMSG, sizeof(rxMSG)-sizeof(long int), 0, 0);
		for(int i = 0; i<20; i++)
		{
			zx[i] = rxMSG.touchX;
			zy[i] = rxMSG.touchY;
			msgrcv(messageID1, &rxMSG, sizeof(rxMSG)-sizeof(long int), 0, IPC_NOWAIT);
			usleep(10000);
		}
	}
	touchExit();
}

int main ( int argc , char *argv[])
{
	ledLibInit();
	buzzerLibInit();
	
	pthread_create(&TOUCHTH_ID, NULL, &TOUCHFUNC, NULL);
	
	//char 	inputfileName[MAX_BUFF+1];
	//int		readSize,inputIndex;
	//struct input_event  stEvent;
	int ran= rand()&10;
	
	//inputIndex = atoi(argv[1]);

	//sprintf(inputfileName,"%s%d",INPUT_DEVICE_LIST,inputIndex);
	//printf("read button event:%s\n",inputfileName);

// buttonInit();
  buttonInit() ;

  ledtextwrite("1","start");
int messageID = msgget(MESSAGE_ID, IPC_CREAT|0666);	//To Receive Message from Library.
	BUTTON_MSG_T rxMsg;
 
  char fin;
	int sum=0;
	sleep(1);
	fnd(0,sum);
	 int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;
    int cols = 0, rows = 0;
	char *data;
	    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}
	fb_clear();
	int sajin5[10][6]={ {9,0,2,4,7,10},{1,9,4,8,5,10},{7,2,8,4,9,10},{6,0,3,1,5,10} ,{9,0,1,6,2,10 },{8,5,4,3,7,10},{ 2,5,1,0,7,10},{6,8,9,3,4,10 },{7,2,9,8,5,10},{1,0,3,4,6,10 }};
	int sajin6[10][7]={ {7,9,0,2,4,7,10},{5,1,9,4,8,5,10},{4,7,2,8,4,9,10},{3,6,0,3,1,5,10} ,{8,9,0,1,6,2,10 },{1,8,5,4,3,7,10},{ 5,2,5,1,0,7,10},{2,6,8,9,3,4,10 },{6,7,2,9,8,5,10},{9,1,0,3,4,6,10 }};
	int sajin7[10][8]={ {1,7,9,0,2,4,7,10},{2,5,1,9,4,8,5,10},{3,4,7,2,8,4,9,10},{4,3,6,0,3,1,5,10} ,{5,8,9,0,1,6,2,10 },{6,1,8,5,4,3,7,10},{ 7,5,2,5,1,0,7,10},{8,2,6,8,9,3,4,10 },{9,6,7,2,9,8,5,10},{1,9,1,0,3,4,6,10 }};
	int sajin8[10][9]={ {9,1,7,9,0,2,4,7,10},{8,2,5,1,9,4,8,5,10},{7,3,4,7,2,8,4,9,10},{6,4,3,6,0,3,1,5,10} ,{5,5,8,9,0,1,6,2,10 },{4,6,1,8,5,4,3,7,10},{3, 7,5,2,5,1,0,7,10},{2,8,2,6,8,9,3,4,10 },{1,9,6,7,2,9,8,5,10},{5,1,9,1,0,3,4,6,10 }};
   int sajin9[10][10]={ {2,9,1,7,9,0,2,4,7,10},{3,8,2,5,1,9,4,8,5,10},{4,7,3,4,7,2,8,4,9,10},{5,6,4,3,6,0,3,1,5,10} ,{6,5,5,8,9,0,1,6,2,10 },{7,4,6,1,8,5,4,3,7,10},{8,3, 7,5,2,5,1,0,7,10},{9,2,8,2,6,8,9,3,4,10 },{6,1,9,6,7,2,9,8,5,10},{1,5,1,9,1,0,3,4,6,10 }};
	
	
	int hexa=0x0f;
	int state=0;
	int level=1;
	int start=0;
	ledOnOff (hexa);


while(hexa>0 ) {

		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		printf ("ReceivedMessage:%d-%d",rxMsg.keyInput, rxMsg.pressed);
		
		switch(rxMsg.keyInput)
		{
			case KEY_HOME: 
			printf("Home key):"); 
				     start=1;
			
			break;
				case KEY_SEARCH: 
			
				printf("Volume up key):");
				state=0;
		         level=1;
		       hexa=0x0f;
		       sum=0;
		       start=0;
		       ledtextwrite("1","reset");
		 ledtextwrite("2","LEVEL 0");
		 	ledOnOff (hexa);
			break;
		case KEY_BACK: 
				printf("Search key):"); 
				     start=1;
			break;
			case KEY_MENU: 
				printf("Back key):");
				     start=1;
			break;
			case KEY_VOLUMEUP: 
				printf("Menu key):"); 
			     start=1;
			break;
			case KEY_VOLUMEDOWN:
				printf("Volume down key):");
				     start=1;
			break;
		}
		
	/*if (rxMsg.keyInput==KEY_HOME && rxMsg.pressed !=0 )
	{   state=0;
		level=1;
		hexa=0x0f;
		sum=0;
	}*/
	
//	else if(&&rxMsg.keyInput== KEY_BACK && rxMsg.pressed !=0 )
	
	
	 if(state==0 &&level==1 &&start == 1) {
		 usleep(1000);
		 	buzzerLibOnBuz(8);
		 sleep(1);
	 buzzerLibOffBuz();
	for (int i=0; i<=5;i++)
	{    usleep(1000);
		 ledtextwrite("1","start");
		 ledtextwrite("2","LEVEL 1");
	
		char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",sajin5[ran][i]); //보여주고 싶은거 키트에 넣고 여기를 고치면 동영상 처럼 보여줄수있음  사진갯수가 적으니까 delay를 줘야함.
		//FileRead
       usleep(700000);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
		//FileWrite
		fb_write(data, cols,rows);
   
		close_bmp();
		 }
	 }
	 if(state==0 &&level==2&&start == 1) {
		  usleep(1000);
		 	buzzerLibOnBuz(8);
		 sleep(1);
	 buzzerLibOffBuz();
	for (int i=0; i<=6;i++)
	{  
		 usleep(1000);
		 ledtextwrite("1","start");
		 ledtextwrite("2","LEVEL 2");
	
		char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",sajin6[ran][i]); //보여주고 싶은거 키트에 넣고 여기를 고치면 동영상 처럼 보여줄수있음  사진갯수가 적으니까 delay를 줘야함.
		//FileRead
       usleep(500000);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
		//FileWrite
		fb_write(data, cols,rows);
   
		close_bmp();
		 }
	 }
	 
	 if(state==0 &&level==3&&start == 1) {
		  usleep(1000);
		 	buzzerLibOnBuz(8);
		 sleep(1);
	 buzzerLibOffBuz();
	for (int i=0; i<=7;i++)
	{  
		 //sleep(1);
		 ledtextwrite("1","start");
		 ledtextwrite("2","LEVEL 3");
		
		char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",sajin7[ran][i]); //보여주고 싶은거 키트에 넣고 여기를 고치면 동영상 처럼 보여줄수있음  사진갯수가 적으니까 delay를 줘야함.
		//FileRead
       usleep(400000);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
		//FileWrite
		fb_write(data, cols,rows);
   
		close_bmp();
		 }
	 }
	 
	 if(state==0 &&level==4&&start == 1) {
		  usleep(1000);
		 	buzzerLibOnBuz(8);
		 sleep(1);
	 buzzerLibOffBuz();
	for (int i=0; i<=8;i++)
	{  
		// sleep(1);
		 ledtextwrite("1","start");
		 ledtextwrite("2","LEVEL 4");
		
		char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",sajin8[ran][i]); //보여주고 싶은거 키트에 넣고 여기를 고치면 동영상 처럼 보여줄수있음  사진갯수가 적으니까 delay를 줘야함.
		//FileRead
      usleep(300000);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
		//FileWrite
		fb_write(data, cols,rows);
   
		close_bmp();
		 }
	 }
	 
	 if(state==0 &&level==5&&start == 1) {
		  usleep(1000);
		 	buzzerLibOnBuz(8);
		 sleep(1);
	 buzzerLibOffBuz();
	for (int i=0; i<=9;i++)
	{  
		// sleep(1);
		 ledtextwrite("1","start");
		 ledtextwrite("2","LEVEL 5");
	
		char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",sajin9[ran][i]); //보여주고 싶은거 키트에 넣고 여기를 고치면 동영상 처럼 보여줄수있음  사진갯수가 적으니까 delay를 줘야함.
		//FileRead
       usleep(200000);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
		//FileWrite
		fb_write(data, cols,rows);
   
		close_bmp();
		 }
	 }
 
		printf("%d %d\n", zx[0], zy[0]);
		sleep(1);
		fin=getchar();
		
				 if(fin=='f')
		{
			getchar();
			sum=sum-500;
	      fnd( MODE_STATIC_DIS,sum);
	      
	      buzzerLibOnBuz(5);
			usleep(500000);
			buzzerLibOffBuz();
			usleep(1000);
		
	
		hexa=hexa>>1;
		ledOnOff(hexa);
		ledtextwrite("1","fail");
		start=0;
		}
	
		else if(fin=='s')
		{
			getchar();
			sum=sum+1000;
			fnd( MODE_STATIC_DIS,sum);
		
			buzzerLibOnBuz(1);
			
			usleep(500000);
			buzzerLibOffBuz();
			usleep(1000);
			buzzerLibOnBuz(3);
			usleep(500000);
			buzzerLibOffBuz();
			usleep(1000);
			buzzerLibOnBuz(5);
			
			usleep(500000);
			buzzerLibOffBuz();
			usleep(1000);
		
			
			level++;
			start=0;
			if (level==6)
			{level=5;}
			
			ledtextwrite("1","success");
			ran= (rand())%10;
		}

			else  if(fin=='n')
		{;}
		
	
	sleep(1);
	
	msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
	} 

	ledtextwrite("1","game over");
		ledtextwrite("2","^^         ");

fnd( MODE_STATIC_DIS,0);
	fb_close();
ledLibExit();
 buttonExit();
buzzerLibOffBuz();
pthread_cancel(TOUCHTH_ID);
return 0;

}














