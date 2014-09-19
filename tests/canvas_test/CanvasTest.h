#ifndef CANVASTEST_H
#define CANVASTEST_H

#include "SolCanvas.h"
#include "SolScene.h"

class CanvasTest : public sol::Scene
{
public:
    CanvasTest();
    
private:
    sol::Canvas canvas;
};

#endif