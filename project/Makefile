all: button.h button.c led.h led.c
	arm-linux-gnueabi-gcc -c button.c -o button.o
	arm-linux-gnueabi-gcc -c led.c -o led.o
	arm-linux-gnueabi-gcc -c textlcd.c -o textlcd.o
	arm-linux-gnueabi-ar rc libMyperi.a button.o led.o textlcd.o
