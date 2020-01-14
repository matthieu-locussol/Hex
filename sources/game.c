#include "game.h"

void window_init(SDL_Surface ** screen)
{

	SDL_Init(SDL_INIT_VIDEO);

	*screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	SDL_WM_SetCaption(WINDOW_TITLE, NULL);

	TTF_Init();

}

void game_init(board * b, buttonGroup * bg, theme * t)
{

	theme_init(t, DEFAULT_THEME);

	board_init(b, t);

	buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_MAIN);

}

bool game_eventHandling(board * b, buttonGroup * bg, theme * t, SDL_Event * e)
{

	while (SDL_PollEvent(e))
	{

		switch (e->type)
		{

			case SDL_QUIT:
				return false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				board_mouseClickHandle(e, b, t);
				buttonGroup_mouseClickHandle(b, bg, t, e);
				if (b->finished)
					buttonGroup_initButtonGroup(b, bg, t, bg->type);
				break;

			case SDL_MOUSEMOTION:
				board_mouseMotionHandle(e, b);
				buttonGroup_mouseMotionHandle(bg, e);
				break;

			case SDL_KEYDOWN:
				{

					switch (e->key.keysym.sym)
					{

						case SDLK_F1:
							theme_init(t, DARK);
							buttonGroup_initButtonGroup(b, bg, t, bg->type);
							board_setNotificationText(b, t, "Theme modifie (DARK).", SUCCESS);
							break;

						case SDLK_F2:
							theme_init(t, BLUE);
							buttonGroup_initButtonGroup(b, bg, t, bg->type);
							board_setNotificationText(b, t, "Theme modifie (BLUE).", SUCCESS);
							break;

						default:
							break;

					}

				}
				break;

			default:
				break;

		}

	}

	return true;

}

void game_display(board * b, buttonGroup * bg, theme * t, SDL_Surface * screen)
{

	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

	SDL_BlitSurface(t->images[BACKGROUND].image, NULL, screen, NULL);

	board_display(screen, t, b);
	buttonGroup_display(bg, screen, t);

	SDL_Flip(screen);

}

void game_pause(int * time_elapsed, int * time_previously_elapsed)
{

	*time_elapsed = SDL_GetTicks();

	if (*time_elapsed - *time_previously_elapsed > (1000 / GAME_FPS))
		*time_previously_elapsed = *time_elapsed;
	else
		SDL_Delay((1000 / GAME_FPS) - (*time_elapsed - *time_previously_elapsed));

}

void game_close(board * b, buttonGroup * bg, theme * t)
{

	board_close(b);

	buttonGroup_close(bg);

	theme_close(t);

}

void window_close()
{

	TTF_Quit();

	SDL_Quit();

}
