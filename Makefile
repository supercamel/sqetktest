CC=g++
CFLAGS=-c -g -Wall -std=c++17 -pthread -I../EmbeddedToolKit/inc \
	   -I./squirrel -DSQ_EXCLUDE_DEFAULT_MEMFUNCTIONS

LDFLAGS= -lpthread
SOURCES=$(wildcard *.cpp) $(wildcard ./squirrel/*.cpp)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(HEADERS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)  $(HEADERS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	find . -name \*.o -execdir rm {} \;
	rm -f $(EXECUTABLE)
