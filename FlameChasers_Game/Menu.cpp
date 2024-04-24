#include "Menu.h"

void openMenu(bool &isMenu, SDL_Renderer *gRenderer, game_screen &menu, SDL_Event &m){
    while(isMenu){
        while(SDL_PollEvent(&m) != 0){
            //User enter game
            if(m.type == SDL_KEYDOWN && m.key.keysym.sym == SDLK_SPACE){
                menu.free();
                isMenu = false;
            }
        }
            //render menu
            menu.render(0, 0, gRenderer);
            SDL_RenderPresent(gRenderer);
    }
}

void Guide(bool &isTutorial, SDL_Renderer *gRenderer, game_screen &tutorial, SDL_Event &m){
    while(isTutorial){
        while(SDL_PollEvent(&m) != 0){
            //User enter game
            if(m.type == SDL_KEYDOWN && m.key.keysym.sym == SDLK_SPACE){
                tutorial.free();
                isTutorial = false;
            }
        }
            //render menu
            tutorial.render(110, 0, gRenderer);
            SDL_RenderPresent(gRenderer);
    }
}

