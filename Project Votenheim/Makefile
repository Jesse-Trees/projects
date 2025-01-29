# THE NAME OF YOUR EXECUTABLE
TARGET = FP
# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = main.cpp character.cpp hero.cpp enemy.cpp area.cpp

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(OS),Windows_NT)
	TARGET := $(TARGET).exe
	DEL = del
	Q =

	INC_PATH = Z:/CSCI200/include/
	LIB_PATH = Z:/CSCI200/lib/

	ARCH = 
else
	DEL = rm -f
	Q = "

	INC_PATH = /usr/local/include/
	LIB_PATH = /usr/local/lib/

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		TARGET_MAKEFILE = Makefile.osx
		CXXFLAGS += -D OSX
	endif

	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		ARCH = 
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		ARCH = 
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		ARCH = 
	endif
endif

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(ARCH) -o $@ $^ -L$(LIB_PATH) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(ARCH) -o $@ -c $< -I$(INC_PATH)

clean:
	$(DEL) $(TARGET) $(OBJECTS)
	
depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

# DEPENDENCIES 
main.o: main.cpp character.h hero.h enemy.h area.h
character.o: character.cpp character.h
hero.o: hero.cpp hero.h character.h
enemy.o: enemy.cpp enemy.h character.h
area.o: area.cpp area.h enemy.h character.h hero.h
