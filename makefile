GXX = g++
SRC = $(wildcard ./src/*.cpp)
CXXFLAGS = -I./raylib/src
LDFLAGS_WIN =  -L./raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm
LDFLAGS_LINUX = -L./raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

WARNING_FLAGS = -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion -Werror

OUT_WIN = app.exe
OUT_LINUX = app.out

.PHONY: build_win build_linux run_win run_linux windows linux 

dependencies: 
	@rmdir /s /q .\raylib\ 
	@git clone --recurse-submodules https://github.com/raysan5/raylib.git
	@git submodule update --init --recursive
	@cd ./raylib/src && make PLATFORM=PLATFORM_DESKTOP

build_win: 
	@$(GXX) $(SRC) $(CXXFLAGS) $(LDFLAGS_WIN) -o $(OUT_WIN)

build_linux: 
	@$(GXX) $(SRC) $(CXXFLAGS) $(LDFLAGS_LINUX) -o $(OUT_LINUX)

run_win: build_win
	@./$(OUT_WIN)

run_linux: build_linux
	@./$(OUT_LINUX)

windows: dependencies run_win

linux: dependencies run_linux

clean:
	@rm -f $(OUT_WIN) $(OUT_LINUX)