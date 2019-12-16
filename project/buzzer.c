
#include <stdio.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <stdlib.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <string.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <fcntl.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <unistd.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include <dirent.h> // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가
#include "buzzer.h" // 프로그램을 실행시키기 위해 쓰는 함수들을 위해 헤더파일 추가

#define MAX_SCALE_STEP 8 // 간편하게 쓰기 위해 define함수
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"// 간편하게 쓰기 위해 define함수
#define BUZZER_FILENAME "peribuzzer"// 간편하게 쓰기 위해 define함수
#define BUZZER_ENABLE_NAME "enable"// 간편하게 쓰기 위해 define함수
#define BUZZER_FREQUENCY_NAME "frequency"// 간편하게 쓰기 위해 define함수
char gBuzzerBaseSysDir[128]; ///sys/bus/platform/devices/peribuzzer.XX 가 결정됨
static const int musicScale[MAX_SCALE_STEP] =
{
262, /*do*/ 294,330,349,392,440,494, /* si */ 523
};

int buzzerLibInit(void){ 
	
DIR      *dir_info ;
dir_info = opendir(BUZZER_BASE_SYS_PATH);
int ifNotFound = 1;
if (dir_info != NULL){
while (1){
struct dirent *dir_entry;
dir_entry = readdir (dir_info);
if (dir_entry == NULL) break;
if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0){
ifNotFound = 0;
sprintf(gBuzzerBaseSysDir,"%s%s/",BUZZER_BASE_SYS_PATH,dir_entry->d_name);
}
}
}
printf("find %s\n",gBuzzerBaseSysDir);
return ifNotFound;
}

void buzzerEnable(int bEnable) // buzzer 활성화시키는 함수
{
char path[200];
sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME);
int fd=open(path,O_WRONLY);
if ( bEnable) write(fd, &"1", 1);
else write(fd, &"0", 1);
close(fd);
}

void setFrequency(int frequency) // set Frequency 함수
{
char path[200];
sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
int fd=open(path,O_WRONLY);
dprintf(fd, "%d", frequency);
close(fd);
}

int buzzerLibOnBuz(int freq) //buzzer on 시키는 함수
{
	int freIndex;
	

	freIndex = freq;

	printf("freq  :%d \n",freq);
	setFrequency(musicScale[freIndex-1]);
	
	buzzerEnable(1);
	}
	
	int buzzerLibOffBuz(void) // buzzer off 시키는 함수
{
	
	buzzerEnable(0);
	
	}
