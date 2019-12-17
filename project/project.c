#include <stdio.h> //exit() atoi() rand() srand() system() 함수를 사용하기 위한 헤더파일.
#include <stdlib.h>//Standard Input/Output library (표준입출력 라이브러리)의 약어로써, C 언어의 표준 라이브러리 함수의 매크로 정의, 상수, 여러 형의 입출력 함수가 포함된 헤더 파일이다
#include <string.h>//C 언어의 표준 라이브러리로, 메모리 블록이나 문자열을 다룰 수 있는 함수들을 포함하는 헤더파일
#include <sys/ioctl.h>
#include <ctype.h>// C 언어의 표준 라이브러리로, 문자들을 조건에 맞는지 검사하고 변환하는 함수들을 포함하는 헤더파일
#include <sys/ipc.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>//파일을 제어하는 헤더파일
#include <unistd.h>//유닉스와 같은 시스템에 의해 정의 된 인터페이스에서 unistd.h전형적으로 주로 구성되어 기능 랩퍼 시스템 콜 등 fork, pipe및 I / O 프리미티브 ( read, write, close등).을 사용하기 위한 헤더파일
#include "fnd.h" //fnd헤더파일을 만들어줌
#include "textlcd.h" //textlcd헤더파일을 만들어서 사용
#include "buzzer.h"//buzzer헤더파일을 만들어서 사용
#include "led.h"//led헤더파일을 만들어서 사용
#include "button.h"//button헤더파일을 만들어서 사용
#include "touch.h"//touch헤더파일을 만들어서 사용
#include "libBitmap.h"//libBitmap헤더파일을 만들어서 사용
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

	
    int a,x,y; //정수 변수 a,x,y 선언
	int i = 0; //i에 0 초기값 부여
	int zero=10; //zero에 10을 대입
	
    char fin; //char타입의 fin변수 선언
	int sum=0; //정수형 sum을 0으로 선언
	sleep(1);
	fnd(0,sum);
	
	int screen_width; // 스크린 너비 변수
    int screen_height; //스크린 높이 변수
    int bits_per_pixel; //비트당 픽셀 변수
    int line_length; //선의 길이 변수
    int cols = 0, rows = 0; //행과 열을 0으로 선언
	char *data; //char타입의 data이름을 가진 포인터 선
	    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 ) //screen_width, &screen_height, &bits_per_pixel, &line_length가 0보다 작으
	{
		printf ("FrameBuffer Init Failed\r\n"); //init fail문구 표출
		return 0; //초기화
	}
	fb_clear();
	
	int sajin5[10][5]={ {9,0,2,4,7},{1,9,4,8,5},{7,2,8,4,9},{6,0,3,1,5} ,{9,0,1,6,2 },{8,5,4,3,7},{ 2,5,1,0,7},{6,8,9,3,4 },{7,2,9,8,5},{1,0,3,4,6 }}; //1스테이지에 나오는 문제를 배열로 선언
	int sajin6[10][6]={ {7,9,0,2,4,7},{5,1,9,4,8,5},{4,7,2,8,4,9},{3,6,0,3,1,5} ,{8,9,0,1,6,2 },{1,8,5,4,3,7},{ 5,2,5,1,0,7},{2,6,8,9,3,4},{6,7,2,9,8,5},{9,1,0,3,4,6 }}; //2스테이지에 나오는 문제를 배열로 선언
	int sajin7[10][7]={ {1,7,9,0,2,4,7},{2,5,1,9,4,8,5},{3,4,7,2,8,4,9},{4,3,6,0,3,1,5} ,{5,8,9,0,1,6,2},{6,1,8,5,4,3,7},{ 7,5,2,5,1,0,7},{8,2,6,8,9,3,4 },{9,6,7,2,9,8,5},{1,9,1,0,3,4,6 }}; //3스테이지에 나오는 문제를 배열로 선언
	int sajin8[10][8]={ {9,1,7,9,0,2,4,7},{8,2,5,1,9,4,8,5},{7,3,4,7,2,8,4,9},{6,4,3,6,0,3,1,5},{5,5,8,9,0,1,6,2},{4,6,1,8,5,4,3,7},{3, 7,5,2,5,1,0,7},{2,8,2,6,8,9,3,4},{1,9,6,7,2,9,8,5},{5,1,9,1,0,3,4,6 }}; //4스테이지에 나오는 문제를 배열로 선언
    int sajin9[10][9]={ {2,9,1,7,9,0,2,4,7},{3,8,2,5,1,9,4,8,5},{4,7,3,4,7,2,8,4,9},{5,6,4,3,6,0,3,1,5} ,{6,5,5,8,9,0,1,6,2 },{7,4,6,언1,8,5,4,3,7},{8,3, 7,5,2,5,1,0,7},{9,2,8,2,6,8,9,3,4 },{6,1,9,6,7,2,9,8,5},{1,5,1,9,1,0,3,4,6 }}; //5스테이지에 나오는 문제를 배열로 선언
	
	
	int success5[10][5] = {0,}; //success5배열을 선언
	int success6[10][6] = {0,};//success6배열을 선언
	int success7[10][7] = {0,};//success7배열을 선언
	int success8[10][8] = {0,};//success8배열을 선언
	int success9[10][9] = {0,};//success9배열을 선언
	
	
	int hexa=0x0f; //hexa정수형 선언
	int state=0; //state 정수형 선언 
	int level=1; //level 정수형선언
	int start=0; //start 정수형 선언
	int s=0; //s를 0으로 선언
	ledOnOff (hexa); //ledonoff 변수

