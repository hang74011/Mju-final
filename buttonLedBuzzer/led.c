#include <stdlib.h> //exit() atoi() rand() srand() system() 함수를 사용하기 위한 헤더파일.
#include <stdio.h> //Standard Input/Output library (표준입출력 라이브러리)의 약어로써, C 언어의 표준 라이브러리 함수의 매크로 정의, 상수, 여러 형의 입출력 함수가 포함된 헤더 파일이다
#include <fcntl.h> //파일을 제어하는 헤더파일
#include <unistd.h> //유닉스와 같은 시스템에 의해 정의 된 인터페이스에서 unistd.h전형적으로 주로 구성되어 기능 랩퍼 시스템 콜 등 fork, pipe및 I / O 프리미티브 ( read, write, close등).을 사용하기 위한 헤더파일
#include "led.h"

#define LED_DRIVER_NAME		"/dev/periled"

static int fd = 0; //fd값 0으로 초기화
static int ledStatus = 0; //led상태를 0으로 시작

int ledInit(void)
{
	fd = open(LED_DRIVER_NAME,O_RDWR); //LED_DRIVER를 여는 함수
	if ( fd < 0 ) //fd가 0보다 작으면 driver가 열리지 않은 상태 error
	{
		printf("driver (//dev//cnled) open error.\n"); //error가 났을 경우 나오는 문구
		return 0; //초기화
	}
	ledOffAll();
	return 1;
}
int ledOnOff(int ledNum, int OnOff)
{
	int i=1; //i=1로 시작
	i= i<< ledNum; 
	ledStatus = ledStatus & (~i);
	if (OnOff) ledStatus = ledStatus | i;
	write(fd, &ledStatus,4);
	return 1;
}
int ledOnAll(void) //led를 전부 켜는 함수
{
	ledStatus=0xFFFFFFFF; //모든 비트에 1을 넣어 led를 on시킨다
	write(fd,&ledStatus,4);
}
int ledOffAll(void) //led를 모두 끄는 함수
{
	ledStatus=0x0; //led 비트에 모두 0을 넣어 led를 off시킨다.
	write(fd,&ledStatus,4);
}료
int ledExit(void) 
{
	ledOffAll();
	close(fd); //종료
}
