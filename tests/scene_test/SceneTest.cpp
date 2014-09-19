#include "SceneTest.h"

using namespace sol;

Scene1::Scene1() :
    label("arial-rounded.ttf@30")
{
    label.setText("Scene 1");
    label.setAlignment(Label::AlignCenter);
    add(label);
}

bool Scene1::onTouchEvent(const Touch& touch, TouchEvent event)
{
    if (event == TouchDown) Manager::instance().useScene(new Scene2(), true);
    return true;
}

Scene2::Scene2() :
    label("arial-rounded.ttf@50")
{
    label.setText("Scene 2");
    label.setAlignment(Label::AlignCenter);
    add(label);
}

bool Scene2::onTouchEvent(const Touch& touch, TouchEvent event)
{
    if (event == TouchDown) Manager::instance().useScene(new Scene1(), true);
    return true;
}