#include "TextTest.h"

using namespace sol;

TextTest::TextTest()
{
    arial = ResourceManager::instance().getResource<Font>("arial-rounded.ttf@30");
    assert(arial);
    
    droidSans = ResourceManager::instance().getResource<Font>("DroidSans.ttf@20");
    assert(droidSans);
    
    label0 = new SimpleLabel(*arial);
    label0->setText("A simple Arial label");
    add(*label0);
    
    label1 = new TextArea(*droidSans);
    label1->setText("Hello this is Droid Sans.\nWe're using a text area to display this message.\nPretty cool right?\n\nHere is some text for you. If everything is going smoothly it should wrap around to the next line.");
    label1->setWidth(Manager::instance().getScreenSizePoints().x);
    label1->setPosition(Vec2f(0.0, 100.0));
    add(*label1);
}

TextTest::~TextTest()
{
    ResourceManager::instance().destroyAllResourceManager();
}

bool TextTest::onTouchEvent(const Touch& touch, TouchEvent event)
{
    if (event == TouchDown || event == TouchMoved) label0->setPosition(touch.loc);
    return true;
}

void TextTest::update()
{
    label0->rotate(1.0);
    
    float spacing = label1->getSpacing();
    
    if (expanding)
    {
        if (spacing < 2.0)
        {
            label1->setSpacing(spacing + 0.01);
        }
        else
        {
            expanding = false;
        }
    }
    else
    {
        if (spacing > 1.0)
        {
            label1->setSpacing(spacing - 0.01);
        }
        else
        {
            expanding = true;
        }
    }
    
    Scene::update();
}