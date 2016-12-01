.PHONY: build clean run

build:
	gcc -c *.c
	gcc *.o -lpthread -o galaxy-irc

clean:
	rm *.o
	rm galaxy-irc

run:
	./galaxy-irc 127.0.0.1
