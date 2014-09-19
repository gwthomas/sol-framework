#ifndef SOL_TOUCH_H
#define SOL_TOUCH_H

#include "SolVec.h"

namespace sol
{
    
    struct Touch
    {
        Vec2f orig, loc, prev;
        unsigned int id;
    };
    
    enum TouchEvent
    {
        TouchDown,
        TouchMoved,
        TouchUp
    };
    
}

#endif