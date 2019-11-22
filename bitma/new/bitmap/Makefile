CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: bitmap.elf animation.elf aniGif.elf aniwithSound.elf
	cp *.elf ~/
clean:
	rm -f *.elf *.o *.a
	
libMyLib.a: libBitmap.o libBuzzer.o
	$(AR) rc libMyLib.a libBitmap.o libBuzzer.o

libBuzzer.o: libBuzzer.h libBuzzer.c 
	$(CC) -O3 -o libBuzzer.o -c libBuzzer.c
	

libBitmap.o: libBitmap.h libBitmap.c bitmapFileHeader.h
	$(CC) -O3 -o libBitmap.o -c libBitmap.c

bitmap.elf: libMyLib.a bitmap.c bitmap.h
	$(CC) -O3 bitmap.c -L. -l MyLib -o bitmap.elf 

animation.elf: libMyLib.a animation.c
	$(CC) -O3 animation.c -L. -l MyLib -o animation.elf 

aniGif.elf: libMyLib.a aniGif.c ./jpeg-6b/libjpeg.a
	$(CC) -O3 aniGif.c -L. -l MyLib -L./jpeg-6b -ljpeg -o aniGif.elf 

aniwithSound.elf: libMyLib.a aniwithSound.c ./jpeg-6b/libjpeg.a
	$(CC) -O3 aniwithSound.c -L. -l MyLib -L./jpeg-6b -ljpeg -lpthread -o aniwithSound.elf 
