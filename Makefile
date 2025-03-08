# Variables for compiler and flags
CC=clang
CFLAGS=-fsanitize=address -g -c -I/opt/homebrew/include/SDL2 -I/opt/homebrew/include/SDL2_image -I/opt/homebrew/include/SDL2_ttf -I/opt/homebrew/include/SDL2_mixer
LDFLAGS=-fsanitize=address -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# File names
OBJ=main.o initSDL.o toolSDL.o map_maker.o mapISO.o game.o #player.o menu.o #enemy.o
EXEC=Isometric

# Linking
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Compile source code
main.o: source/main.c
	$(CC) $(CFLAGS) source/main.c -o main.o

initSDL.o: source/initSDL.c
	$(CC) $(CFLAGS) source/initSDL.c -o initSDL.o

toolSDL.o: source/toolSDL.c
	$(CC) $(CFLAGS) source/toolSDL.c -o toolSDL.o

mapISO.o: source/mapISO.c
	$(CC) $(CFLAGS) source/mapISO.c -o mapISO.o

#player.o: source/player.c
#	$(CC) $(CFLAGS) source/player.c -o player.o

#menu.o: source/menu.c
#	$(CC) $(CFLAGS) source/menu.c -o menu.o

#enemy.o: source/enemy.c
#	$(CC) $(CFLAGS) source/enemy.c -o enemy.o

map_maker.o: source/map_maker.c
	$(CC) $(CFLAGS) source/map_maker.c -o map_maker.o

game.o: source/game.c
	$(CC) $(CFLAGS) source/game.c -o game.o

# Clean binaries
clean:
	rm -f *.o $(EXEC)

# Run the program
run: $(EXEC)
	./$(EXEC)