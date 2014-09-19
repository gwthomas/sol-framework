#include "AudioTest.h"
#include "SolAudio.h"
#include "SolBufferObjects.h"
#include "SolInputManager.h"
#include "SolNative.h"
#include "SolResourceManager.h"

using namespace sol;

AudioTest::AudioTest()
{
    native::getDefaultFramebuffer().setClearColor(greyColorf(0.4));
    
    background = ResourceManager::instance().getResource<StreamedAudio>("background.ogg");
    powerup = ResourceManager::instance().getResource<BufferedAudio>("laserpowerup.ogg");
    
    add(*background);
    add(*powerup);
    
    background->loop();
}

AudioTest::~AudioTest()
{
    ResourceManager::instance().destroyAllResourceManager();
}

bool AudioTest::onTouchEvent(const Touch& touch, TouchEvent event)
{
    if (event == TouchDown) powerup->play();
    return true;
}