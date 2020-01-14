#include "board.h"
#include "ia.h"

void board_init(board * b, theme * t)
{

	int i, j;

	for (i = 0; i < BOARD_HEXAGON_PER_LINE; ++i)
		for (j = 0; j < BOARD_HEXAGON_PER_LINE; ++j)
		{

			hexagon_setCoordinates(&b->cells[j][i], j, i);
			hexagon_init(&b->cells[j][i]);

		}

	b->player = P1;

	b->position.x = BOARD_OFFSET_X;
	b->position.y = BOARD_OFFSET_Y;

	board_setNotificationText(b, t, "Debut de la partie. C'est au joueur 1 (bleu) de commencer.", DEFAULT);

	b->path_count = 0;
	b->canceled_moves = 0;

	b->hist.first = NULL;
	b->hist.number_elt = 0;

	b->playable = false;
	b->finished = false;
	b->canceled = false;

}

void board_mouseClickHandle(SDL_Event * e, board * b, theme * t)
{

	if(b->playable && !b->finished)
		if (e->button.button == SDL_BUTTON_LEFT)
			board_leftClickHandle(e, b, t);

}

void board_leftClickHandle(SDL_Event * e, board * b, theme * t)
{

	int i, j;

	for (i = 0; i < BOARD_HEXAGON_PER_LINE; ++i)
		for (j = 0; j < BOARD_HEXAGON_PER_LINE; ++j)
			if (hexagon_inHexagon(&b->cells[j][i], e))
			{

				if (hexagon_getState(&b->cells[j][i]) == EMPTY)
				{

          board_updateHistory(b, t, &b->cells[j][i], b->player, b->path_count + 1 - b->canceled_moves);
          board_doMove(b, t, &b->cells[j][i], b->player);

          if (!(b->enemy == HUMAN) && !b->finished)
          {

            hexagon * move_ia = (b->enemy == IA1) ? moveIA1(b, t) : moveIA2(b);
            move_ia = (move_ia == NULL) ? moveIA1(b, t) : move_ia;

            board_updateHistory(b, t, move_ia, b->player, b->path_count + 1 - b->canceled_moves);
            board_doMove(b, t, move_ia, b->player);

          }

				}

				else
					if (b->player == P1)
						board_setNotificationText(b, t, "Mouvement incorrect pour le joueur 1 : l'hexagone n'est pas vide !", ERROR);
					else if (b->player == P2)
						board_setNotificationText(b, t, "Mouvement incorrect pour le joueur 2 : l'hexagone n'est pas vide !", ERROR);

			}

}

void board_mouseMotionHandle(SDL_Event * e, board * b)
{

	int i, j;

	if(b->playable && !b->finished)
		for (i = 0; i < BOARD_HEXAGON_PER_LINE; ++i)
			for (j = 0; j < BOARD_HEXAGON_PER_LINE; ++j)
				if (hexagon_inHexagon(&b->cells[j][i], e))
					hexagon_setHover(&b->cells[j][i], true);
				else
					hexagon_setHover(&b->cells[j][i], false);

}

void board_display(SDL_Surface * screen, theme * t, board * b)
{

	int i, j;

	if (b->playable)
	{

		SDL_BlitSurface(t->images[BOARD].image, NULL, screen, &b->position);

		for (i = 0; i < BOARD_HEXAGON_PER_LINE; ++i)
			for (j = 0; j < BOARD_HEXAGON_PER_LINE; ++j)
				hexagon_display(&b->cells[j][i], screen, t);

		history_display(&b->hist, screen);

	}

	SDL_BlitSurface(b->textNotificationSurface, NULL, screen, &b->textPosition);

}

hexagon * board_getHexagonByCoords(board * b, int x, int y)
{

	int i, j;

	for (i = 0; i < BOARD_HEXAGON_PER_LINE; ++i)
		for (j = 0; j < BOARD_HEXAGON_PER_LINE; ++j)
			if (hexagon_getCoordinateX(&b->cells[j][i]) == x && hexagon_getCoordinateY(&b->cells[j][i]) == y)
				return &b->cells[j][i];

	return NULL;

}

void board_setNotificationText(board * b, theme * t, const char * text, eColor c)
{

	static int freeMemory = 0;

	if (freeMemory)
		SDL_FreeSurface(b->textNotificationSurface);

		b->textNotificationSurface = TTF_RenderText_Blended(t->font, text, t->colors[c]);

		b->textPosition.x = (Sint16)(BOARD_TEXT_OFFSET_X + (630 - b->textNotificationSurface->w) / 2);
		b->textPosition.y = (Sint16)(BOARD_TEXT_OFFSET_Y + (65 - b->textNotificationSurface->h) / 2);


	freeMemory = 1;

}

