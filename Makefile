mp3:	mp3.c
	gcc -O3 -o mp3 mp3.c /usr/lib/libfmodex64.so -pthread -lcurses

run:
	./mp3

clean:
	rm -f mp3
