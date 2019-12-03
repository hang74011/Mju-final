
#ifndef _BUZZER_H_
#define _BUZZER_H_
#define MAX_SCALE_STEP		8

#define BUZZER_BASE_SYS_PATH	"/sys/bus/platform/devices/peribuzzer."

#define BUZZER_ENABLE_NAME		"enable"
#define BUZZER_FREQUENCY_NAME	"frequency"

//int findBuzzerSysPath(void);
void buzzerEnable(int bEnable);
void setFrequency(int frequency);
int buzzerLibInit(void);
int buzzerLibOnBuz(int freq);
int buzzerLibOffBuz(void);
//int buzzerLibExit(void);
#endif 
