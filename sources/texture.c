#include "texture.h"

void texture_nameLoading(texture * t, const char * name)
{

	strcpy(t->image_name, name);

}

void texture_loading(texture * t)
{

	int i;

	for (i = 0; i < TEXTURE_NUMBER; ++i)
		t[i].image = IMG_Load(t[i].image_name);

}

void texture_free(texture * t)
{

	int i;

	for (i = 0; i < TEXTURE_NUMBER; ++i)
		SDL_FreeSurface(t[i].image);

}
