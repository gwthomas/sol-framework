#include "FilterTest.h"
#include "SolBufferObjects.h"
#include "SolNative.h"
#include "SolProgram.h"

using namespace sol;

FilterTest::FilterTest() :
    spr("sol_logo.png"),
    //filter("default_p_tc|invert")
    //filter("default_p_tc|toon", { "uBands" })
    filter("default_p_tc|emboss",  { "uScreenSize" })
{
    native::getDefaultFramebuffer().setClearColor(Colorf(0.1, 0.8, 0.5, 1.0));
    
    add(spr);
    
    filter.prepare();
    //filter.param("uBands", 8);
    filter.param("uScreenSize", Manager::instance().getScreenSizePixels());
}

void FilterTest::render()
{
    if (getInputManager().getTouchCount() > 0)
    {
        filter.render([this]() { getRenderer().renderAll(); });
    }
    else Scene::render();
}