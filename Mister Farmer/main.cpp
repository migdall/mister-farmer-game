/*
 
 Copyright (c) 2013 Jesus A. Noland
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 main.cpp
 Mister Farmer

 Created by Jesus A. Noland on 6/28/13.
 
*/

#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"

#include <string>
#include <iostream>
using namespace std;

#include "render.h"

//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;


// Surfaces that will be used
SDL_Surface* screen = NULL;
SDL_Surface* clear = NULL;

// The event structure that will be used
SDL_Event event;

// Declare the render system
Render* renderer = NULL;

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
    
    // Initialize the Render system
    renderer = new Render();
    
    //Set up the screen
    screen = Render::getScreen();
    
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
    
    //If everything initialized fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( screen );
    
    // Quit Render
    delete renderer;
    
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
    Render::load();
    
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
                    case SDLK_ESCAPE:
                    {
                        quit = true;
                        break;
                    }
                }
            }
        }
        
    }
    
    //Free surfaces and font then quit SDL_ttf and SDL
    clean_up();
    
    return 0;
}


