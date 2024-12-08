run: shell
	@./shell
compile shell: parse.o main.o redirect.o
	@gcc -o shell parse.o main.o redirect.o
parse.o: parse.c parse.h main.h
	@gcc -c parse.c
main.o: main.c parse.h main.h
	@gcc -c main.c
redirect.o: redirect.c redirect.h main.h
	@gcc -c redirect.c
clean:
	rm *.o
	rm shell
