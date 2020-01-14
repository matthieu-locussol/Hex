CC = gcc
LDFLAGS = -Wall -Werror -g -std=c99 -ansi -lSDLmain -lSDL -lSDL_image -lSDL_ttf
EXE = hex_game
TEST = unit_test_hexagon

all: documentation $(EXE) $(TEST)

$(EXE): main.o game.o hexagon.o board.o theme.o menu.o history.o texture.o ia.o
	$(CC) -o $(EXE) main.o game.o hexagon.o board.o theme.o menu.o history.o texture.o ia.o $(LDFLAGS)

main.o: main.c game.h
	$(CC) -o main.o -c main.c $(LDFLAGS)

game.o: game.c game.h board.h theme.h menu.h
	$(CC) -o game.o -c game.c $(LDFLAGS)

hexagon.o: hexagon.c hexagon.h board.h
	$(CC) -o hexagon.o -c hexagon.c $(LDFLAGS)

board.o: board.c board.h hexagon.h theme.h history.h ia.h
	$(CC) -o board.o -c board.c $(LDFLAGS)

theme.o: theme.c theme.h texture.h
	$(CC) -o theme.o -c theme.c $(LDFLAGS)

menu.o: menu.c menu.h theme.h board.h
	$(CC) -o menu.o -c menu.c $(LDFLAGS)

history.o: history.c history.h hexagon.h theme.h
	$(CC) -o history.o -c history.c $(LDFLAGS)

texture.o: texture.c texture.h
	$(CC) -o texture.o -c texture.c $(LDFLAGS)

ia.o: ia.c ia.h board.h
	$(CC) -o ia.o -c ia.c $(LDFLAGS)

unit_test_hexagon: unit_test_hexagon.o hexagon.o theme.o texture.o
	$(CC) -o unit_test_hexagon unit_test_hexagon.o hexagon.o theme.o texture.o $(LDFLAGS)

unit_test_hexagon.o: unit_test_hexagon.c hexagon.h theme.h texture.h
	$(CC) -o unit_test_hexagon.o -c unit_test_hexagon.c $(LDFLAGS)

documentation:
	doxygen docparameters

clean:
	rm -rf *.o documentation/

mrproper: clean
	rm $(EXE) $(TEST)
