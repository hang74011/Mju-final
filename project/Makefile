all: button.h button.c led.h led.c buzzer.c buzzer.h textlcd.c textlcd.h fnd.c fnd.h touch.c touch.h
	arm-linux-gnueabi-gcc -c button.c -o button.o
	arm-linux-gnueabi-gcc -c led.c -o led.o
	arm-linux-gnueabi-gcc -c textlcd.c -o textlcd.o
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o
	arm-linux-gnueabi-gcc -c touch.c -o touch.o
	arm-linux-gnueabi-ar rc libMyperi.a button.o led.o textlcd.o buzzer.o fnd.o touch.o
