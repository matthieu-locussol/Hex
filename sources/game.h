#ifndef _HEX_GAME_
#define _HEX_GAME_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "board.h"
#include "theme.h"
#include "menu.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

#define WINDOW_TITLE "Jeu de Hex"

#define GAME_FPS 25

/**
 *	@defgroup game GAME
 *  @brief Fonctions liées au jeu
 *  @{
 */

/** @brief Initialise la fenêtre
 *
 * @param screen la SDL_Surface qui va jouer le rôle de l'écran
 */
void window_init(SDL_Surface ** screen);

/** @brief Ferme la fenêtre
 *
 */
void window_close();

/** @brief Initialise le jeu
 *
 * @param b le plateau du jeu
 * @param bg le groupe de boutons à charger
 * @param t le thème utilisé par le jeu
 */
void game_init(board * b, buttonGroup * bg, theme * t);

/** @brief Gère les évènements liés au jeu
 *
 * @param b le plateau du jeu
 * @param t le thème du jeu
 * @param e l'évènement qui va être vérifié
 * @return si oui ou non le jeu doit continuer
 */
bool game_eventHandling(board * b, buttonGroup * bg, theme * t, SDL_Event * e);

/** @brief Affiche le jeu à l'écran
 *
 * @param b le plateau à afficher
 * @param bg le groupe de boutons à afficher
 * @param t le thème utilisé par le jeu
 * @param screen la SDL_Surface sur laquelle on va blitter le jeu
 */
void game_display(board * b, buttonGroup * bg, theme * t, SDL_Surface * screen);

/** @brief Met le jeu en pause (à cause du pollEvent())
 *
 * @param time_elapsed le temps qui s'est écoulé
 * @param time_previously_elapsed le temps qui s'était écoulé lors de la précédente pause
 */
void game_pause(int * time_elapsed, int * time_previously_elapsed);

/** @brief Libère la mémoire utilisée par le jeu
 *
 * @param b le plateau à libérer
 * @param bg le groupe de boutons à libérer
 * @param t le thème à libérer
 */
void game_close(board * b, buttonGroup * bg, theme * t);

/** @} */

#endif
