#include "MultitexTest.h"
#include "SolBufferObjects.h"
#include "SolNative.h"
#include "SolProgram.h"
#include "SolResourceManager.h"

using namespace sol;

MultitexTest::MultitexTest() :
    label("arial-rounded.ttf@75"),
    spr("sol_logo.png")
{
    native::getDefaultFramebuffer().setClearColor(blackColorf());
    
    Program* prog = ResourceManager::instance().getResource<Program>("default_p_tc|multitex_multiply");
    
    add(label);
    label.setAlignment(Label::AlignLeft);
    label.tint = whiteColorf();
    label.setText("HELLO\nTHERE");
    label.setScale(0.6, 1.0);
    label.setPosition(-145.0, -25.0);
    
    tex.setup(GL_RGBA, Manager::instance().getScreenSizePixels(), Manager::instance().isRetinaDisplay());
    tex.clearColor(Colorf());
    
    add(spr);
    spr.program = prog;
    spr.setMultiTexture(&tex.getTexture());
}

void MultitexTest::render()
{
    static bool rtt = true;
    
    if (rtt)
    {
        tex.render([this]() { label.render(); });
        rtt = false;
    }
    
    native::getDefaultFramebuffer().bind();
    spr.render();
}