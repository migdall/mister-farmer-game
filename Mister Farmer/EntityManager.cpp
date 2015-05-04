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
 
 EntityManager.cpp
 Mister Farmer
 
 Created by Jesus A. Noland on 3/6/15.
 
 */

#include "EntityManager.h"


// Implement static member variables
unsigned int EntityManager::ENTITY_ID_MAX = 100;


// Implementing the Constructor method for the EntityManager
EntityManager::EntityManager()
{
    // Set the lowest entity id to zero
    _lowestUnassignedEid = 0;
}

EntityManager::~EntityManager()
{
}

unsigned int EntityManager::generateNewEid()
{
    if ( _lowestUnassignedEid < ENTITY_ID_MAX ) {
        return _lowestUnassignedEid++;
    }

    // If we run out of entity ids then return negative one
    // Meaning don't create anymore entities
    return -1;
}

Entity * EntityManager::createEntity()
{
    unsigned int new_eid = generateNewEid();
    
    // Add new Entity to _entities
    _entities.push_back( new_eid );
    
    // Return the new entity
    return new Entity(new_eid);
}
