#include "TouchTest.h"
#include "SolBufferObjects.h"
#include "SolNative.h"
#include "SolSprite.h"

using namespace sol;

TouchTest::TouchTest()
{
    native::getDefaultFramebuffer().setClearColor(whiteColorf());
    
    touchable.setPosition(Vec2f(-50.0, 50.0));
    touchable.setSize(Vec2f(200.0, 200.0));
    touchable.onPress = std::bind(&TouchTest::press, this);
    touchable.onRelease = std::bind(&TouchTest::release, this);
    touchable.onCancel = std::bind(&TouchTest::cancel, this);
    touchable.onEnter = std::bind(&TouchTest::enter, this);
    touchable.onExit = std::bind(&TouchTest::exit, this);
    add(touchable);

    gradient.setSize(touchable.getSize());
    gradient.setColor(blueColorc());
    touchable.addChild(gradient);
}

void TouchTest::update()
{
    const Touch* touch = getInputManager().getTouch(0);
    
    if (touch) SOL_PRINT(touch->loc);
    else SOL_PRINT("No touch");
    
    Scene::update();
}