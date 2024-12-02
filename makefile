compile shell: parse.o main.o
	@gcc -o shell parse.o main.o
run:
	@./shell
parse.o: parse.c parse.h
	@gcc -c parse.c
main.o: main.c parse.h
	@gcc -c main.c
clean:
	rm *.o
	rm shell