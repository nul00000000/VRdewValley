.SILENT:

-include wyatt.make

CC = g++
CFLAGS := -Iglad/include -Iglfw/include -Iglm -Iopenvr/include -DSHADER_BASE=$(shell pwd) $(WYATT_FLAGS) -g

SOURCE_DIR = src
OBJ_DIR = objs

SOURCE_NAMES = main.cpp model.cpp shader.cpp basicshader.cpp light.cpp world.cpp entity.cpp vr.cpp fbo.cpp power.cpp skyboxshader.cpp
HEADER_NAMES = shader.h light.h vr.h world.h model.h entity.h fbo.h power.h
SOURCES = $(addprefix $(SOURCE_DIR)/, $(SOURCE_NAMES))
GLAD_OBJ = glad.o
OBJ_NAMES = $(SOURCE_NAMES:.cpp=.o) $(GLAD_OBJ)
HEADERS = $(addprefix $(SOURCE_DIR)/, $(HEADER_NAMES));
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_NAMES))

GLFW_OBJS = $(wildcard glfw/build/src/CMakeFiles/glfw.dir/*.c.o glfw/build/src/CMakeFiles/glfw.dir/*.c.obj)
TARGET := vdv

-include adam.make

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(GLFW_OBJS) $(WYATT_FLAGS) $(MEOW) -o $(TARGET)
	echo "Totally Unreal Engine is real"

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADERS)
	-mkdir $(OBJ_DIR) 2>/dev/null
	echo "Compiling $*.cpp..."
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/$*.cpp -o $(OBJ_DIR)/$*.o

$(OBJ_DIR)/$(GLAD_OBJ): glad/src/glad.c
	$(CC) $(CFLAGS) -c $^ -o $(OBJ_DIR)/$(GLAD_OBJ)
