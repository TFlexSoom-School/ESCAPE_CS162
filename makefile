c# Tristan Hilbert
# 3/9/18
# Makefile for escape_from_CS162
#

CC = g++
FLAGS = -std=c++11
CURSE = -lncurses

EXECUTABLE = escape
DEBUG_EXECUTABLE = d_escape

# Get all cpp files
SOURCE_FILES := $(wildcard *.cpp)
CURSED_SOURCE_FILES := $(wildcard *.cc)
# Get all Objects
OBJECTS = $(SOURCE_FILES:%.cpp=%.o)
CURSED_OBJECTS = $(SOURCE_FILES:%.cc=%.o)

# Compile all Objects

all: $(EXECUTABLE)

debug: $(DEBUG_EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(DEBUG_EXECUTABLE)
	rm -f $(OBJECTS)

.cpp.o:	
	$(CC) $(FLAGS) -c $< -o $@

.cp.o:
	$(CC) $(FLAGS) $(CURSE) -c $< -o $@


$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $@

$(DEBUG_EXECUTABLE) : 
	$(CC) $(FLAGS) $(CURSE) $(SOURCE_FILES) -g -o $@



