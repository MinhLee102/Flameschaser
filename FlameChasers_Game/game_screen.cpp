#include "game_screen.h"

game_screen::game_screen(){
    //Initialize
    m_Texture = NULL;
    mWidth = 0;
    mHeight = 0;
}

game_screen::~game_screen(){
    //Deallocate
    free();
}

bool game_screen::loadImg(std::string path, SDL_Renderer* gRenderer){
    //Get rid of pre-existing texture
    free();
    //the final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        std::cout << "Unable to load image " << SDL_GetError() << std::endl;
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255 ,255));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
            std::cout << "Unable to create texture from " << path.c_str() << std::endl;
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Clear old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    m_Texture = newTexture;
    return m_Texture != NULL;
}

bool game_screen::loadText(string text, SDL_Color TextColor, SDL_Renderer* gRenderer, TTF_Font* font){
    //Get rid of pre exist texture
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), TextColor);
    if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        m_Texture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( m_Texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return m_Texture != NULL;
}


void game_screen::free(){
    //Free texture if it exists
    if (m_Texture != NULL)
    {
        SDL_DestroyTexture(m_Texture);
        m_Texture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

int game_screen::getWidth(){
    return mWidth;
}

int game_screen::getHeight(){
    return mHeight;
}

void game_screen::render(int x, int y, SDL_Renderer* gRenderer){
    //Set rendering space and render to screen
    SDL_Rect renderStage = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, m_Texture, NULL, &renderStage);
}

int game_screen::updateRenderPosX(const int x){
    return x - mWidth/2;
}

int game_screen::updateRenderPosY(const int y){
    return y - mHeight/2;
}

