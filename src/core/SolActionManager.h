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

#ifndef SOL_ACTIONMANAGER_H
#define SOL_ACTIONMANAGER_H

#include "SolUtil.h"

namespace sol
{
    
    class Action;
    
    class ActionManager : public Noncopyable
    {
    public:
        static ActionManager& instance();
        
        size_t actionCount() const { return _actions.size(); }
        void clearActions();
        void runAction(Action* action) { assert(action); _actions.push_back(action); }
        
        void updateActions();
        
    private:
        std::vector<Action*> _actions;
        
        void actionCompleted(Action* action);
    };
    
}

#endif