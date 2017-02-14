OBJS = main.cpp input/keyboard.cpp math/math.cpp camera/camera.cpp map/map.cpp img/img.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image -lnoise

OBJ_NAME = magic

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/$(OBJ_NAME)
