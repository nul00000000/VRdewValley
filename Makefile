CC = g++
CFLAGS = -IOpenXR/include

SOURCES = main.cpp
OBJS = $(SOURCES:.cpp=.o)
TARGET = vdv.exe

.PHONY: all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $*.cpp