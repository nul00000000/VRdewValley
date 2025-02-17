CC = g++
CFLAGS = -IOpenXR/include -Iglad/include -Iglfw/include

SOURCES = main.cpp
OBJS = $(SOURCES:.cpp=.o) glad.o

GLFW_OBJS = glfw/build/src/CMakeFiles/glfw.dir/*.c.obj
TARGET = a.exe

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(GLFW_OBJS) -lgdi32 -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $*.cpp

glad.o: glad/src/glad.c
	$(CC) $(CFLAGS) -c $^