int board_newPath(board * b)
{

	return ++b->path_count;

}

void board_pathConvert(board * b, eState player, int src, int dst)
{

	int i, j;

	for (i = 0; i < BOARD_HEXAGON_PER_LINE; ++i)
		for (j = 0; j < BOARD_HEXAGON_PER_LINE; ++j)
			if (b->cells[j][i].state == player)
				if (b->cells[j][i].path == src)
						b->cells[j][i].path = dst;

}

bool board_pathComplete(board * b, eState player, int path)
{

	int i, j;

	bool result_first = false;
	bool result_last = false;

	if (player == P1)
	{

		for (i = 0; i < BOARD_HEXAGON_PER_LINE; ++i)
			for (j = 0; j < BOARD_HEXAGON_PER_LINE; ++j)
				if (b->cells[j][i].state == player)
					if (b->cells[j][i].path == path)
					{

						if (hexagon_getCoordinateX(&b->cells[j][i]) == 0)
							result_first = true;
						else if (hexagon_getCoordinateX(&b->cells[j][i]) == (BOARD_HEXAGON_PER_LINE - 1))
							result_last = true;

					}

	}

	else
	{

		for (i = 0; i < BOARD_HEXAGON_PER_LINE; ++i)
			for (j = 0; j < BOARD_HEXAGON_PER_LINE; ++j)
				if (b->cells[j][i].state == player)
					if (b->cells[j][i].path == path)
					{

						if (hexagon_getCoordinateY(&b->cells[j][i]) == 0)
							result_first = true;
						else if (hexagon_getCoordinateY(&b->cells[j][i]) == (BOARD_HEXAGON_PER_LINE - 1))
							result_last = true;

					}

	}

	return (result_first & result_last);

}

eState board_gameWinner(board * b)
{

	if (board_pathComplete(b, P1, b->path_count))
	{
		b->finished = true;
		return P1;
	}
	else if (board_pathComplete(b, P2, b->path_count))
	{
		b->finished = true;
		return P2;
	}
	else
		return EMPTY;

}

void board_close(board * b)
{

	history_close(&b->hist);

}

void board_updateHistory(board * b, theme * t, hexagon * h, eState player, int number)
{

	char text[32];

	sprintf(text, "J%d en %s (%d)", player, hexagon_getName(h), number);

	history_add(&b->hist, historyline_create(t, h, player, text));

}

void board_updateHistoryInverse(board * b, theme * t, hexagon * h, eState player, int number)
{

	char text[32];

	sprintf(text, "J%d en %s (%d)", player, hexagon_getName(h), number);

	history_add_inverse(&b->hist, historyline_create(t, h, player, text));

}

void board_cancelMove(board * b, theme * t)
{

	if(!b->finished)
		if (b->playable && !b->canceled && b->path_count)
		{

			b->player = (b->player == P1) ? P2 : P1;
			b->last_cell_move->state = EMPTY;
			b->last_cell_move->path = 0;

			history_del(&b->hist);

			b->canceled = true;
			++b->canceled_moves;

			board_setNotificationText(b, t, "Votre coup a ete annule.", SUCCESS);

		}

		else
			board_setNotificationText(b, t, "Vous ne pouvez pas annuler deux coups d'affilee !", ERROR);

	else
		board_setNotificationText(b, t, "Vous ne pouvez pas annuler ce coup (partie terminee) !", ERROR);

}

void board_saveGame(board * b, theme * t, const char * filename)
{

	if (b->playable)
	{

		int i, j;

		FILE * file_save = NULL;
		file_save = fopen(filename, "w");

		fprintf(file_save, "\\hex\n\\board\n");

		for (i = 0; i < BOARD_HEXAGON_PER_LINE; ++i)
		{

			for (j = 0; j < BOARD_HEXAGON_PER_LINE; ++j)
				if (hexagon_getState(&b->cells[j][i]) == P1)
					fprintf(file_save, "%c", 'B');
				else if (hexagon_getState(&b->cells[j][i]) == P2)
					fprintf(file_save, "%c", 'R');
				else
					fprintf(file_save, "%c", '.');

				fprintf(file_save, "\n");

		}

		fprintf(file_save, "\\endboard\n\\game\n");

		historyline * current = b->hist.first;

		while (current)
		{

			fprintf(file_save, "\\play %c %d %d\n", (current->player == P1) ? 'A' : 'B', current->hex->x, current->hex->y);
			current = current->next;

		}

		fseek(file_save, 0, SEEK_END);

		fprintf(file_save, "\\endgame\n\\endhex");

		fclose(file_save);

		board_setNotificationText(b, t, "Partie sauvegardee avec succes.", SUCCESS);

	}

}

