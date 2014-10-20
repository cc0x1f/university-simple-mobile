CC = g++
LD = g++

SRC_DIR = src
RENDER_DIR = $(SRC_DIR)/render
OBJPARSER_DIR = $(SRC_DIR)/objparser

# add -DDEBUG=1 to CFLAGS enable debug output
CFLAGS = -g -Wall -DDEBUG=1
LDLIBS = -lm -lglut -lGLEW -lGL
INCLUDES = -Isource
VPATH = src

OBJ = Mobile.o $(SRC_DIR)/Helper.o $(SRC_DIR)/ShaderProgram.o $(SRC_DIR)/Texture.o $(SRC_DIR)/Camera.o $(SRC_DIR)/Lightsource.o $(SRC_DIR)/GlutProgram.o $(OBJPARSER_DIR)/tiny_obj_loader.o $(RENDER_DIR)/RenderingObject.o $(RENDER_DIR)/LineRenderingObject.o $(RENDER_DIR)/BillboardRenderingObject.o $(RENDER_DIR)/OBJRenderingObject.o
TARGET = Mobile

# Rules
all: $(TARGET)

$(TARGET).o: $(TARGET).cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(SRC_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(OBJPARSER_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(RENDER_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(RENDER_DIR)/*.o $(OBJPARSER_DIR)/*.o *.o $(TARGET)

.PHONY: clean

# Dependencies
$(TARGET): $(OBJ)


