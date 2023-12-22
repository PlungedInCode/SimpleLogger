CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb -g

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= main

CPPCHECK = cppcheck

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

cppcheck:
	@$(CPPCHECK) --quiet --enable=all --error-exitcode=1 --inline-suppr \
		-I $(INCLUDE) $(SRC) -i external/printf --suppress=missingIncludeSystem .
