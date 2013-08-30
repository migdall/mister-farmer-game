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
 
 render.cpp
 Mister Farmer
 
 Created by Jesus A. Noland on 7/23/13.
 
 */

#include "render.h"

#include <string>
#include <iostream>

// initialize static properties for class
std::vector<SDL_Surface*> Render::loaded;
std::unordered_multimap<std::string,int> Render::bin;

SDL_Surface* Render::screen;

// paths to predefined assets
const std::string lazy_font = "../assets/fonts/lazy.ttf";
const std::string basic_character = "../assets/images/basic_character.png";

//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

Render::Render()
{
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        // output an error message
        std::cout << "Error: Screen was not setup correctly. Render::Render()" << std::endl;
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Mister Farmer", NULL );
}

Render::~Render()
{
    // erase SDL_Surface references
    SDL_Surface* temp = NULL;
    for(int i = 0; i < loaded.size(); i++) {
        temp = loaded[i];
        delete temp;
    }
    loaded.erase(loaded.begin(), loaded.end());
}

// static method for loading any predefined assets
int Render::load()
{
    // predefined
    std::string player_avatar_texture_loc = "../assets/images/basic_character.png";
    
    // return 1 that everything loaded fine
    return 1;
}
