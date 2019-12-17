#include <stdio.h>//변수선언
#include <stdlib.h>////변수선언
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "textlcd.h"

#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"
int ledtextwrite(const char* str1, const char* str2)
{
	unsigned int linenum = 0;
    int fd;
	stTextLCD  stlcd; 
	int len; 
	
	memset(&stlcd,0,sizeof(stTextLCD));//구조체 초기화
	
	linenum = strtol(str1,NULL,10);
	printf("linenum :%d\n", linenum);//지워도 될듯.
		if ( linenum == 1) // firsst line
	{
		stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
	}
	else if ( linenum == 2) // second line
	{
		stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
	}
	else 
	{
		printf("linenum : %d  wrong .  range (1 ~ 2)\n", linenum);
		return 1; 
	}
	printf("string:%s\n",str2);//지워도 될듯.
	len = strlen(str2);
	
	if ( len > COLUMN_NUM)
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],str2,COLUMN_NUM);//입력한걸 16bit 만큼 첫줄에 쓴다 뒤에가 짤림.
	}
	else
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],str2,len);//입력한걸 줄에 씀.
	}
	stlcd.cmd = CMD_WRITE_STRING; //쓰기모드?
	// open  driver 
	fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
	
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
	write(fd,&stlcd,sizeof(stTextLCD)); //fd 에 stlcd내용을 구조체크기만큼 쓴다

	
	close(fd);
	
	//return 0;
	}
