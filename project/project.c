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
#include "touch.h"
#include "libBitmap.h"
#include <pthread.h>
#include <sys/ipc.h>
#include <linux/input.h>
#include <sys/msg.h>
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>
#include <time.h>



#define EVENT_DEVICE    "/dev/input/event4"
#define MAX_SCALE_STEP 8

#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"


#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

#define FND_DRIVER_NAME		"/dev/perifnd"

#define LED_DRIVER_NAME "/dev/periled"


const int musicScale[MAX_SCALE_STEP] =
{
262, /*do*/ 294,330,349,392,440,494, /* si */ 523
};


int main ( int argc , char *argv[])
{
    
	int ran= rand()%10;
	
	int messageIDT = msgget(MESSAGE_IDT, IPC_CREAT|0666);
	TOUCH_MSG_T rxTMsg;
	
	int messageID = msgget(MESSAGE_ID, IPC_CREAT|0666);	//To Receive Message from Library.
	BUTTON_MSG_T rxMsg;
    ledLibInit();
	buzzerLibInit();	
	
	touchInit();
	touchFunc();
	buttonInit() ;

   ledtextwrite("1","start");

	
    int a,x,y;
	int i = 0;
	int zero=10;
	
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
	
	int sajin5[10][5]={ {9,0,2,4,7},{1,9,4,8,5},{7,2,8,4,9},{6,0,3,1,5} ,{9,0,1,6,2 },{8,5,4,3,7},{ 2,5,1,0,7},{6,8,9,3,4 },{7,2,9,8,5},{1,0,3,4,6 }};
	int sajin6[10][6]={ {7,9,0,2,4,7},{5,1,9,4,8,5},{4,7,2,8,4,9},{3,6,0,3,1,5} ,{8,9,0,1,6,2 },{1,8,5,4,3,7},{ 5,2,5,1,0,7},{2,6,8,9,3,4},{6,7,2,9,8,5},{9,1,0,3,4,6 }};
	int sajin7[10][7]={ {1,7,9,0,2,4,7},{2,5,1,9,4,8,5},{3,4,7,2,8,4,9},{4,3,6,0,3,1,5} ,{5,8,9,0,1,6,2},{6,1,8,5,4,3,7},{ 7,5,2,5,1,0,7},{8,2,6,8,9,3,4 },{9,6,7,2,9,8,5},{1,9,1,0,3,4,6 }};
	int sajin8[10][8]={ {9,1,7,9,0,2,4,7},{8,2,5,1,9,4,8,5},{7,3,4,7,2,8,4,9},{6,4,3,6,0,3,1,5},{5,5,8,9,0,1,6,2},{4,6,1,8,5,4,3,7},{3, 7,5,2,5,1,0,7},{2,8,2,6,8,9,3,4},{1,9,6,7,2,9,8,5},{5,1,9,1,0,3,4,6 }};
    int sajin9[10][9]={ {2,9,1,7,9,0,2,4,7},{3,8,2,5,1,9,4,8,5},{4,7,3,4,7,2,8,4,9},{5,6,4,3,6,0,3,1,5} ,{6,5,5,8,9,0,1,6,2 },{7,4,6,1,8,5,4,3,7},{8,3, 7,5,2,5,1,0,7},{9,2,8,2,6,8,9,3,4 },{6,1,9,6,7,2,9,8,5},{1,5,1,9,1,0,3,4,6 }};
	
	
	int success5[10][5] = {0,};
	int success6[10][6] = {0,};
	int success7[10][7] = {0,};
	int success8[10][8] = {0,};
	int success9[10][9] = {0,};
	
	
	int hexa=0x0f;
	int state=0;
	int level=1;
	int start=0;
	int s=0;
	ledOnOff (hexa);

char filename7[200]={0,};
		snprintf(filename7,200,"start.bmp"); 

       usleep(1000);

     if (read_bmp(filename7, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();

while(hexa>0 ) {

	
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		printf ("ReceivedMessage:%d-%d",rxMsg.keyInput, rxMsg.pressed);
	
		switch(rxMsg.keyInput)
		{
			
				case KEY_SEARCH: 
			
				printf("Volume up key):");
				
		         level=1;
		       hexa=0x0f;
		       sum=0;
		       start=0;
		       ledtextwrite("1","reset");
		 ledtextwrite("2","LEVEL 0");
		 	ledOnOff (hexa);
			break;
			
			case KEY_HOME : 
			printf("start"); 
				     start=1;
				
			
			break;
			
				case KEY_BACK: 
				printf("game over:"); 
				hexa=0;
			break;
			
			case KEY_MENU: 
				printf("restart:");
				level=1;
			break;
	
		}
		

	 if(level==1 &&start == 1) {
		 usleep(1000);
		 	buzzerLibOnBuz(8);
		 sleep(1);
	 buzzerLibOffBuz();
	for (int i=0; i<=4;i++)
	{    usleep(1000);
		 ledtextwrite("1","start");
		 ledtextwrite("2","LEVEL 1");
	
		char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",sajin5[ran][i]); 
		
       usleep(600000);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
		
		fb_write(data, cols,rows);
   
		close_bmp();
		 }
		 sleep(1);
	 }
	 
	 if(level==2&&start == 1) {
		  usleep(1000);
		 	buzzerLibOnBuz(8);
		 sleep(1);
	 buzzerLibOffBuz();
	for (int i=0; i<=5;i++)
	{  
		 usleep(1000);
		 ledtextwrite("1","start");
		 ledtextwrite("2","LEVEL 2");
	
		char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",sajin6[ran][i]); 
	
       usleep(400000);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
	
		fb_write(data, cols,rows);
   
		close_bmp();
		 }
		 sleep(1);
	 }
	 
	 if(level==3&&start == 1) {
		  usleep(1000);
		 	buzzerLibOnBuz(8);
		 sleep(1);
	 buzzerLibOffBuz();
	for (int i=0; i<=6;i++)
	{  
		 //sleep(1);
		 ledtextwrite("1","start");
		 ledtextwrite("2","LEVEL 3");
		
		char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",sajin7[ran][i]); 
		
       usleep(250000);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
	
		fb_write(data, cols,rows);
   
		close_bmp();
		 }
		 sleep(1);
	 }
	 
	 if(level==4&&start == 1) {
		  usleep(1000);
		 	buzzerLibOnBuz(8);
		 sleep(1);
	 buzzerLibOffBuz();
	for (int i=0; i<=7;i++)
	{  
		// sleep(1);
		 ledtextwrite("1","start");
		 ledtextwrite("2","LEVEL 4");
		
		char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",sajin8[ran][i]); 
      usleep(150000);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
		 }
		 sleep(1);
	 }
	 
	 
	 if(level==5&&start == 1) {
		  usleep(1000);
		 	buzzerLibOnBuz(8);
		 sleep(1);
	 buzzerLibOffBuz();
	for (int i=0; i<=8;i++)
	{  
	
		 ledtextwrite("1","start");
		 ledtextwrite("2","LEVEL 5");
	
		char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",sajin9[ran][i]); 
	
       usleep(100000);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
	
		fb_write(data, cols,rows);
   
		close_bmp();
		 }
		 sleep(1);
	 }
	 
	 

			
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",zero); 

       usleep(1000);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
		
		sleep(1);
		
		
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		
	
		
		
	if(level==1 &&start == 1)	
	{
		s=0;
			for (int j=0; j<=4;j++){
				char filename10[200]={0,};
		snprintf(filename10,200,"key.bmp"); 

       usleep(1000);

     if (read_bmp(filename10, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
				
				msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, 0);
		x = rxTMsg.touchX;
		y = rxTMsg.touchY;
		
			for(i = 0; i<40; i++)
		{
			msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, IPC_NOWAIT);
		
			usleep(5000);
			
		}
		if(y>=0 && y<228)
		{
			if(x>=30 && x<222)
			{
				a = 9;
			}
			else if(x>=222 && x<415)
			{
				a = 8;
			}
			else if(x >=415 && x<607)
			{
				a = 7;
			}
			else if(x>=607 && x<801)
			{
				a = 6;
			}
			else if(x>=801)
			{
				a = 5;
			}
		}
		else if(y>=228)
		{
			if(x>=30 && x<222)
			{
				a = 4;
			}
			else if(x>=222 && x<415)
			{
				a = 3;
			}
			else if(x >=415 && x<607)
			{
				a = 2;
			}
			else if(x>=607 && x<801)
			{
				a = 1;
			}
			else if(x>=801)
			{
				a = 0;
			}
		}
				char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",a); 
	
     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
	
		fb_write(data, cols,rows);
   
		close_bmp();
		
		sleep(2);
	
	printf("\r\n현재 좌표 x : %d, y : %d\n\r\n\r\n", x, y);
		printf("현재 눌린 번호는 %d번 입니다.\n\n", a);
		printf("정답은  %d번 입니다.\n\n", sajin5[ran][j]);
		
		success5[ran][j]= a;
		
		if(success5[ran][j] ==sajin5[ran][j]) s++;
		
		
  

		
		while(1)
		{
			int rcv =  msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, IPC_NOWAIT);
		
			if(rcv == -1)
			break;
		}
	}
		 	char filename1[200]={0,};
		snprintf(filename1,200,"%d.bmp",zero); 

       usleep(1000);

     if (read_bmp(filename1, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
			if (s==5)
	{
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
			else
			 {
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
	
	
}
		
			if(level==2 &&start == 1)	
	{
		s=0;
			for (int j=0; j<=5;j++){
				
					char filename11[200]={0,};
		snprintf(filename11,200,"key.bmp"); 

       usleep(1000);

     if (read_bmp(filename11, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
				
				
				msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, 0);
		x = rxTMsg.touchX;
		y = rxTMsg.touchY;
		
			for(i = 0; i<40; i++)
		{
			msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, IPC_NOWAIT);
	
			
			usleep(5000);
			
		}
		if(y>=0 && y<228)
		{
			if(x>=30 && x<222)
			{
				a = 9;
			}
			else if(x>=222 && x<415)
			{
				a = 8;
			}
			else if(x >=415 && x<607)
			{
				a = 7;
			}
			else if(x>=607 && x<801)
			{
				a = 6;
			}
			else if(x>=801)
			{
				a = 5;
			}
		}
		else if(y>=228)
		{
			if(x>=30 && x<222)
			{
				a = 4;
			}
			else if(x>=222 && x<415)
			{
				a = 3;
			}
			else if(x >=415 && x<607)
			{
				a = 2;
			}
			else if(x>=607 && x<801)
			{
				a = 1;
			}
			else if(x>=801)
			{
				a = 0;
			}
		}
				char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",a); 
	

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
	
		fb_write(data, cols,rows);
   
		close_bmp();
		sleep(2);
	
	printf("\r\n현재 좌표 x : %d, y : %d\n\r\n\r\n", x, y);
		printf("현재 눌린 번호는 %d번 입니다.\n\n", a);
		printf("정답은  %d번 입니다.\n\n", sajin6[ran][j]);
		
		success6[ran][j]= a;
		
		if(success6[ran][j] ==sajin6[ran][j]) s++;
		
	
		
		
	}
	
		while(1)
		{
			int rcv =  msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, IPC_NOWAIT);
		
			if(rcv == -1)
			break;
		}
			char filename2[200]={0,};
		snprintf(filename2,200,"%d.bmp",zero); 

       usleep(1000);

     if (read_bmp(filename2, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
			if (s==6)
	{
		printf("맞춘횟수는.  %d번 입니다.\n\n", s);
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
			else
			 {
				 printf("맞춘횟수는.  %d번 입니다.\n\n", s);
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
	
	
}

   		if(level==3 &&start == 1)	
	{
		s=0;
			for (int j=0; j<=6;j++){
									char filename12[200]={0,};
		snprintf(filename12,200,"key.bmp"); 

       usleep(1000);

     if (read_bmp(filename12, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
				
				msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, 0);
		x = rxTMsg.touchX;
		y = rxTMsg.touchY;
		
			for(i = 0; i<40; i++)
		{
			msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, IPC_NOWAIT);
		
			
			usleep(5000);
			
		}
		if(y>=0 && y<228)
		{
			if(x>=30 && x<222)
			{
				a = 9;
			}
			else if(x>=222 && x<415)
			{
				a = 8;
			}
			else if(x >=415 && x<607)
			{
				a = 7;
			}
			else if(x>=607 && x<801)
			{
				a = 6;
			}
			else if(x>=801)
			{
				a = 5;
			}
		}
		else if(y>=228)
		{
			if(x>=30 && x<222)
			{
				a = 4;
			}
			else if(x>=222 && x<415)
			{
				a = 3;
			}
			else if(x >=415 && x<607)
			{
				a = 2;
			}
			else if(x>=607 && x<801)
			{
				a = 1;
			}
			else if(x>=801)
			{
				a = 0;
			}
		}
				char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",a); 
	

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
		
		fb_write(data, cols,rows);
   
		close_bmp();
		sleep(2);
	
	printf("\r\n현재 좌표 x : %d, y : %d\n\r\n\r\n", x, y);
		printf("현재 눌린 번호는 %d번 입니다.\n\n", a);
		printf("정답은  %d번 입니다.\n\n", sajin7[ran][j]);
		
		success7[ran][j]= a;
		
		if(success7[ran][j] ==sajin7[ran][j]) s++;
		
	
		
		
		while(1)
		{
			int rcv =  msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, IPC_NOWAIT);
			
			if(rcv == -1)
			break;
		}
	} 	char filename3[200]={0,};
		snprintf(filename3,200,"%d.bmp",zero); 

       usleep(1000);

     if (read_bmp(filename3, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
		
	
			if (s==7)
	{
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
			else
			 {
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
	
}
	
	 		if(level==4 &&start == 1)	
	{
		s=0;
			for (int j=0; j<=7;j++){
									char filename13[200]={0,};
		snprintf(filename13,200,"key.bmp"); 

       usleep(1000);

     if (read_bmp(filename13, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
		sleep(2);
				
				msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, 0);
		x = rxTMsg.touchX;
		y = rxTMsg.touchY;
		
			for(i = 0; i<40; i++)
		{
			msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, IPC_NOWAIT);
		
	
			
			usleep(5000);//5ms = 200ms
			
		}
		if(y>=0 && y<228)
		{
			if(x>=30 && x<222)
			{
				a = 9;
			}
			else if(x>=222 && x<415)
			{
				a = 8;
			}
			else if(x >=415 && x<607)
			{
				a = 7;
			}
			else if(x>=607 && x<801)
			{
				a = 6;
			}
			else if(x>=801)
			{
				a = 5;
			}
		}
		else if(y>=228)
		{
			if(x>=30 && x<222)
			{
				a = 4;
			}
			else if(x>=222 && x<415)
			{
				a = 3;
			}
			else if(x >=415 && x<607)
			{
				a = 2;
			}
			else if(x>=607 && x<801)
			{
				a = 1;
			}
			else if(x>=801)
			{
				a = 0;
			}
		}
				char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",a); 


     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
	
	printf("\r\n현재 좌표 x : %d, y : %d\n\r\n\r\n", x, y);
		printf("현재 눌린 번호는 %d번 입니다.\n\n", a);
		printf("정답은  %d번 입니다.\n\n", sajin8[ran][j]);
		
		success8[ran][j]= a;
		
		if(success8[ran][j] ==sajin8[ran][j]) s++;
		
	
		
		
		
		while(1)
		{
			int rcv =  msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, IPC_NOWAIT);
			
			if(rcv == -1)
			break;
		}
	}
		char filename4[200]={0,};
		snprintf(filename4,200,"%d.bmp",zero); 

       usleep(1000);

     if (read_bmp(filename4, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
			if (s==8)
	{
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
			else
			 {
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
	
}

  	 		if(level==5 &&start == 1)	
	{
		s=0;
			for (int j=0; j<=8;j++){
									char filename14[200]={0,};
		snprintf(filename14,200,"key.bmp"); 

       usleep(1000);

     if (read_bmp(filename14, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
				
				msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, 0);
		x = rxTMsg.touchX;//zx[0];
		y = rxTMsg.touchY;//zy[0];
		
			for(i = 0; i<40; i++)
		{
			msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, IPC_NOWAIT);
	
		
			
			usleep(5000);//5ms = 200ms
			
		}
		if(y>=0 && y<228)
		{
			if(x>=30 && x<222)
			{
				a = 9;
			}
			else if(x>=222 && x<415)
			{
				a = 8;
			}
			else if(x >=415 && x<607)
			{
				a = 7;
			}
			else if(x>=607 && x<801)
			{
				a = 6;
			}
			else if(x>=801)
			{
				a = 5;
			}
		}
		else if(y>=228)
		{
			if(x>=30 && x<222)
			{
				a = 4;
			}
			else if(x>=222 && x<415)
			{
				a = 3;
			}
			else if(x >=415 && x<607)
			{
				a = 2;
			}
			else if(x>=607 && x<801)
			{
				a = 1;
			}
			else if(x>=801)
			{
				a = 0;
			}
		}
				char filename[200]={0,};
		snprintf(filename,200,"%d.bmp",a);

     if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
	
		fb_write(data, cols,rows);
   
		close_bmp();
		sleep(2);
	
	printf("\r\n현재 좌표 x : %d, y : %d\n\r\n\r\n", x, y);
		printf("현재 눌린 번호는 %d번 입니다.\n\n", a);
		printf("정답은  %d번 입니다.\n\n", sajin9[ran][j]);
		
		success9[ran][j]= a;
		
		if(success9[ran][j] ==sajin9[ran][j]) s++;
		
	
		
		
		while(1)
		{
			int rcv =  msgrcv(messageIDT, &rxTMsg, sizeof(rxTMsg)-sizeof(long int), 0, IPC_NOWAIT);
			
			if(rcv == -1)
			break;
		}
	}
		char filename5[200]={0,};
		snprintf(filename5,200,"%d.bmp",zero); 

       usleep(1000);

     if (read_bmp(filename5, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
		
	
			if (s==9)
	{
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
			{level=5;
				char filename16[200]={0,};
		snprintf(filename16,200,"clear.bmp"); 

       usleep(1000);

     if (read_bmp(filename16, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
				}
			
			ledtextwrite("1","success");
			ran= rand()%10;
	
		}
			else
			 {
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
	
}


	  
	
	sleep(1);
	
	msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
	} 
char filename6[200]={0,};
		snprintf(filename6,200,"gameover.bmp"); 

       usleep(1000);

     if (read_bmp(filename6, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();




	ledtextwrite("1","game over");
		ledtextwrite("2","^^         ");

fnd( MODE_STATIC_DIS,0);
	fb_close();
ledLibExit();
 buttonExit();
 
 
buzzerLibOffBuz();
return 0;

}












