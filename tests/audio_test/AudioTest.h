#ifndef AUDIOTEST_H
#define AUDIOTEST_H

#include "SolAudio.h"
#include "SolScene.h"

class AudioTest : public sol::Scene
{
public:
    AudioTest();
    ~AudioTest();
    
    bool onTouchEvent(const sol::Touch& touch, sol::TouchEvent event) override;
    
private:
    sol::StreamedAudio* background;
    sol::BufferedAudio* powerup;
};

#endif