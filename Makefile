OBJS = input/keyboard.cpp math/math.cpp camera/camera.cpp map/map.cpp img/img.cpp
TEST = camera/camera_test.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image -lnoise

OBJ_NAME = magic

all : $(OBJS)
	$(CC) main.cpp $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/$(OBJ_NAME)
	./bin/$(OBJ_NAME)

test: $(OBJS) $(TEST)
	$(CC) test.cpp $(OBJS) $(TEST) $(COMPILER_FLAGS) -lgtest $(LINKER_FLAGS) -o bin/test
	./bin/test
