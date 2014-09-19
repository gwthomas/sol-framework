/*
 *
 * Copyright (c) 2012 Garrett Thomas
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#include "SolActionManager.h"
#include "SolApplication.h"
#include "SolAudio.h"
#include "SolGL.h"
#include "SolManager.h"
#include "SolNative.h"
#include "SolResourceManager.h"
#include "SolScene.h"
#include "SolUtil.h"

namespace sol
{
    
    inline void initGL()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    Manager& Manager::instance()
    {
        static Manager instance;
        return instance;
    }
    
    void Manager::init0(const Vec2i& screenSize)
    {
        if (!_initialized)
        {
            _screenSize = screenSize;
            _resourcePath = native::getResourcePath();
            _retinaDisplay = native::isRetinaDisplay();
            
            _initialized = true;
            _running = true;
            
            setOrientation(SOL_DEFAULT_ORIENTATION);
        }
    }
    
    void Manager::init1()
    {
        initGL();
        Audio::init();
        app::init();
        
        _daemon = new Scene();
    }
    
    void Manager::deinit()
    {
        if (_initialized)
        {
            SOL_SAFE_DELETE(_currentScene);
            
            app::deinit();
            ResourceManager::instance().destroyAllResourceManager();
            Audio::deinit();
            
            _initialized = false;
            _running = false;
        }
    }
    
    void Manager::pause()
    {
        if (_running)
        {
            if (_currentScene) _currentScene->onPause();
            _running = false;
        }
    }
    
    void Manager::resume()
    {
        if (!_running)
        {
            if (_currentScene) _currentScene->onResume();
            _running = true;
        }
    }
    
    void Manager::useScene(Scene* scene, bool deleteCurrent)
    {
        assert(_daemon != scene);
        _nextScene = std::make_pair(scene, deleteCurrent);
    }
    
    void Manager::update()
    {
        if (_nextScene.first)
        {
            if (_nextScene.second) SOL_SAFE_DELETE(_currentScene);
            _currentScene = _nextScene.first;
            _nextScene.first = nullptr;
        }
        
        _daemon->update();
        ActionManager::instance().updateActions();
        if (_currentScene) _currentScene->update();
    }
    
    void Manager::render()
    {
        if (!_daemonForeground) _daemon->render();
        if (_currentScene) _currentScene->render();
        if (_daemonForeground) _daemon->render();
    }
    
    void Manager::setOrientation(Orientation orientation)
    {
        _orientation = orientation;
        
        float smallerSide = min<float>(_screenSize.x, _screenSize.y);
        float largerSide = max<float>(_screenSize.x, _screenSize.y);
        float rotation;
        
        if (_orientation == Portrait)
        {
            _screenSize = Vec2i(smallerSide, largerSide);
            rotation = 0.0;
        }
        else
        {
            _screenSize = Vec2i(largerSide, smallerSide);
            rotation = -90.0;
        }
        
        _worldTransform = Matrix().rotation(rotation) *  Matrix().ortho(-_screenSize.x * 0.5, _screenSize.x * 0.5, -_screenSize.y * 0.5, _screenSize.y * 0.5);
    }
    
}