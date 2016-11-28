.PHONY: build clean run

build:
	gcc -c *.c
	gcc *.o -o galaxy-irc

clean:
	rm *.o
	rm galaxy-irc

run:
	./galaxy-irc
