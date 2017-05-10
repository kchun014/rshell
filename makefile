CC=g++
CC_FLAGS= -g -Wall -Werror -ansi -pedantic
EXEC=rshell.exe
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: 
	mkdir -p bin
	Rshell Executable Connector Semicolon

Rshell:
	$(CC) $(CC_FLAGS) src/Rshell.cpp -o bin/rshell 

Executable:
	$(CC) $(CC_FLAGS) src/Executable.cpp   -o bin/Executable

Connector:
	$(CC) $(CC_FLAGS) src/Connector.cpp   -o bin/Connector

Semicolon:
	$(CC) $(CC_FLAGS) src/Semicolon.cpp   -o bin/Semicolon

