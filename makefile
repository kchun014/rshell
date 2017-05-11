CC=g++
CC_FLAGS= -g -Wall -Werror -ansi -pedantic
EXEC=rshell
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: Rshell Executable Connector Semicolon
	$(CC) src/*.cpp -o ./bin/$(EXEC) #helps to make the executable.

Rshell: Bin
	$(CC) -c $(CC_FLAGS) src/Rshell.cpp -o ./bin/rshell.o

Executable: Bin
	$(CC) -c $(CC_FLAGS) src/Executable.cpp   -o ./bin/Executable.o

Connector: Bin
	$(CC) -c $(CC_FLAGS) src/Connector.cpp   -o ./bin/Connector.o

Semicolon: Bin
	$(CC) -c $(CC_FLAGS) src/Semicolon.cpp   -o ./bin/Semicolon.o
	
Bin:
	mkdir -p bin
	
clean:
	rm -rf ./bin
