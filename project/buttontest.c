#include <string.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <linux/input.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <unistd.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <fcntl.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <sys/ioctl.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <sys/mman.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <fcntl.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <unistd.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <stdio.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <stdlib.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <pthread.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <sys/ipc.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <sys/msg.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#define  INPUT_DEVICE_LIST	"/dev/input/event" //가져다 쉽게 불러쓰기 위해 define 함수 씀
#define  SYS_PATH	"S: Sysfs=" //가져다 쉽게 불러쓰기 위해 define 함수 씀
#define  BUTTON_NAME	"ecube-button" //가져다 쉽게 불러쓰기 위해 define 함수 씀
#define  LINE_FEED	0x0A //가져다 쉽게 불러쓰기 위해 define 함수 씀
#define  MAX_BUFF	200 //가져다 쉽게 불러쓰기 위해 define 함수 씀
int main(int argc, char *argv[]) //함수 배열 선언
{

	char 	inputfileName[MAX_BUFF+1]; // 변수 선언
	int		readSize,inputIndex; // 변수 선언
	struct input_event  stEvent;
	if (argc != 2)
	{
		printf("Usage : buttontest  <input Number>\n");
		printf("       Firstly read the '/proc/bus/input/devices' file to check <input Number> \n");
		printf("       >cat /proc/bus/input/devices\n");
		
		return 1;
	}
	inputIndex = atoi(argv[1]); // 글자를 잘라서 저장하기 위해 씀

	sprintf(inputfileName,"%s%d",INPUT_DEVICE_LIST,inputIndex);
	printf("read button event:%s\n",inputfileName);

buttonLibInit();
for(int i=0; i<100; i++)
{
	printf("i= %d\n",i);
	sleep(1);
}
buttonLibExit();	
}
