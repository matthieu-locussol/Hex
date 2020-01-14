#ifndef _HEX_HISTORY_
#define _HEX_HISTORY_

#define HISTORY_LINES_NUMBER 18

#define HISTORY_OFFSET_X 920
#define HISTORY_OFFSET_Y 68

#define HISTORY_LINE_WIDTH 158
#define HISTORY_LINE_HEIGHT 32

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "hexagon.h"
#include "theme.h"

/**
 *	@defgroup history Structure HISTORY
 *  @brief Definition de la structure history et de ses fonctions
 *  @{
 */

typedef struct historyline historyline;
struct historyline {

	SDL_Surface * content;
	hexagon * hex;
	historyline * next;
	eState player;

};

struct history {

	historyline * first;
	int number_elt;

};
typedef struct history history;

/** @brief Affiche l'historique à l'écran
 *
 * @param h l'historique à afficher
 * @param screen la SDL_Surface sur laquelle on va blitter l'historique
 */
void history_display(history * h, SDL_Surface * screen);

/** @brief Ajoute une ligne d'historique à l'historique
 *
 * @param h l'historique dans lequel on veut stocker le coup
 * @param x la ligne d'historique correspondant au coup
 */
void history_add(history * h, historyline * x);

/** @brief Ajoute une ligne d'historique à la fin de l'historique
 *
 * @param h l'historique dans lequel on veut stocker le coup
 * @param x la ligne d'historique correspondante au coup à ajouter
 */
void history_add_inverse(history * h, historyline * x);

/** @brief Supprime une ligne d'historique de l'historique
 *
 * @param h l'historique dans lequel on veut enlever le coup
 * @param x la ligne d'historique correspondante au coup à supprimer
 */
void history_del(history * h);

/** @brief Libère la mémoire utilisée par l'historique
 *
 * @param h l'historique à libérer
 */
void history_close(history * h);

/** @brief Affiche une ligne d'historique à l'écran
 *
 * @param x la ligne d'historique à afficher
 * @param screen la SDL_Surface sur laquelle on va blitter la ligne d'historique
 * @param position la position de la ligne d'historique (première, deuxième..)
 */
void historyline_display(historyline * x, SDL_Surface * screen, int position);

/** @brief Créer une nouvelle ligne d'historique
 *
 * @param t le thème utilisé par la ligne d'historique
 * @param h l'hexagone qui a été posé
 * @param player le joueur qui a posé l'hexagone
 * @param text le texte à afficher dans la ligne d'historique
 * @return la ligne d'historique nouvellement créée
 */
historyline * historyline_create(theme * t, hexagon * h, eState player, const char * text);

/** @} */

#endif
