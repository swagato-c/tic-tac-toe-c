INCLUDE_PATH = include/
PROJECT_NAME = tictactoe

cli_exec:
	bin
	gcc main.c ./bin/* -I$(INCLUDE_PATH) -o $(PROJECT_NAME)

bin:
	mkdir bin
	gcc -c ./src/*.c -I$(INCLUDE_PATH)-std='c11' -Wall
	mv *.o ./bin

clean:
	rm -rf bin/ $(PROJECT_NAME)
