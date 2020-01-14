#ifndef _HEX_MENU_
#define _HEX_MENU_

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "theme.h"
#include "board.h"

#define BUTTON_WIDTH 158
#define BUTTON_HEIGHT 65

#define BUTTON_OFFSET_X 2
#define BUTTON_OFFSET_Y 68

/**
 *	@defgroup menu Structures BUTTON et BUTTONGROUP
 *  @brief Definition des structures button et buttongroups et de leur fonctions
 *  @{
 */

enum eButton { BUTTON_QUIT, BUTTON_PLAY, BUTTON_LOAD, BUTTON_PVP, BUTTON_PVIA1, BUTTON_PVIA2, BUTTON_RETURN, BUTTON_SAVE, BUTTON_CANCEL, BUTTON_RETURN_MENU, BUTTON_S1, BUTTON_S2, BUTTON_S3, BUTTON_S4, BUTTON_S5, BUTTON_L1, BUTTON_L2, BUTTON_L3, BUTTON_L4, BUTTON_L5, BUTTON_CANCEL_SL };
typedef enum eButton eButton;

enum eButtonGroup { BUTTON_GROUP_MAIN, BUTTON_GROUP_MENU, BUTTON_GROUP_PLAY, BUTTON_GROUP_SAVE, BUTTON_GROUP_LOAD };
typedef enum eButtonGroup eButtonGroup;

struct button {

	SDL_Surface * text_surface;
	SDL_Rect text_coordinates;
	SDL_Rect coordinates;
	eButton type;
	int hover;
	int disabled;

};
typedef struct button button;

struct buttonGroup {

	int buttons_number;
	eButtonGroup type;
	button * buttons;

};
typedef struct buttonGroup buttonGroup;

/** @brief Initialise un bouton
 *
 * @param b le bouton à initialiser
 * @param t le thème utilisé par le bouton
 * @param type le type de bouton à charger
 * @param name le texte afficher dans le bouton
 * @param position la position du bouton (premier bouton, deuxième bouton..)
 */
void button_init(button * b, theme * t, eButton type, const char * name, int position);

/** @brief Gère les évènements de survol du bouton
 *
 * @param b le bouton
 * @param action l'évènement qui va vérifier le survol
 */
void button_mouseMotionHandle(button * b, SDL_Event * action);

/** @brief Libère la mémoire utilisée par un bouton
 *
 * @param b le bouton à libérer
 */
void button_close(button * b);

/** @brief Gère les évènements de survol sur un groupe de boutons
 *
 * @param bg le groupe de boutons
 * @param action l'évènement qui va vérifier le survol
 */
void buttonGroup_mouseMotionHandle(buttonGroup * bg, SDL_Event * action);

/** @brief Gère les évènements de clic sur un groupe de boutons
 *
 * @param b le plateau actuellement chargé
 * @param bg le groupe de boutons
 * @param t le thème utilisé par le groupe de boutons
 * @param action l'évènement qui va vérifier le clic
 */
void buttonGroup_mouseClickHandle(board * b, buttonGroup * bg, theme * t, SDL_Event * action);

/** @brief Initialise un groupe de boutons
 *
 * @param b le plateau actuellement chargé
 * @param bg le groupe de boutons
 * @param t le thème utilisé par le groupe de boutons
 * @param ebg le type de groupe de boutons à charger
 */
void buttonGroup_initButtonGroup(board * b, buttonGroup * bg, theme * t, eButtonGroup ebg);

/** @brief Affiche un groupe de boutons à l'écran
 *
 * @param bg le groupe de boutons
 * @param screen la SDL_Surface sur laquelle on va blitter le groupe de boutons
 * @param t le thème utilisé par le groupe de boutons
 */
void buttonGroup_display(buttonGroup * bg, SDL_Surface * screen, theme * t);

/** @brief Libère la mémoire utilisée par un groupe de boutons
 *
 * @param bg le groupe de boutons à libérer
 */
void buttonGroup_close(buttonGroup * bg);

/** @} */

#endif