bool board_loadGame(board * b, theme * t, const char * filename)
{

	FILE * file_save = NULL;
	file_save = fopen(filename, "r");

	if (file_save == NULL)
		return false;

	char line[16];
	char c;
	char player;
	int x, y;

	int i, j;

	fscanf(file_save, "%s\n", line);
	if (strcmp(line, "\\hex"))
	{
		fclose(file_save);
		return false;
	}

	fscanf(file_save, "%s\n", line);
	if (strcmp(line, "\\board"))
	{
		fclose(file_save);
		return false;
	}

	board_close(b);
	board_init(b, t);

	b->playable = true;
	b->path_count = 0;

	for (i = 0; i < 11; ++i)
		for (j = 0; j < 11; ++j)
		{

			if (j == (11 - 1))
				fscanf(file_save, "%c\n", &c);
			else
				fscanf(file_save, "%c", &c);

			switch (c)
			{

				case 'B':
					board_doMove(b, t, &b->cells[j][i], P1);
					break;

				case 'R':
					board_doMove(b, t, &b->cells[j][i], P2);
					break;

				default:
					break;

			}

		}

	fscanf(file_save, "%s\n", line);
	if (strcmp(line, "\\endboard"))
	{
		fclose(file_save);
		return false;
	}

	fscanf(file_save, "%s\n", line);
	if (strcmp(line, "\\game"))
	{
		fclose(file_save);
		return false;
	}

	for (i = 0; i < b->path_count; ++i)
	{

		fscanf(file_save, "\\play %c", &player);
		fscanf(file_save, " %d", &x);
		fscanf(file_save, " %d\n", &y);

		if (player == 'A' && board_getHexagonByCoords(b, x, y)->state == P1)
		{
			board_updateHistoryInverse(b, t, board_getHexagonByCoords(b, x, y), P1, (b->path_count - i));
			if(!i)
				b->last_cell_move = board_getHexagonByCoords(b, x, y);
		}
		else if (player == 'B' && board_getHexagonByCoords(b, x, y)->state == P2)
		{
			board_updateHistoryInverse(b, t, board_getHexagonByCoords(b, x, y), P2, (b->path_count - i));
			if(!i)
				b->last_cell_move = board_getHexagonByCoords(b, x, y);
		}
		else
			return false;

	}

	fscanf(file_save, "%s\n", line);
	if (strcmp(line, "\\endgame"))
	{
		fclose(file_save);
		return false;
	}

	fscanf(file_save, "%s\n", line);
	if (strcmp(line, "\\endhex"))
	{
		fclose(file_save);
		return false;
	}

	fclose(file_save);

	return true;

}

void board_convertNeighboorsPath(board * b, hexagon * h)
{

	int k, l;

	for (k = h->y - 1; k < h->y + 2; ++k)
		for (l = h->x - 1; l < h->x + 2; ++l)
			if(board_getHexagonByCoords(b, l, k))
				if (!(l == h->x && k == h->y) && !(l == h->x - 1 && k == h->y - 1) && !(l == h->x + 1 && k == h->y + 1))
					board_pathConvert(b, h->state, board_getHexagonByCoords(b, l, k)->path, h->path);

}

void board_doMove(board * b, theme * t, hexagon * h, eState player)
{

	hexagon_setState(h, player);

	h->path = board_newPath(b);
	board_convertNeighboorsPath(b, h);

	b->player = (b->player == P1) ? P2 : P1;
	b->last_cell_move = h;
	b->canceled = false;

	if (board_gameWinner(b) == P1)
		board_setNotificationText(b, t, "Le joueur 1 (bleu) a gagne !", SUCCESS);
	else if (board_gameWinner(b) == P2)
		board_setNotificationText(b, t, "Le joueur 2 (rouge) a gagne !", SUCCESS);
	else if (b->player == P1)
		board_setNotificationText(b, t, "C'est le tour du joueur 1 (bleu).", DEFAULT);
	else if (b->player == P2)
		board_setNotificationText(b, t, "C'est le tour du joueur 2 (rouge).", DEFAULT);

}
