CC := gcc
CXX := g++

CFLAGS := -O0 -g
CXXFLAGS := -O0 -g

OBJ := weighted_uniform_sampler_test weighted_uniform_sampler random_variable
OBJS := $(addsuffix .o,$(OBJ))

TARGET := wusampler_exe
all:
	make compile

compile:
	@echo "Compiling ..."
	-make $(OBJS)
	-make $(TARGET)

$(TARGET): $(OBJS)
	-$(CXX) -o $(TARGET) $(OBJS)
	-./$(TARGET)

weighted_uniform_sampler_test.o: weighted_uniform_sampler_test.c
	-$(CC) -c -o weighted_uniform_sampler_test.o weighted_uniform_sampler_test.c

weighted_uniform_sampler.o: weighted_uniform_sampler.c
	-$(CC) -c -o weighted_uniform_sampler.o weighted_uniform_sampler.c

random_variable.o: random_variable.cpp
	-$(CXX) -c -o random_variable.o random_variable.cpp

clean:
	-rm -rf *.o $(TARGET)