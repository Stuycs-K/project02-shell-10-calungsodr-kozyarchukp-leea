run: shell
	@./shell
compile shell: parse.o main.o misc.o redirect.o
	@gcc -o shell parse.o main.o misc.o redirect.o
parse.o: parse.c parse.h main.h
	@gcc -c parse.c
main.o: main.c parse.h misc.h main.h
	@gcc -c main.c
misc.o: misc.c misc.h main.h
	@gcc -c misc.c
redirect.o: redirect.c redirect.h main.h
	@gcc -c redirect.c
clean:
	rm *.o
	rm shell
