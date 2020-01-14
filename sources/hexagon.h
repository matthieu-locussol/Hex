#ifndef _HEX_HEXAGON_
#define _HEX_HEXAGON_

#include <stdlib.h>
#include <stdbool.h>

#include "SDL/SDL.h"

#include "theme.h"

#define HEXAGON_WIDTH 30
#define HEXAGON_HEIGHT 32

#define HEXAGON_BOARD_OFFSET 18

#define HEXAGON_OFFSET_X 15
#define HEXAGON_OFFSET_Y 25

/**
 *	@defgroup hexagon Structure HEXAGON
 *  @brief Definition de la structure hexagon et de ses fonctions
 *  @{
 */

enum eState { EMPTY, P1, P2 };
typedef enum eState eState;

struct hexagon {

	SDL_Rect position;
	eState state;
	bool hover;
	int x;
	int y;

	int path;

};
typedef struct hexagon hexagon;

/** @brief Initialise un hexagone
 *
 * @param h l'hexagone à initialiser
 */
void hexagon_init(hexagon * h);

/** @brief Vérifie si le clic de la souris est dans le triangle haut gauche de l'hexagone
 *
 * @param h l'hexagone à vérifer
 * @param l'évènement qui stocke les coordonnées de la souris
 * @return retourne si oui ou non on a toucher le triangle
 */
bool hexagon_inTopLeftCorner(hexagon * h, SDL_Event * e);

/** @brief Vérifie si la souris est dans le triangle haut droit de l'hexagone
 *
 * @param h l'hexagone à vérifer
 * @param l'évènement qui stocke les coordonnées de la souris
 * @return retourne si oui ou non on a toucher le triangle
 */
bool hexagon_inTopRightCorner(hexagon * h, SDL_Event * e);

/** @brief Vérifie si la souris est dans le triangle bas gauche de l'hexagone
 *
 * @param h l'hexagone à vérifer
 * @param l'évènement qui stocke les coordonnées de la souris
 * @return retourne si oui ou non on a toucher le triangle
 */
bool hexagon_inBottomLeftCorner(hexagon * h, SDL_Event * e);

/** @brief Vérifie si la souris est dans le triangle bas droit de l'hexagone
 *
 * @param h l'hexagone à vérifer
 * @param l'évènement qui stocke les coordonnées de la souris
 * @return retourne si oui ou non on a toucher le triangle
 */
bool hexagon_inBottomRightCorner(hexagon * h, SDL_Event * e);

/** @brief Vérifie si la souris est dans les bordures gauche ou droite de l'hexagone
 *
 * @param h l'hexagone à vérifer
 * @param l'évènement qui stocke les coordonnées de la souris
 * @return retourne si oui ou non on a toucher un des bords
 */
bool hexagon_inSideBorders(hexagon * h, SDL_Event * e);

/** @brief Vérifie si la souris est dans la surface CONTENANT l'hexagone
 *
 * @param h l'hexagone à vérifer
 * @param l'évènement qui stocke les coordonnées de la souris
 * @return retourne si oui ou non on est dans cette surface
 */
bool hexagon_inSurface(hexagon * h, SDL_Event * e);

/** @brief Vérifie si la souris est dans l'hexagone
 *
 * @param h l'hexagone à vérifer
 * @param l'évènement qui stocke les coordonnées de la souris
 * @return retourne si oui ou non on est dans l'hexagone
 */
bool hexagon_inHexagon(hexagon * h, SDL_Event * e);

/** @brief Affiche un hexagone à l'écran
 *
 * @param h l'hexagone à afficher
 * @param screen la SDL_Surface sur laquelle on va afficher l'hexagone
 * @param t le thème utilisé par l'hexagone
 */
void hexagon_display(hexagon * h, SDL_Surface * screen, theme * t);

/** @brief Définit les coordonnées d'un hexagone [0-10][0-10]
 *
 * @param h l'hexagone
 * @param x la nouvelle coordonnée x de l'hexagone
 * @param y la nouvelle coordonnée y de l'hexagone
 */
void hexagon_setCoordinates(hexagon * h, int x, int y);

/** @brief Récupère la coordonnée x d'un hexagone
 *
 * @param h l'hexagone
 * @return retourne la coordonnée x de l'hexagone
 */
int hexagon_getCoordinateX(hexagon * h);

/** @brief Récupère la coordonnée y d'un hexagone
 *
 * @param h l'hexagone
 * @return retourne la coordonnée y de l'hexagone
 */
int hexagon_getCoordinateY(hexagon * h);

/** @brief Définit l'état de survol d'un hexagone
 *
 * @param h l'hexagone
 * @param hover si oui ou non l'hexagone est survolé
 */
void hexagon_setHover(hexagon * h, bool hover);

/** @brief Récupère l'état de survol de l'hexagone
 *
 * @param h l'hexagone
 * @return retourne si oui ou non l'hexagone est survolé
 */
bool hexagon_getHover(hexagon * h);

/** @brief Définit l'état de l'hexagone (vide, joueur1, joueur2)
 *
 * @param h l'hexagone
 * @param state le nouvel état de l'hexagone
 */
void hexagon_setState(hexagon * h, eState state);

/** @brief Récupère l'état d'un hexagone
 *
 * @param h l'hexagone
 * @return retourne l'état de l'hexagone
 */
eState hexagon_getState(hexagon * h);

/** @brief Récupère la position en pixels du bord haut gauche de la surface de l'hexagone par rapport à l'origine
 *
 * @param h l'hexagone dont on veut la position
 * @return retourne la position de l'hexagone
 */
SDL_Rect * hexagon_getPosition(hexagon * h);

/** @brief Récupère le nom de l'hexagone
 *
 * @param h l'hexagone dont on veut connaître le nom
 * @return retourne le nom de l'hexagone (ex: K7)
 */
char * hexagon_getName(hexagon * hex);

/** @} */

#endif
