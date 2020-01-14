#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "game.h"

int main(int argc, char * argv[])
{
	(void)argc;
	(void)argv;

	srand(time(NULL));

	int time_elapsed = 0;
	int time_previous_elapsed = 0;

	SDL_Event action;
	SDL_Surface * screen = NULL;

	board plateau;
	buttonGroup bg;
	theme current_theme;

	window_init(&screen);
	game_init(&plateau, &bg, &current_theme);

	while (game_eventHandling(&plateau, &bg, &current_theme, &action)) {
		game_display(&plateau, &bg, &current_theme, screen);
		game_pause(&time_elapsed, &time_previous_elapsed);
	}

	game_close(&plateau, &bg, &current_theme);
	window_close();

	return EXIT_SUCCESS;
}
