OBJS = main.cpp input/keyboard.cpp math/math.cpp camera/camera.cpp map/map.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lnoise

OBJ_NAME = worlds

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/$(OBJ_NAME)
