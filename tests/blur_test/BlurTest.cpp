#include "BlurTest.h"
#include "SolBufferObjects.h"
#include "SolNative.h"

using namespace sol;

BlurTest::BlurTest() :
    spr0("sol_logo.png"),
    spr1("sol_logo.png")
{
    native::getDefaultFramebuffer().setClearColor(greyColorf(0.4));
    
    add(spr0);
    spr0.setPosition(150.0, 0.0);
    
    add(spr1);
    spr1.setPosition(-150.0, 0.0);
    spr1.autorender = false; // so it's not drawn with the blur
}

void BlurTest::render()
{
    blur.render([this]() { getRenderer().renderAll(); });
    spr1.render();
}