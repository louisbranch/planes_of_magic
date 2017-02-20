OBJS =
TEST = camera_test.cpp

CC = clang

COMPILER_FLAGS = -w

LINKER_FLAGS = -lm -lSDL2 -lSDL2_image -lnoise -lstdc++

OBJ_NAME = magic

all : $(OBJS)
	$(CC) main.cpp $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/$(OBJ_NAME)
	./bin/$(OBJ_NAME)

test: $(OBJS) $(TEST)
	$(CC) test.cpp $(OBJS) $(TEST) $(COMPILER_FLAGS) -lgtest $(LINKER_FLAGS) -o bin/test
	./bin/test
