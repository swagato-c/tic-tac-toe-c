#OBJECTS = main.o $(SRC_OBJECTS)
SRC_FILES = src
CFLAGS = -Wall
INCLUDE = include
DEBUG_FLAGS = -ggdb
NAME = tictac

build :bin
	gcc -c main.c
	gcc main.o libraries/*.o -o $(NAME) -O2

install: build clean
	clear && make build && make clean

bin:
	mkdir -p libraries/
	for dir in $(SRC_FILES); do\
		cd $$dir;\
		gcc -c *.c -I=../$(INCLUDE) $(CFLAGS);\
		mv *.o ../libraries;\
		cd ..;\
	done

clean:
	rm -rf libraries
	rm *.o
