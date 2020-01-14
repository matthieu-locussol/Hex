#include "ia.h"

hexagon * moveIA1(board * b, theme * t)
{

	static int b_coordX, b_coordY, b_side;
  static hexagon * lastmove = NULL;

	/* Premier coup à être joué */
	if (lastmove == NULL)
	{

		b_coordX = rand() % 11;
		b_side = rand() % 2;

		if (b_side == 1)
			b_coordY = 10;
    else
      b_coordY = 0;

		while (b->cells[b_coordX][b_coordY].state != EMPTY)
			b_coordX = rand() % 11;

    lastmove = &b->cells[b_coordX][b_coordY];

		return lastmove;

	}

  if(b_side == 1) /* On fait un chemin vers le haut */
  {

    if(hexagon_getState(&b->cells[lastmove->x][lastmove->y - 1]) == EMPTY) /* Peut-on jouer sur la case juste au dessus ? */
      lastmove = &b->cells[lastmove->x][lastmove->y - 1];
    else /* Si on ne peut pas... */
    {

      if(lastmove->x > 0 && lastmove->y < BOARD_HEXAGON_PER_LINE - 1 && hexagon_getState(&b->cells[lastmove->x + 1][lastmove->y - 1]) == EMPTY)
        lastmove = &b->cells[lastmove->x + 1][lastmove->y - 1];
      else if(lastmove->x < BOARD_HEXAGON_PER_LINE - 1 && hexagon_getState(&b->cells[lastmove->x + 1][lastmove->y]) == EMPTY) /* Si on est pas au bord droit et que l'hexagone est vide */
        lastmove = &b->cells[lastmove->x + 1][lastmove->y];
      else if(lastmove->x > 0 && hexagon_getState(&b->cells[lastmove->x - 1][lastmove->y]) == EMPTY) /* Si on est pas au bord gauche et que l'hexagone est vide */
        lastmove = &b->cells[lastmove->x - 1][lastmove->y];
      else if(lastmove->x < BOARD_HEXAGON_PER_LINE - 1 && lastmove->y < 0 && hexagon_getState(&b->cells[lastmove->x + 1][lastmove->y - 1]) == EMPTY)
        lastmove = &b->cells[lastmove->x - 1][lastmove->y + 1];
      else
        lastmove = NULL;

    }

  }

  else /* on fait un chemin vers le bas*/
  {

    if(hexagon_getState(&b->cells[lastmove->x][lastmove->y + 1]) == EMPTY) /* Peut-on jouer sur la case juste au dessus ? */
      lastmove = &b->cells[lastmove->x][lastmove->y + 1];
    else /* Si on ne peut pas... */
    {

      if(lastmove->x > 0 && lastmove->y < BOARD_HEXAGON_PER_LINE - 1 && hexagon_getState(&b->cells[lastmove->x - 1][lastmove->y + 1]) == EMPTY)
        lastmove = &b->cells[lastmove->x - 1][lastmove->y + 1];
      else if(lastmove->x < BOARD_HEXAGON_PER_LINE - 1 && hexagon_getState(&b->cells[lastmove->x + 1][lastmove->y]) == EMPTY) /* Si on est pas au bord droit et que l'hexagone est vide */
        lastmove = &b->cells[lastmove->x + 1][lastmove->y];
      else if(lastmove->x > 0 && hexagon_getState(&b->cells[lastmove->x - 1][lastmove->y]) == EMPTY) /* Si on est pas au bord gauche et que l'hexagone est vide */
        lastmove = &b->cells[lastmove->x - 1][lastmove->y];
      else if(lastmove->x < BOARD_HEXAGON_PER_LINE - 1 && lastmove->y < 0 && hexagon_getState(&b->cells[lastmove->x + 1][lastmove->y - 1]) == EMPTY)
        lastmove = &b->cells[lastmove->x + 1][lastmove->y - 1];
      else
        lastmove = NULL;

    }

  }

	return lastmove;

}

hexagon * moveIA2(board * b)
{

	(void)b;

	return NULL;

}
