#include "SolManager.h"
#include "SolApplication.h"

// tests
#include "ActionTest.h"
#include "AnimationTest.h"
#include "AudioTest.h"
#include "BlurTest.h"
#include "CanvasTest.h"
#include "FilterTest.h"
#include "MultitexTest.h"
#include "PhysicsTest.h"
#include "SceneTest.h"
#include "TextureAtlasTest.h"
#include "Test.h"
#include "TextTest.h"
#include "TouchTest.h"

namespace sol
{
    namespace app
    {
        
        void init()
        {
            // global app startup goes here
            Manager::instance().useScene(new TouchTest(), false);
        }
    
        void deinit()
        {
            // global app shutdown goes here
        }
        
    }
}