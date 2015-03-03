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
 
 render.h
 Mister Farmer
 
 Created by Jesus A. Noland on 7/23/13.
 
 */

#ifndef Mister_Farmer_render_h
#define Mister_Farmer_render_h

#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"

#include <unordered_map>
#include <vector>
#include <string>

class Render
{
private:
    // privately global mapping of asset name as the key held by a container
    // the value is an integer to collect SDL_Surface resource at the index
    // location in the loaded static private property of the Render system
    static std::unordered_multimap<std::string,int> bin;
    static std::vector<SDL_Surface*> loaded;
    
    // SDL needed properties
    static SDL_Surface* screen;
public:
    Render();
    ~Render();
    
    static int load();
    static SDL_Surface* load_image( std::string filename );
    static SDL_Surface* getScreen();

	void render();
};

#endif
