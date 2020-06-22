# Note this Makefile is intended for a Mac OS

LDFLAGS = -framework GLUT -framework OpenGL
CC = g++ 
CFLAGS = -std=c++14 -w -O3

all: main Game Graphics Interface Objects AI KeyManager
	$(CC) $(CFLAGS) -o snake.exe main.o Game.o Graphics.o Interface.o Objects.o AI.o KeyManager.o $(LDFLAGS)

main: 
	$(CC) $(CFLAGS) main.cpp -c

Game:
	$(CC) $(CFLAGS) Game.cpp -c

Graphics:
	$(CC) $(CFLAGS) Graphics.cpp -c

Interface:
	$(CC) $(CFLAGS) Interface.cpp -c

Objects:
	$(CC) $(CFLAGS) Objects.cpp -c

AI:
	$(CC) $(CFLAGS) AI.cpp -c

KeyManager:
	$(CC) $(CFLAGS) KeyManager.cpp -c

clean:
	rm snake.exe main.o Game.o Graphics.o Interface.o Objects.o AI.o KeyManager.o



