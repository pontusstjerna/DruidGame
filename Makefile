SRC_DIR=druidgame
OBJ_DIR=obj
SRC_FILES=$(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES=$(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.cpp, %.o, $(SRC_FILES))))

ifeq ($(OS), Windows_NT)
	I_DIR=D:\\dev\\vcpkg\\installed\\x64-mingw-dynamic\\include
	L_DIR=D:\\dev\\vcpkg\\installed\\x64-mingw-dynamic\\lib -LD:\\dev\\vcpkg\\installed\\x64-mingw32-dynamic\\lib\\manual-link
else
	I_DIR=/mnt/d/dev/vcpkg/installed/x64-linux/include
	L_DIR=/mnt/d/dev/vcpkg/installed/x64-linux/lib
endif

ifeq ($(OS), Windows_NT)
	
else
	SYS_FLAGS=-pthread
endif

CC=g++

LDFLAGS=-L$(L_DIR) -lSDL2 -lSDL2_image -lSDL2main -lbox2d 
CPPFLAGS=-std=c++17 -I$(I_DIR)

all: print directories druidgame

print:
	@echo Making druid game.

directories: $(OBJ_DIR)

$(OBJ_DIR): 
	mkdir $(OBJ_DIR)

druidgame: $(OBJ_FILES)
	@echo Linking...
	$(CC) $(SYS_FLAGS) $^ $(LDFLAGS) -o game

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS)

.PHONY: clean directories

clean:
ifeq ($(OS), Windows_NT)
	rd /s obj
else
	rm -rf $(OBJ_DIR) game
endif