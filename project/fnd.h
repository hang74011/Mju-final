

#ifndef __FND_H__
#define __FND_H__

#define MAX_FND_NUM	6
#define FND_DATA_BUFF_LEN	(MAX_FND_NUM + 2)
#define FND_DRIVER_NAME		"/dev/perifnd"
#define MODE_STATIC_DIS		0
//#define MODE_TIME_DIS		1
#define MODE_COUNT_DIS		2

int fndDisp(int num , int dotflag);
int fnd(int mode,int number);
typedef struct FNDWriteDataForm_tag 
{
	char	DataNumeric[FND_DATA_BUFF_LEN];
	char	DataDot[FND_DATA_BUFF_LEN];
	char	DataValid[FND_DATA_BUFF_LEN];	
}stFndWriteForm,*pStFndWriteForm;
#endif
