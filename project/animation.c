#include <stdio.h>
#include <stdlib.h>
#include "libBitmap.h"

int main (int argc, char **argv) // 배열 선언
{
    int screen_width; // 스크린 너비 설정
    int screen_height; // 스크린 높이 설정
    int bits_per_pixel; // 픽셀 설정
    int line_length; // 라인 길이
    int cols = 0, rows = 0;  // 행,열
	char *data;  // 데이터 변수 선언
	//FrameBuffer init
    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}
	//Clear FB.
	fb_clear();
	
	int i=0;
	for (i=99; i<=3285;i++)
	{
		char filename[200]={0,};
		snprintf(filename,200,"./superm/supermario_%05d.bmp",i); //보여주고 싶은거 키트에 넣고 여기를 고치면 동영상 처럼 보여줄수있음  사진갯수가 적으니까 delay를 줘야함
		//FileRead
	    if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
		//FileWrite
		fb_write(data, cols,rows);
    
		close_bmp();
	}
	fb_close();
    return 0;
}
