#include "theme.h"

void theme_init(theme * t, eTheme type)
{

	static int freeMemory = 0;

	if (t->value != type)
	{

		if (freeMemory)
			theme_close(t);

		t->value = type;

		switch (t->value)
		{

			case DARK:
				theme_loadDark(t);
				break;

			case BLUE:
				theme_loadBlue(t);
				break;

		}

		texture_loading(t->images);

	}

	freeMemory = 1;

}

void theme_loadDark(theme * t)
{

	t->colors[DEFAULT] = (SDL_Color) { 221, 221, 221 };
	t->colors[SUCCESS] = (SDL_Color) { 62, 148, 117 };
	t->colors[ERROR] = (SDL_Color) { 211, 106, 95 };
	t->colors[C_P1] = (SDL_Color) { 60, 154, 201 };
	t->colors[C_P2] = (SDL_Color) { 211, 106, 95 };

	t->font = TTF_OpenFont("fonts/audiowide.ttf", 13);

	texture_nameLoading(&t->images[BACKGROUND], "dark_theme/background.png");
	texture_nameLoading(&t->images[BOARD], "dark_theme/board.png");
	texture_nameLoading(&t->images[HEX], "dark_theme/hexa.png");
	texture_nameLoading(&t->images[HEX_HOVER], "dark_theme/hexa_hover.png");
	texture_nameLoading(&t->images[HEX_P1], "dark_theme/hexa_p1.png");
	texture_nameLoading(&t->images[HEX_P2], "dark_theme/hexa_p2.png");
	texture_nameLoading(&t->images[BUTTON], "dark_theme/button.png");
	texture_nameLoading(&t->images[BUTTON_HOVER], "dark_theme/button_hover.png");

}

void theme_loadBlue(theme * t)
{

	t->colors[DEFAULT] = (SDL_Color) { 255, 255, 255 };
	t->colors[SUCCESS] = (SDL_Color) { 46, 204, 113 };
	t->colors[ERROR] = (SDL_Color) { 231, 76, 60 };
	t->colors[C_P1] = (SDL_Color) { 60, 154, 201 };
	t->colors[C_P2] = (SDL_Color) { 211, 106, 95 };

	t->font = TTF_OpenFont("fonts/audiowide.ttf", 13);

	texture_nameLoading(&t->images[BACKGROUND], "blue_theme/background.png");
	texture_nameLoading(&t->images[BOARD], "blue_theme/board.png");
	texture_nameLoading(&t->images[HEX], "blue_theme/hexa.png");
	texture_nameLoading(&t->images[HEX_HOVER], "blue_theme/hexa_hover.png");
	texture_nameLoading(&t->images[HEX_P1], "blue_theme/hexa_p1.png");
	texture_nameLoading(&t->images[HEX_P2], "blue_theme/hexa_p2.png");
	texture_nameLoading(&t->images[BUTTON], "blue_theme/button.png");
	texture_nameLoading(&t->images[BUTTON_HOVER], "blue_theme/button_hover.png");

}

void theme_close(theme * t)
{

	texture_free(t->images);

	TTF_CloseFont(t->font);

}
