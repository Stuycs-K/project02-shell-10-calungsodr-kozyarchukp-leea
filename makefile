run: shell
	@./shell
compile shell: parse.o main.o misc.o commands.o
	@gcc -o shell parse.o main.o misc.o commands.o
parse.o: parse.c parse.h main.h
	@gcc -c parse.c
main.o: main.c parse.h misc.h main.h commands.h
	@gcc -c main.c
misc.o: misc.c misc.h main.h
	@gcc -c misc.c
commands.o: commands.c commands.h main.h misc.h
	@gcc -c commands.c
clean:
	rm *.o
	rm shell
