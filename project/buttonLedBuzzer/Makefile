#LED Piano
CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: libJaeminLib.a piano.elf

piano.elf: main.o libJaeminLib.a button.h buzzer.h led.h
	$(CC) main.o -o piano.elf -lJaeminLib -L. -lpthread

libJaeminLib.a:	button.o buzzer.o led.o
	$(AR) rc libJaeminLib.a button.o buzzer.o led.o

button.o: button.c button.h
buzzer.o: buzzer.c buzzer.h
led.o: led.c led.h
#위 세개의 o 파일은 암묵적 makefile 규칙에 의해 자동 생성됨

clean:
	rm -f *.elf *.o *.a