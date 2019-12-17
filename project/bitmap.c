#include <stdio.h>
#include <stdlib.h>     // for exit


#include "bitmap.h"
#include "libBitmap.h"

void usage(void)
{
    printf("====================================================\n");
    printf("\nUsage: ./bitmap [FILE.bmp]\n");
    printf("====================================================\n");
}


int main (int argc, char **argv)
{
    int screen_width; //스크린의 넓이
    int screen_height; //스크린의 높이
    int bits_per_pixel; //비트당 픽셀
    int line_length; //줄의 길이
    int cols = 0, rows = 0; //cols와 rows를 0으로 시작
	char *data;//char타입 포인터 사용


    printf("=================================\n");
    printf("Frame buffer Application - Bitmap\n");
    printf("=================================\n\n");

    if(argc != 2) {
        usage();
        return  0;
    }

	//FrameBuffer init
    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}

	//Clear FB.
	fb_clear();

	//FileRead
    if (read_bmp(argv[1], &data, &cols, &rows) < 0)
	{
		printf ("File open failed\r\n");
		return 0;
	}
    printf("\tBitmapFile: %dx%d pixels\n", cols, rows);
    printf("\tFB Screen: %dx%d\n", screen_width, screen_height);
    printf("\tFB bits_per_pixel: %d, FB line_length: %d\n", bits_per_pixel, line_length);
	
	//FileWrite
	fb_write(data, cols,rows);
    
	close_bmp();
	fb_close();
    return 0;
}
