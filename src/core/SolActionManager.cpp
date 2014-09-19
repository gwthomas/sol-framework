/*
 *
 * Copyright (c) 2012 Garrett Thomas
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#include "SolAction.h"
#include "SolActionManager.h"

namespace sol
{
    
    ActionManager& ActionManager::instance()
    {
        static ActionManager instance;
        return instance;
    }
    
    void ActionManager::clearActions()
    {
        for (Action* action : _actions) delete action;
        _actions.clear();
    }
    
    void ActionManager::updateActions()
    {
        std::vector<Action*> toremove;
        
        for (int i = 0; i < _actions.size(); i++)
        {
            Action* action = _actions[i];
            action->update();
            if (action->isDone()) toremove.push_back(action);
        }
        
        for (int i = 0; i < toremove.size(); i++) actionCompleted(toremove[i]);
    }
    
    void ActionManager::actionCompleted(Action* action)
    {
        for (int i = 0; i < _actions.size(); i++)
        {
            Action* current = _actions[i];
            
            if (current == action)
            {
                _actions.erase(_actions.begin() + i);
                delete current;
                return;
            }
        }
    }
    
}