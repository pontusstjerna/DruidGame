SRC_DIR=druidgame
OBJ_DIR=obj
SRC_FILES=$(wildcard $(SRC_DIR)/**/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
I_DIR=D:/dev/vcpkg/installed/x64-windows/include
L_DIR=D:/dev/vcpkg/installed/x64-windows/lib

CC=g++
CPPFLAGS=-I$(I_DIR) -L$(L_DIR)

all: directories druidgame

directories: $(OBJ_DIR)

$(OBJ_DIR): 
	mkdir $(OBJ_DIR)

druidgame: $(OBJ_FILES)
	echo "Making druid game."
	$(CC) -g $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<
	
.PHONY: clean

clean:
	rm -rf $(OBJ_DIR)