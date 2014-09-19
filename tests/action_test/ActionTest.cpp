#include "ActionTest.h"
#include "SolActionManager.h"
#include "SolBufferObjects.h"
#include "SolNative.h"

using namespace sol;

ActionTest::ActionTest() :
    spr("Dude.png")
{
    native::getDefaultFramebuffer().setClearColor(blueColorf());
    
    add(spr);

    trans = createTranslateBy(3.0, &spr, Vec2f(100,100), easeInOutCirc<Vec2f>);
    scale = createScaleTo(4.0, &spr, Vec2f(2.0,1.0), easeInQuad<Vec2f>);
    rot = createRotateBy(5.0, &spr, 720.0, easeOutQuart<float>);
    
    ActionManager::instance().runAction(trans);
    ActionManager::instance().runAction(scale);
    ActionManager::instance().runAction(rot);
}