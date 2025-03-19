# Hämta OS-namnet via uname. 
# Om uname inte finns (t.ex. ren Windows utan MSYS), sätt OS till Windows_NT.
OBJ = main.o initSDL.o toolSDL.o map_maker.o mapISO.o game.o

OS := $(shell uname -s 2>/dev/null)
ifeq ($(OS),)
  OS := Windows_NT
endif

ifeq ($(OS), Darwin)
    # --- macOS Settings ---
    # Variables for compiler and flags
    CC = clang
    CFLAGS = -fsanitize=address -g -c \
             -I/opt/homebrew/include/SDL2 \
             -I/opt/homebrew/include/SDL2_image \
             -I/opt/homebrew/include/SDL2_ttf \
             -I/opt/homebrew/include/SDL2_mixer \
             -I/opt/homebrew/include/SDL2_net
    LDFLAGS = -fsanitize=address \
              -I/opt/homebrew/include/SDL2 \
              -L/opt/homebrew/lib \
              -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf \
              -lSDL2_mixer -lSDL2_net

    # File names
    EXEC = Isometric

else ifeq ($(OS), Windows_NT)
    # --- Windows (MinGW/MSYS) Settings ---
    # Adjust these paths for your environment:
    CC = gcc
    # If your SDL2 is in C:/SDL2, for example:
    CFLAGS = -g -c \
             -IC:/SDL2/include \
             -IC:/SDL2_image/include \
             -IC:/SDL2_ttf/include \
             -IC:/SDL2_mixer/include \
             -IC:/SDL2_net/include
    LDFLAGS = -LC:/SDL2/lib \
              -LC:/SDL2_image/lib \
              -LC:/SDL2_ttf/lib \
              -LC:/SDL2_mixer/lib \
              -LC:/SDL2_net/lib \
              -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

    EXEC = Isometric.exe

endif

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