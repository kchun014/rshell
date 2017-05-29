CC=g++
CC_FLAGS= -g -Wall -Werror -ansi -pedantic
EXEC=rshell
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: Rshell Evaluate
	$(CC) src/*.cpp -o ./bin/$(EXEC) #helps to make the executable.

Rshell: Bin
	$(CC) -c $(CC_FLAGS) src/Rshell.cpp -o ./bin/rshell.o

Evaluate: Bin
	$(CC) -c $(CC_FLAGS) src/Evaluate.cpp   -o ./bin/Evaluate.o

Bin:
	mkdir -p bin
	
clean:
	rm -rf ./bin
