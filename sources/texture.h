#ifndef _HEX_TEXTURE_
#define _HEX_TEXTURE_

#include <string.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define TEXTURE_NUMBER 8

/**
 *	@defgroup texture Structure TEXTURE
 *  @brief Definition de la structure texture et de ses fonctions
 *  @{
 */

enum eTexture { BACKGROUND, BOARD, HEX, HEX_HOVER, HEX_P1, HEX_P2, BUTTON, BUTTON_HOVER };
typedef enum eTexture eTexture;

struct texture {

	SDL_Surface * image;
	char image_name[32];

};
typedef struct texture texture;

/** @brief Charge une image dans une texture
 *
 * @param t la texture dans laquelle on va charger l'image
 * @param name le chemin relatif vers l'image
 */
void texture_nameLoading(texture * t, const char * name);

/** @brief Charge une texture en mémoire
 *
 * @param t la texture qu'on veut charger en mémoire
 */
void texture_loading(texture * t);

/** @brief Libère la mémoire utilisée par une texture
 *
 * @param t la texture à libérer
 */
void texture_free(texture * t);

/** @} */

#endif
