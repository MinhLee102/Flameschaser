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
                    menu.render(0, 0, gRenderer);
                    SDL_RenderPresent(gRenderer);
    }
}
