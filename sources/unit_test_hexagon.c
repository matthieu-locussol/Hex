#include <assert.h>

#include "hexagon.h"

int main(int argc, char * argv[])
{

	(void)argc;
	(void)argv;

  hexagon h;
  theme t;

	SDL_Event action;
	SDL_Surface * screen = NULL;
  SDL_Rect * position;

  int continuer = 1;
  int numberTests = 9;

  SDL_Init(SDL_INIT_VIDEO);

  screen = SDL_SetVideoMode(160, 160, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	SDL_WM_SetCaption("Tests unitaires - Hexagon", NULL);

  /**
   * On initialise l'hexagone pour les tests et le thème contenant l'image de l'hexagone
   */

  hexagon_init(&h);
  theme_init(&t, BLUE);

  /**
   * On centre l'hexagone pour les tests
   */

  h.position.x = ((screen->w - 31) / 2);
  h.position.y = ((screen->h - 33) / 2);

  while(continuer)
  {

    SDL_WaitEvent(&action);

    switch(action.type)
    {

      case SDL_QUIT:
        continuer = 0;
        break;

      /**
       * Test manuel du fonctionnement du survol de la souris
       */

      case SDL_MOUSEMOTION:
        if (hexagon_inHexagon(&h, &action))
          hexagon_setHover(&h, true);
        else
          hexagon_setHover(&h, false);
        break;

      /**
       * Test manuel du fonctionnement du clic de la souris
       */

      case SDL_MOUSEBUTTONDOWN:
        if (action.button.button == SDL_BUTTON_LEFT)
        {

					if(hexagon_inHexagon(&h, &action))
					{

	          if(hexagon_getState(&h) == P1)
	            hexagon_setState(&h, EMPTY);
	          else
	            hexagon_setState(&h, P1);

					}

        }
        else if(action.button.button == SDL_BUTTON_RIGHT)
        {

					if(hexagon_inHexagon(&h, &action))
					{

	          if(hexagon_getState(&h) == P2)
	            hexagon_setState(&h, EMPTY);
	          else
	            hexagon_setState(&h, P2);

					}

        }
				break;

      default:
        break;

    }

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    hexagon_display(&h, screen, &t);

    SDL_Flip(screen);

  }

  /**
   * Une fois les tests manuels terminés, on passe aux tests automatiques
   */

  hexagon_setState(&h, EMPTY);
  assert(hexagon_getState(&h) == EMPTY);
  fprintf(stdout, "Test 1/%d passed\n", numberTests);

  position = hexagon_getPosition(&h);
  assert(position->x == ((screen->w - 31) / 2));
  fprintf(stdout, "Test 2/%d passed\n", numberTests);
  assert(position->y == ((screen->h - 33) / 2));
  fprintf(stdout, "Test 3/%d passed\n", numberTests);

  h.position.x = 0;
  h.position.y = 10;

  position = hexagon_getPosition(&h);
  assert(position->x == 0);
  fprintf(stdout, "Test 4/%d passed\n", numberTests);
  assert(position->y == 10);
  fprintf(stdout, "Test 5/%d passed\n", numberTests);

  hexagon_setCoordinates(&h, 1, 7);
  assert(hexagon_getCoordinateX(&h) == 1);
  fprintf(stdout, "Test 6/%d passed\n", numberTests);
  assert(hexagon_getCoordinateY(&h) == 7);
  fprintf(stdout, "Test 7/%d passed\n", numberTests);

  assert(!strcmp(hexagon_getName(&h), "B8"));
  fprintf(stdout, "Test 8/%d passed\n", numberTests);
  hexagon_setCoordinates(&h, 10, 6);
  assert(!strcmp(hexagon_getName(&h), "K7"));
  fprintf(stdout, "Test 9/%d passed\n", numberTests);

  /**
   * On libère la mémoire
   */

  theme_close(&t);

  SDL_Quit();

	return EXIT_SUCCESS;

}
