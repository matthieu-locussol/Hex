#include "board.h"
#include "hexagon.h"

void hexagon_init(hexagon * h)
{

	h->path = 0;
	h->hover = 0;
	h->state = EMPTY;

	h->position.x = (Sint16)(h->y * HEXAGON_OFFSET_X + h->x * HEXAGON_WIDTH + BOARD_OFFSET_X + HEXAGON_BOARD_OFFSET);
	h->position.y = (Sint16)(h->y * HEXAGON_OFFSET_Y + BOARD_OFFSET_Y + HEXAGON_BOARD_OFFSET);

}

bool hexagon_inTopLeftCorner(hexagon * h, SDL_Event * e)
{

	bool result = false;
	int i, j;

	for (j = 0; j < 8; ++j)
		for (i = 0; i < (16 - 2 * j); ++i)
			result |= ((e->motion.x - h->position.x) == i && (e->motion.y - h->position.y) == j);

	return result;

}

bool hexagon_inTopRightCorner(hexagon * h, SDL_Event * e)
{

	bool result = false;
	int i, j;

	for (j = 0; j < 8; ++j)
		for (i = (15 + 2 * j); i < 31; ++i)
			result |= ((e->motion.x - h->position.x) == i && (e->motion.y - h->position.y) == j);

	return result;

}

bool hexagon_inBottomLeftCorner(hexagon * h, SDL_Event * e)
{

	bool result = false;
	int i, j;

	for (j = 25; j < 33; ++j)
		for (i = 0; i < (16 - 2 * (32 - j)); ++i)
			result |= ((e->motion.x - h->position.x) == i && (e->motion.y - h->position.y) == j);

	return result;

}

bool hexagon_inBottomRightCorner(hexagon * h, SDL_Event * e)
{

	bool result = false;
	int i, j;

	for (j = 25; j < 33; ++j)
		for (i = (15 + 2 * (32 - j)); i < 31; ++i)
			result |= ((e->motion.x - h->position.x) == i && (e->motion.y - h->position.y) == j);

	return result;

}

bool hexagon_inSideBorders(hexagon * h, SDL_Event * e)
{

	bool result = false;
	int i;

	for (i = 8; i < 25; ++i)
		result |= ((e->motion.x - h->position.x) == 0 && (e->motion.y - h->position.y) == i) || ((e->motion.x - h->position.x) == 30 && (e->motion.y - h->position.y) == i);

	return result;

}

bool hexagon_inSurface(hexagon * h, SDL_Event * e)
{

	return (e->motion.x - h->position.x) >= 0 && (e->motion.x - h->position.x) <= 30 && (e->motion.y - h->position.y) >= 0 && (e->motion.y - h->position.y) <= 32;

}

bool hexagon_inHexagon(hexagon * h, SDL_Event * e)
{

	return hexagon_inSurface(h, e) && !(hexagon_inBottomRightCorner(h, e) || hexagon_inBottomLeftCorner(h, e) || hexagon_inTopRightCorner(h, e) || hexagon_inTopLeftCorner(h, e) || hexagon_inSideBorders(h, e));

}

void hexagon_display(hexagon * h, SDL_Surface * screen, theme * t)
{

	if (h->state == P1)
		SDL_BlitSurface(t->images[HEX_P1].image, NULL, screen, &h->position);
	else if (h->state == P2)
		SDL_BlitSurface(t->images[HEX_P2].image, NULL, screen, &h->position);
	else if (h->hover)
		SDL_BlitSurface(t->images[HEX_HOVER].image, NULL, screen, &h->position);
	else
		SDL_BlitSurface(t->images[HEX].image, NULL, screen, &h->position);

}

void hexagon_setCoordinates(hexagon * h, int x, int y)
{

	h->x = x;
	h->y = y;

}

int hexagon_getCoordinateX(hexagon * h)
{

	return h->x;

}

int hexagon_getCoordinateY(hexagon * h)
{

	return h->y;

}

void hexagon_setHover(hexagon * h, bool hover)
{

	if (!h->hover && hover)
		h->hover = true;
	else if (h->hover && !hover)
		h->hover = false;

}

bool hexagon_getHover(hexagon * h)
{

	return h->hover;

}

void hexagon_setState(hexagon * h, eState state)
{

	if (h->state != state)
		h->state = state;

}

eState hexagon_getState(hexagon * h)
{

	return h->state;

}

SDL_Rect * hexagon_getPosition(hexagon * hex)
{

	return &hex->position;

}

char * hexagon_getName(hexagon * hex)
{

	char * hexName = malloc(sizeof(char) * 5);

	sprintf(hexName, "%c%d%c", hex->x + 65, hex->y + 1, '\0');

	return hexName;

}
