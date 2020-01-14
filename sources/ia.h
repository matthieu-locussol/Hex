#ifndef _HEX_IA_
#define _HEX_IA_

#include <time.h>

#include "board.h"

/**
 *	@defgroup ia Intelligence Artificielle
 *  @brief Fonctions utilisées par l'intelligence artificielle
 *  @{
 */

/** @brief L'ordinateur joue un coup (IA1)
 *
 * @param b le plateau sur lequel jouer le coup
 * @param t le thème utilisé par le groupe de boutons
 * @return l'hexagone sur lequel a choisit de jouer l'IA 1
 */
hexagon * moveIA1(board * b, theme * t);

/** @brief L'ordinateur joue un coup (IA2)
 *
 * @param b le plateau sur lequel jouer le coup
 * @param t le thème utilisé par le groupe de boutons
 * @return l'hexagone sur lequel a choisit de jouer l'IA 2
 */
hexagon * moveIA2(board * b);

/** @} */

#endif
