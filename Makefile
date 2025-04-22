CC = g++
CFLAGS = -IOpenXR/include -Iglad/include -Iglfw/include -Iglm

SOURCE_DIR = src
OBJ_DIR = objs

SOURCE_NAMES = main.cpp model.cpp shader.cpp basicshader.cpp light.cpp world.cpp
SOURCES = $(addprefix $(SOURCE_DIR)/, $(SOURCE_NAMES))
GLAD_OBJ = glad.o
OBJ_NAMES = $(SOURCE_NAMES:.cpp=.o) $(GLAD_OBJ)
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_NAMES))

GLFW_OBJS = glfw/build/src/CMakeFiles/glfw.dir/*.c.obj
TARGET = a.exe

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(GLFW_OBJS) -lgdi32 -o $(TARGET)
	@echo "Totally Unreal Engine is real"

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/$*.cpp -o $(OBJ_DIR)/$*.o

$(OBJ_DIR)/$(GLAD_OBJ): glad/src/glad.c
	$(CC) $(CFLAGS) -c $^ -o $(OBJ_DIR)/$(GLAD_OBJ)