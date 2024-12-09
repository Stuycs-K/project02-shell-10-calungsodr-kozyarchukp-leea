run: shell
	@./shell
compile shell: parse.o main.o redirect.o pipe.o
	@gcc -o shell parse.o main.o redirect.o pipe.o
parse.o: parse.c parse.h main.h
	@gcc -c parse.c
main.o: main.c parse.h main.h pipe.h
	@gcc -c main.c
redirect.o: redirect.c redirect.h main.h
	@gcc -c redirect.c
pipe.o: pipe.c pipe.h main.h
	@gcc -c pipe.c
clean:
	rm *.o
	rm shell
