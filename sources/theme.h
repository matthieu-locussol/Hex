#ifndef _HEX_THEME_
#define _HEX_THEME_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "texture.h"

#define DEFAULT_THEME BLUE

/**
 *	@defgroup theme Structure THEME
 *  @brief Definition de la structure theme et de ses fonctions
 *  @{
 */

enum eTheme { DARK, BLUE };
typedef enum eTheme eTheme;

enum eColor { DEFAULT, SUCCESS, ERROR, C_P1, C_P2 };
typedef enum eColor eColor;

struct theme {

	eTheme value;

	TTF_Font * font;

	SDL_Color colors[5];
	eColor last_color;

	texture images[TEXTURE_NUMBER];

};
typedef struct theme theme;

/** @brief Initialise le thème avec le nom du thème donné
 *
 * @param t le thème à initialiser
 * @param type le nom du thème à charger
 */
void theme_init(theme * t, eTheme type);

/** @brief Charge le thème "Dark"
 *
 * @param t le thème pour le chargement
 */
void theme_loadDark(theme * t);

/** @brief Charge le thème "Light"
 *
 * @param t le thème pour le chargement
 */
void theme_loadLight(theme * t);

/** @brief Charge le thème "Blue"
 *
 * @param t le thème pour le chargement
 */
void theme_loadBlue(theme * t);

/** @brief Libère la mémoire utilisée par le thème
 *
 * @param t le thème
 */
void theme_close(theme * t);

/** @} */

#endif
