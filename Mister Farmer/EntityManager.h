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
 
 EntityManager.h
 Mister Farmer
 
 Created by Jesus A. Noland on 3/6/15.
 
 */


#ifndef __Mister_Farmer__EntityManager__
#define __Mister_Farmer__EntityManager__

// Import header files
#include <vector>
#include <string>
#include <unordered_map>

#include "entity.h"
#include "component.h"

class EntityManager
{
private:
    // Static members
    static unsigned int ENTITY_ID_MAX;
    // Private properties
    
    // A mutable array to hold the entity ids that are generated
    std::vector<int> _entities;
    // A mutable dictionary to hold the components
    std::unordered_map<std::string, std::unordered_map<int, Component *>> _componentsByClass;
    
    unsigned int _lowestUnassignedEid;
    // Private methods
    unsigned int generateNewEid();
public:
    EntityManager();
    ~EntityManager();
    
    // Public member methods
    Entity * createEntity();
    void addComponent();
    Component * getComponentOfClass();
};


#endif /* defined(__Mister_Farmer__EntityManager__) */
