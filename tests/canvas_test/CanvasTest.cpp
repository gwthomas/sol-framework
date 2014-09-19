#include "SolImage.h"
#include "SolResourceManager.h"

#include "CanvasTest.h"

using namespace sol;

CanvasTest::CanvasTest() :
    canvas(Vec2i(60, 60), 5.0)
{
    Image* img = ResourceManager::instance().getResource<Image>("Dude.png");
    canvas.clear(greenColorc());
    canvas.blit(*img, Vec2i(10, 10));
    add(canvas);
}