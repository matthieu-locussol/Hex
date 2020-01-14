#include "menu.h"

void button_init(button * b, theme * t, eButton type, const char * name, int position)
{

	b->type = type;

	b->hover = 0;
	b->disabled = 0;

	b->coordinates.x = (Sint16)(BUTTON_OFFSET_X);
	b->coordinates.y = (Sint16)(BUTTON_OFFSET_Y + position * BUTTON_HEIGHT);

	b->text_surface = TTF_RenderText_Blended(t->font, name, t->colors[DEFAULT]);

	b->text_coordinates.x = (Sint16)(BUTTON_OFFSET_X + (BUTTON_WIDTH - b->text_surface->w) / 2);
	b->text_coordinates.y = (Sint16)(BUTTON_OFFSET_Y + position * BUTTON_HEIGHT + (BUTTON_HEIGHT - b->text_surface->h) / 2);

}

void button_mouseMotionHandle(button * b, SDL_Event * action)
{

	if (action->motion.x >= b->coordinates.x && action->motion.x <= b->coordinates.x + BUTTON_WIDTH && action->motion.y >= b->coordinates.y && action->motion.y < b->coordinates.y + BUTTON_HEIGHT)
		b->hover = 1;
	else
		b->hover = 0;

}

void buttonGroup_mouseMotionHandle(buttonGroup * bg, SDL_Event * action)
{

	int i;

	for (i = 0; i < bg->buttons_number; ++i)
		button_mouseMotionHandle(&bg->buttons[i], action);

}

void buttonGroup_mouseClickHandle(board * b, buttonGroup * bg, theme * t, SDL_Event * action)
{

	int i;

	for (i = 0; i < bg->buttons_number; ++i)
		if(bg->buttons[i].hover)
			switch (bg->buttons[i].type)
			{

				case BUTTON_QUIT:
					action->type = SDL_QUIT;
					SDL_PushEvent(action);
					break;

				case BUTTON_PLAY:
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_MENU);
					break;

				case BUTTON_RETURN:
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_MAIN);
					break;

				case BUTTON_RETURN_MENU:
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_MENU);
					break;

				case BUTTON_PVP:
					if (b->playable)
					{

						board_close(b);
						board_init(b, t);

					}
					b->playable = true;
					b->enemy = HUMAN;
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_PVIA1:
					if (b->playable)
					{

						board_close(b);
						board_init(b, t);

					}
					b->playable = true;
					b->enemy = IA1;
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_PVIA2:
					if (b->playable)
					{

						board_close(b);
						board_init(b, t);

					}
					b->playable = true;
					b->enemy = IA2;
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_CANCEL:
					board_cancelMove(b, t);
					break;

				case BUTTON_SAVE:
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_SAVE);
					break;

				case BUTTON_LOAD:
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_LOAD);
					break;

				case BUTTON_S1:
					board_saveGame(b, t, "saves/1.txt");
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_S2:
					board_saveGame(b, t, "saves/2.txt");
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_S3:
					board_saveGame(b, t, "saves/3.txt");
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_S4:
					board_saveGame(b, t, "saves/4.txt");
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_S5:
					board_saveGame(b, t, "saves/5.txt");
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_L1:
					if (board_loadGame(b, t, "saves/1.txt"))
						board_setNotificationText(b, t, "Sauvegarde chargee avec succes.", SUCCESS);
					else
					{
						board_setNotificationText(b, t, "Sauvegarde corrompue ou inexistante. Partie non chargee.\n", ERROR);
						b->playable = false;
						b->finished = true;
					}
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_L2:
					if (board_loadGame(b, t, "saves/2.txt"))
						board_setNotificationText(b, t, "Sauvegarde chargee avec succes.", SUCCESS);
					else
					{
						board_setNotificationText(b, t, "Sauvegarde corrompue ou inexistante. Partie non chargee.\n", ERROR);
						b->playable = false;
						b->finished = true;
					}
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_L3:
					if (board_loadGame(b, t, "saves/3.txt"))
						board_setNotificationText(b, t, "Sauvegarde chargee avec succes.", SUCCESS);
					else
					{
						board_setNotificationText(b, t, "Sauvegarde corrompue ou inexistante. Partie non chargee.\n", ERROR);
						b->playable = false;
						b->finished = true;
					}
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_L4:
					if (board_loadGame(b, t, "saves/4.txt"))
						board_setNotificationText(b, t, "Sauvegarde chargee avec succes.", SUCCESS);
					else
					{
						board_setNotificationText(b, t, "Sauvegarde corrompue ou inexistante. Partie non chargee.\n", ERROR);
						b->playable = false;
						b->finished = true;
					}
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_L5:
					if (board_loadGame(b, t, "saves/5.txt"))
						board_setNotificationText(b, t, "Sauvegarde chargee avec succes.", SUCCESS);
					else
					{
						board_setNotificationText(b, t, "Sauvegarde corrompue ou inexistante. Partie non chargee.\n", ERROR);
						b->playable = false;
						b->finished = true;
					}
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				case BUTTON_CANCEL_SL:
					buttonGroup_initButtonGroup(b, bg, t, BUTTON_GROUP_PLAY);
					break;

				default:
					break;

			}

}

