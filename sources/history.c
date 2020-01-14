#include "history.h"

void history_display(history * h, SDL_Surface * screen)
{

	historyline * actuel = h->first;

	int i;

	for (i = 0; i < HISTORY_LINES_NUMBER && actuel != NULL; ++i)
	{

		historyline_display(actuel, screen, i);
		actuel = actuel->next;

	}

}

void history_add(history * h, historyline * x)
{

	x->next = h->first;
	h->first = x;

	++h->number_elt;

}

void history_add_inverse(history * h, historyline * x)
{

	historyline * current = h->first;

	x->next = NULL;

	if (current)
	{

		while (current->next)
			current = current->next;

		current->next = x;

	}

	else
		h->first = x;

	++h->number_elt;

}

void history_del(history * h)
{

	historyline * to_delete = h->first;

	if (h->first)
	{

		h->first = h->first->next;
		free(to_delete);

	}

	--h->number_elt;

}

void history_close(history * h)
{

	historyline * current = h->first;
	historyline * temp = NULL;

	while (current)
	{

		SDL_FreeSurface(current->content);
		temp = current;
		current = current->next;
		free(temp);

	}

}

void historyline_display(historyline * x, SDL_Surface * screen, int position)
{

	SDL_Rect pos;
	
	pos.x = (Sint16)(HISTORY_OFFSET_X + (HISTORY_LINE_WIDTH - x->content->w) / 2);
	pos.y = (Sint16)(HISTORY_OFFSET_Y + (HISTORY_LINE_HEIGHT - x->content->h) / 2);

	if(position % 2 == 0)
		pos.y += (Sint16)(position / 2 * HISTORY_LINE_HEIGHT + position / 2 * (HISTORY_LINE_HEIGHT + 1));
	else
		pos.y += (Sint16)((position + 1) / 2 * HISTORY_LINE_HEIGHT + (position - 1) / 2 * (HISTORY_LINE_HEIGHT + 1));

	SDL_BlitSurface(x->content, NULL, screen, &pos);

}

historyline * historyline_create(theme * t, hexagon * h, eState player, const char * text)
{

	historyline * x = (historyline *)malloc(sizeof(historyline));

	if (x == NULL)
		exit(EXIT_FAILURE);

	if(player == P1)
		x->content = TTF_RenderText_Blended(t->font, text, t->colors[C_P1]);
	else
		x->content = TTF_RenderText_Blended(t->font, text, t->colors[C_P2]);

	x->player = player;
	x->hex = h;

	return x;

}