char filename7[200]={0,}; //char타입의 배열 선언
		snprintf(filename7,200,"start.bmp");  //""의 내용을 filename에 넣는다.

       usleep(1000); //1ms딜레이

     if (read_bmp(filename7, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();

while(hexa>0 ) {
	ran = rand()%10; //난수 생성

	
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		printf ("ReceivedMessage:%d-%d",rxMsg.keyInput, rxMsg.pressed); //리시브 메시지 표출
	
		switch(rxMsg.keyInput) //스위치문
		{
			
				case KEY_SEARCH: 
			
				printf("reset"); //리셋
				 
		         level=1; //레벨은 1로 시작
		       hexa=0x0f; //헥사로 0f
		       sum=0; //sum은 0
		       start=0; //start = 0 
		       ledtextwrite("1","reset"); //
		 ledtextwrite("2","LEVEL 0"); //
		 	ledOnOff (hexa);
			break;
			
			case KEY_HOME : //home키가 눌리면
			printf("start"); //start문구 
				     start=1; //start =1 
				
			
			break;
			
				case KEY_BACK: //back이 눌리면
				printf("game over:"); //game over 문구 표시
				hexa=0x00; //0으로 초기화
				fnd( MODE_STATIC_DIS,0);
				ledOnOff (hexa);
			break;
			
			case KEY_MENU: //Menu가 눌리면
				printf("restart:"); //restart 표시
				level=1; //level = 1
				start=1; //start =1 
				hexa=0x0f;
				ledOnOff (hexa); //led on
					fnd( MODE_STATIC_DIS,sum);
				
			break;
	
		}
		

	 if(level==1 &&start == 1) { //level 과 start가 1이면
		 usleep(1000); //1ms delay
		 	buzzerLibOnBuz(8); //높은 도음 부저
		 sleep(1); //1초 delay
	 buzzerLibOffBuz(); //부저 off
	for (int i=0; i<=4;i++) //i를 증가시키는 for문 
	{    usleep(1000); //1ms delay
		 ledtextwrite("1","start"); //text메세지 표출
		 ledtextwrite("2","LEVEL 1");//text메세지 표출
	
		char filename[200]={0,}; //char타입의 filname이름을 가진 배열 선언
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
		 sleep(1); //1초 딜레이
	 }
	 
	 if(level==2&&start == 1) { //레벨이 2인 경우
		  usleep(1000); //1ms 딜레이
		 	buzzerLibOnBuz(8); //높은 도 부저 on
		 sleep(1); //1초 딜레이
	 buzzerLibOffBuz(); //부저 off
	for (int i=0; i<=5;i++) //i를 5까지 나오게 하는 for 문
	{  
		 usleep(1000); //1ms딜레이
		 ledtextwrite("1","start"); //start문구 표시
		 ledtextwrite("2","LEVEL 2");//level2 표시
	
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
		
		usleep(400000);
	
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
			ran = rand()%10;

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
			if(hexa==0x00)
		{
			char filename6[200]={0,};
		snprintf(filename6,200,"gameover.bmp"); 

       sleep(1);

     if (read_bmp(filename6, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
		hexa=1;
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		}
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
		usleep(400000);
	
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
			if(hexa==0x00)
		{
			char filename6[200]={0,};
		snprintf(filename6,200,"gameover.bmp"); 

       sleep(1);

     if (read_bmp(filename6, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
		hexa=1;
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		}
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
		usleep(400000);
	
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
			if(hexa==0x00)
		{
			char filename6[200]={0,};
		snprintf(filename6,200,"gameover.bmp"); 

       sleep(1);

     if (read_bmp(filename6, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
		hexa=1;
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		}
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
		usleep(400000);
	
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
		
			if(hexa==0x00)
		{
			char filename6[200]={0,};
		snprintf(filename6,200,"gameover.bmp"); 

       sleep(1);

     if (read_bmp(filename6, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
		hexa=1;
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		}
		}
	
}

  	 		if(level==5 &&start == 1)	
	{
		s=0;
			for (int j=0; j<=8;j++){
									char filename14[200]={0,};언
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
	usleep(400000);
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
		
		
		if(hexa==0x00)
		{
			char filename6[200]={0,};
		snprintf(filename6,200,"gameover.bmp"); 

       sleep(1);

     if (read_bmp(filename6, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	

		fb_write(data, cols,rows);
   
		close_bmp();
		hexa=1;
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		}
		


	}
	
}


	  
	
	sleep(1);
	
	msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
	} 

			char filename22[200]={0,};
		snprintf(filename22,200,"thank.bmp"); 
	
     if (read_bmp(filename22, &data, &cols, &rows) < 0)
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












