//
//  main.cpp
//  Mister Farmer
//
//  Created by Jesus A. Noland on 6/28/13.
//  Copyright (c) 2013 Reverent Studios. All rights reserved.
//

#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"
#include <string>
#include <iostream>

using namespace std;

//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

// Surfaces that will be used
SDL_Surface* message = NULL;
SDL_Surface* beginMessage = NULL;
SDL_Surface* startScreenMessage = NULL;
SDL_Surface* screen = NULL;
SDL_Surface* clear = NULL;

// The event structure that will be used
SDL_Event event;

// The font that's going to be used
TTF_Font *font = NULL;

// The color of the font
SDL_Color textColor = { 255, 255, 255 };

// Player avatar properties
SDL_Surface* player = NULL;
SDL_Rect* playerRect = NULL;

// Boolean values
bool level0 = false;
bool level1 = false;

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    
    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        //Free the old surface
        SDL_FreeSurface( loadedImage );
        
        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
    
    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	// Make a temporary rectangle to hold the offsets
	SDL_Rect offset;
    
	// Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;
    
	// Blit the surface
	SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }
    
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "The Advent", NULL );
    
    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Open the font
    font = TTF_OpenFont( "/Users/mehryn/Documents/Code/mister_farmer/Mister Farmer/Mister Farmer/assets/fonts/lazy.ttf", 28 );
    
    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }
    
    // Load the player's avatar
    player = load_image( "/Users/mehryn/Documents/Code/mister_farmer/Mister Farmer/Mister Farmer/assets/images/basic_character.png" );
    
    // Check if the image player image loaded
    if( player == NULL )
    {
        return false;
    }
    
    playerRect = &player->clip_rect;
    
    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( message );
    SDL_FreeSurface( beginMessage );
    SDL_FreeSurface( player );
    
    //Close the font that was used
    TTF_CloseFont( font );
    
    //Quit SDL_ttf
    TTF_Quit();
    
    //Quit SDL
    SDL_Quit();
}

void clearScreen()
{
    // Creating a black color-filled surface
    clear = SDL_CreateRGBSurface( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0 );
    
    // Blit surface to clear screen
    apply_surface( 0, 0, clear, screen );
    
    // Release the surface and null
    SDL_FreeSurface( clear );
    clear = NULL;
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;
    
    //Initialize
    if( init() == false )
    {
        return 1;
    }
    
    //Load the files
    if( load_files() == false )
    {
        return 1;
    }
    
    //Render the text
    char text[] = "Press 'SPACEBAR' to Start";
    message = TTF_RenderText_Solid( font, text, textColor );
    
    //If there was an error in rendering the text
    if( message == NULL )
    {
        return 1;
    }
    
    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }
    
    // Render beginMessage text
    char beginText[] = "Now to begin your adventure";
    beginMessage = TTF_RenderText_Solid( font, beginText, textColor );
    
    //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        if( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
            //If a key was pressed
            else if( event.type == SDL_KEYDOWN )
            {
                //Set the begin message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_SPACE: clearScreen(); message = beginMessage; level0 = true; break;
                    case SDLK_RIGHT: if( level0 || level1 ) {clearScreen(); level1 = true; level0 = false; playerRect->x += 20;} break;
                    case SDLK_LEFT: if( level0 || level1 ) {clearScreen(); level1 = true; level0 = false; playerRect->x -= 20;} break;
                    case SDLK_UP: if( level0 || level1 ) {clearScreen(); level1 = true; level0 = false; playerRect->y -= 20;} break;
                    case SDLK_DOWN: if( level0 || level1 ) {clearScreen(); level1 = true; level0 = false; playerRect->y += 20;} break;
                }
            }
        }
        
        //If a message needs to be displayed
        if( message != NULL )
        {
            //Apply the message centered on the screen
            apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) / 2, message, screen );
            
            //Null the surface pointer
            message = NULL;
        }
        
		if( level0 )
		{
            apply_surface( ( SCREEN_WIDTH - player->w ) / 2, 400, player, screen );
		}
        
        if( level1 )
        {
            apply_surface( playerRect->x, playerRect->y, player, screen );
        }
        
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }
    
    //Free surfaces and font then quit SDL_ttf and SDL
    clean_up();
    
    return 0;
}


