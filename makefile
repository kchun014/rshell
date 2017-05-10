CC=g++
CC_FLAGS= -g -Wall -Werror -ansi -pedantic
EXEC=rshell.exe
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: Rshell Executable Connector Semicolon

Rshell: Bin
	$(CC) -c $(CC_FLAGS) src/Rshell.cpp -o ./bin/rshell

Executable: Bin
	$(CC) -c $(CC_FLAGS) src/Executable.cpp   -o ./bin/Executable

Connector: Bin
	$(CC) -c $(CC_FLAGS) src/Connector.cpp   -o ./bin/Connector

Semicolon: Bin
	$(CC) -c $(CC_FLAGS) src/Semicolon.cpp   -o ./bin/Semicolon
	
Bin:
	mkdir -p bin
	
Clean:
	rm -rf bin