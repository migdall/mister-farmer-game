//
//  render.cpp
//  Mister Farmer
//
//  Created by Mehryn on 7/23/13.
//  Copyright (c) 2013 Reverent Studios. All rights reserved.
//

#include "render.h"

std::vector<SDL_Surface*> Render::loaded;

Render::Render()
{
    loaded.resize(10, NULL);
}
