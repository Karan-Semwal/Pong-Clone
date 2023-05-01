# compiler
GCC= g++
CLANG=clang

# compiler flags
Flags= -std=c++17 -O3

Link= -lsfml-graphics -lsfml-window -lsfml-system -lstdc++

Src_Dir=./src/
Exec_Dir=./bin/

g++: main Game
	$(GCC) -o Pong $(Flags) \
	$(Exec_Dir)main.o \
	$(Exec_Dir)Game.o \
	$(Link)

clang: main Game
	$(CLANG) -o Pong $(Flags) \
	$(Exec_Dir)main.o \
	$(Exec_Dir)Game.o \
	$(Link)


# generate main.o obj file
main: $(Src_Dir)main.cpp
	$(GCC) -c $(Src_Dir)main.cpp -o $(Exec_Dir)main.o

# generate Game.o obj file
Game: $(Src_Dir)Game.cpp
	$(GCC) -c $(Src_Dir)Game.cpp -o $(Exec_Dir)Game.o

run: 
	./Pong

clean:
	rm -rf Pong
	rm -rf $(Exec_Dir)*.o
