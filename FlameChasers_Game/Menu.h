#ifndef MENU_H
#define MENU_H

#include "GameLib.h"
#include "game_screen.h"

void openMenu(bool &isMenu, SDL_Renderer *gRenderer, game_screen &menu, SDL_Event &m);

void Guide(bool &isTutorial, SDL_Renderer *gRenderer, game_screen &tutorial, SDL_Event &m);


#endif // MENU
