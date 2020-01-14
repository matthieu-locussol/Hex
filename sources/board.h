#ifndef _HEX_BOARD_
#define _HEX_BOARD_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "SDL/SDL.h"

#include "hexagon.h"
#include "theme.h"
#include "history.h"

#define BOARD_OFFSET_X 278
#define BOARD_OFFSET_Y 200

#define BOARD_TEXT_OFFSET_X 288
#define BOARD_TEXT_OFFSET_Y 653

#define BOARD_HEXAGON_PER_LINE 11

/**
 *	@defgroup board Structure BOARD
 *  @brief Definition de la structure board et de ses fonctions
 *  @{
 */

enum eEnemy { HUMAN, IA1, IA2 };
typedef enum eEnemy eEnemy;

struct board {

	hexagon cells[BOARD_HEXAGON_PER_LINE][BOARD_HEXAGON_PER_LINE];
	hexagon * last_cell_move;
	SDL_Surface * textNotificationSurface;
	SDL_Rect textPosition;
	SDL_Rect position;
	eState player;

	history hist;

	int path_count;
	int canceled_moves;

	bool playable;
	bool finished;
	bool canceled;

	eEnemy enemy;

};
typedef struct board board;

/** @brief Initialise un plateau
 *
 * @param b le plateau à initialiser
 * @param t le thème utilisé par le plateau
 */
void board_init(board * b, theme * t);

/** @brief Gère les évènements de clic sur le plateau
 *
 * @param e l'évènement qui stocke les actions de la souris
 * @param b le plateau à vérifier
 * @param t le thème utilisé par le plateau
 */
void board_mouseClickHandle(SDL_Event * e, board * b, theme * t);

/** @brief Gère les évènements de clic gauche sur le plateau
 *
 * @param e l'évènement qui stocke les actions de la souris
 * @param b le plateau à vérifier
 * @param t le thème utilisé par le plateau
 */
void board_leftClickHandle(SDL_Event * e, board * b, theme * t);

/** @brief Gère les évènements de survol de la souris sur le plateau
 *
 * @param e l'évènement qui stocke les actions de la souris
 * @param b le plateau à vérifier
 */
void board_mouseMotionHandle(SDL_Event * e, board * b);

/** @brief Affiche un plateau à l'écran
 *
 * @param screen la SDL_Surface sur laquelle on va blitter le plateau
 * @param t le thème utilisé par le plateau
 * @param b le plateau à afficher
 */
void board_display(SDL_Surface * screen, theme * t, board * b);

/** @brief Récupère un hexagone à partir de ses coordonnées de plateau
 *
 * @param b le plateau sur lequel on veut récupérer l'hexagone
 * @param x la coordonnée x de l'hexagone
 * @param y la coordonnée y de l'hexagone
 * @return l'hexagone représentée par les coordonnées (x, y)
 */
hexagon * board_getHexagonByCoords(board * b, int x, int y);

/** @brief Change la notification actuellement affichée
 *
 * @param b le plateau sur lequel afficher la notification
 * @param t le thème utilisé par le plateau
 * @param text le texte de notification
 * @param c le type de la notification
 */
void board_setNotificationText(board * b, theme * t, const char * text, eColor c);

/** @brief Libère la mémoire utilisée par un plateau de jeu
 *
 * @param b le plateau à libérer
 */
void board_close(board * b);

/** @brief Annule un mouvement sur un plateau
 *
 * @param b le plateau sur lequel annuler le coup
 * @param t le thème utilisé par le plateau
 */
void board_cancelMove(board * b, theme * t);

/** @brief Convertit le numéro de chemin des hexagones voisins à l'hexagone passé en paramètre
 *
 * @param b le plateau sur lequel chercher les voisins
 * @param h l'hexagone dont on cherche les voisins
 */
void board_convertNeighboorsPath(board * b, hexagon * h);

/** @brief Joue un mouvement sur le plateau
 *
 * @param b le plateau sur lequel on joue le coup
 * @param t le thème utilisé par le plateau
 * @param h l'hexagone que le joueur a voulu joueur
 * @param player le joueur qui effectue le coup
 */
void board_doMove(board * b, theme * t, hexagon * h, eState player);

/** @brief Met à jour l'historique (en ajoutant à la fin de la pile)
 *
 * @param b le plateau correspondant à l'historique
 * @param t le thème utilisé par le plateau
 * @param h l'hexagone nouvellement joué
 * @param player le joueur qui a joué cet hexagones
 * @param number le numéro du coup joué (premier coup, deuxième coup..)
 */
void board_updateHistoryInverse(board * b, theme * t, hexagon * h, eState player, int number);

/** @brief Change le numéro de chemin "global"
 *
 * @param b le plateau contenant le numéro de chemin global
 * @return le numéro global mis à jour
 */
int board_newPath(board * b);

/** @brief Convertit un ancien numéro de chemin à un nouveau numéro de chemin
 *
 * @param b le plateau sur lequel convertir les numéros
 * @param player le joueur qui a posé l'hexagone contaminant
 * @param src l'ancien numéro de chemin
 * @param dst le nouveau numéro de chemin
 */
void board_pathConvert(board * b, eState player, int src, int dst);

/** @brief Vérifie si un chemin est complet pour un joueur
 *
 * @param b le plateau sur lequel vérifier le chemin
 * @param player le joueur dont on veut vérifier s'il a complété un chemin
 * @param path le numéro du chemin à vérifier
 */
bool board_pathComplete(board * b, eState player, int path);

/** @brief Annule un mouvement sur un plateau
 *
 * @param b le plateau sur lequel annuler le coup
 * @param t le thème utilisé par le plateau
 */
eState board_gameWinner(board * b);

/** @brief Met à jour l'historique
 *
 * @param b le plateau correspondant à l'historique
 * @param t le thème utilisé par le plateau
 * @param h l'hexagone nouvellement joué
 * @param player le joueur qui a joué cet hexagones
 * @param number le numéro du coup joué (premier coup, deuxième coup..)
 */
void board_updateHistory(board * b, theme * t, hexagon * h, eState player, int number);

/** @brief Sauvegarde une partie
 *
 * @param b le plateau à sauvegarder
 * @param t le thème utilisé par le plateau
 * @param filename le nom du fichier de sauvegarde
 */
void board_saveGame(board * b, theme * t, const char * filename);

/** @brief Charger une partie
 *
 * @param b le plateau dans lequel charger la partie
 * @param t le thème utilisé par le plateau
 * @param filename le nom du fichier de sauvegarde à charger
 */
bool board_loadGame(board * b, theme * t, const char * filename);

/** @} */

#endif