void buttonGroup_initButtonGroup(board * b, buttonGroup * bg, theme * t, eButtonGroup ebg)
{

	static int freeMemory = 0;

	if (freeMemory)
		buttonGroup_close(bg);
	else
		bg->buttons = NULL;

	bg->type = ebg;

	switch (bg->type)
	{

		case BUTTON_GROUP_MAIN:
			{

				bg->buttons_number = 3;
				bg->buttons = (button *) malloc(sizeof(button) * bg->buttons_number);

				button_init(&bg->buttons[0], t, BUTTON_PLAY, "Jouer", 0);
				button_init(&bg->buttons[1], t, BUTTON_LOAD, "Charger", 1);
				button_init(&bg->buttons[2], t, BUTTON_QUIT, "Quitter", 2);

			}
			break;

		case BUTTON_GROUP_MENU:
			{

				bg->buttons_number = 5;
				bg->buttons = (button *) malloc(sizeof(button) * bg->buttons_number);

				button_init(&bg->buttons[0], t, BUTTON_PVP, "Humain VS Humain", 0);
				button_init(&bg->buttons[1], t, BUTTON_PVIA1, "Humain VS IA1", 1);
				button_init(&bg->buttons[2], t, BUTTON_PVIA2, "Humain VS IA2", 2);
				button_init(&bg->buttons[3], t, BUTTON_RETURN, "Retour", 3);
				button_init(&bg->buttons[4], t, BUTTON_QUIT, "Quitter", 4);

			}
			break;

		case BUTTON_GROUP_PLAY:
			{

				bg->buttons_number = 5;

				bg->buttons = (button *) malloc(sizeof(button) * bg->buttons_number);

				button_init(&bg->buttons[0], t, BUTTON_SAVE, "Sauvegarder", 0);
				button_init(&bg->buttons[1], t, BUTTON_LOAD, "Charger", 1);
				button_init(&bg->buttons[2], t, BUTTON_CANCEL, "Annuler coup", 2);
				button_init(&bg->buttons[3], t, BUTTON_RETURN_MENU, "Retour", 3);
				button_init(&bg->buttons[4], t, BUTTON_QUIT, "Quitter", 4);

			}
			break;

		case BUTTON_GROUP_SAVE:
		{

			bg->buttons_number = 6;
			bg->buttons = (button *)malloc(sizeof(button) * bg->buttons_number);

			button_init(&bg->buttons[0], t, BUTTON_S1, "Slot 1", 0);
			button_init(&bg->buttons[1], t, BUTTON_S2, "Slot 2", 1);
			button_init(&bg->buttons[2], t, BUTTON_S3, "Slot 3", 2);
			button_init(&bg->buttons[3], t, BUTTON_S4, "Slot 4", 3);
			button_init(&bg->buttons[4], t, BUTTON_S5, "Slot 5", 4);
			button_init(&bg->buttons[5], t, BUTTON_CANCEL_SL, "Retour", 5);

		}
		break;

		case BUTTON_GROUP_LOAD:
		{

			bg->buttons_number = 6;
			bg->buttons = (button *)malloc(sizeof(button) * bg->buttons_number);

			button_init(&bg->buttons[0], t, BUTTON_L1, "Slot 1", 0);
			button_init(&bg->buttons[1], t, BUTTON_L2, "Slot 2", 1);
			button_init(&bg->buttons[2], t, BUTTON_L3, "Slot 3", 2);
			button_init(&bg->buttons[3], t, BUTTON_L4, "Slot 4", 3);
			button_init(&bg->buttons[4], t, BUTTON_L5, "Slot 5", 4);
			button_init(&bg->buttons[5], t, BUTTON_CANCEL_SL, "Retour", 5);

		}
		break;

	}

	freeMemory = 1;

}

void buttonGroup_display(buttonGroup * bg, SDL_Surface * screen, theme * t)
{

	int i;

	for (i = 0; i < bg->buttons_number; ++i)
	{

		if (bg->buttons[i].hover)
		{
			bg->buttons[i].text_coordinates.x += 3;
			SDL_BlitSurface(t->images[BUTTON_HOVER].image, NULL, screen, &bg->buttons[i].coordinates);
		}
		else
			SDL_BlitSurface(t->images[BUTTON].image, NULL, screen, &bg->buttons[i].coordinates);

		SDL_BlitSurface(bg->buttons[i].text_surface, NULL, screen, &bg->buttons[i].text_coordinates);

		if (bg->buttons[i].hover)
			bg->buttons[i].text_coordinates.x -= 3;

	}

}

void buttonGroup_close(buttonGroup * bg)
{

	int i;

	for (i = 0; i < bg->buttons_number; ++i)
		button_close(&bg->buttons[i]);

	free(bg->buttons);
	bg->buttons = NULL;

}

void button_close(button * b)
{

	SDL_FreeSurface(b->text_surface);
	b->text_surface = NULL;

}
