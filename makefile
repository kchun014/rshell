CC=g++
CC_FLAGS= -g -Wall -Werror -ansi -pedantic
EXEC=Rshell.exe
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: Rshell Executable Connector Semicolon
	$(CC) src/*.cpp -o $(EXEC) #helps to make the executable.

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
	
clean:
	rm -rf ./bin
