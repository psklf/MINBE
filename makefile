# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS = -Wall
CFLAGS += -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXxf86vm -lXinerama -lXcursor -lXi -ldl

# the build target executable:
TARGET = GlWindow

all: $(TARGET)

$(TARGET): $(TARGET).cpp GlUtils.cpp glad.c
	$(CC) $(CFLAGS) -o $(TARGET).out ${TARGET}.cpp GlUtils.cpp glad.c $(CFLAGS)


clean:
	$(RM) $(TARGET)
