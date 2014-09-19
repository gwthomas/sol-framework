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

#ifndef SOL_MANAGER_H
#define SOL_MANAGER_H

#include "SolAdManager.h"
#include "SolInputManager.h"
#include "SolMatrix.h"
#include "SolRenderer.h"
#include "SolVec.h"

namespace sol
{
    
    class Scene;
    
    enum Orientation
    {
        Portrait,
        Landscape
    };
    
    class Manager : public Noncopyable
    {
    public:
        bool renderNewFrame = true;
        float fps = SOL_DEFAULT_FPS;
        
        static Manager& instance();
        
        bool isInitialized() const { return _initialized; }
        bool isRunning() const { return _running; }
        bool isRetinaDisplay() const { return _retinaDisplay; }
        const std::string& getResourcePath() const { return _resourcePath; }
        Scene* getCurrentScene() const { return _currentScene; }
        Scene& getDaemon() { return *_daemon; }
        Orientation getOrientation() const { return _orientation; }
        const Vec2i& getScreenSizePoints() const { return _screenSize; }
        Vec2i getScreenSizePixels() const { return isRetinaDisplay() ? _screenSize * 2 : _screenSize; }
        Matrix& getWorldTransform() { return _worldTransform; }
        float dt() const { return 1.0 / fps; }
        
        void setOrientation(Orientation orientation);
        void setDaemonForeground(bool fore = true) { _daemonForeground = fore; }
        
        void init0(const Vec2i& screenSize);
        void init1();
        void deinit();
        void pause();
        void resume();
        
        void useScene(Scene* scene, bool deleteCurrent);
        
        void update();
        void render();
        
    private:
        bool _initialized = false;
        bool _running = false;
        
        Scene* _daemon = nullptr;
        bool _daemonForeground = false;
        
        Scene* _currentScene = nullptr;
        std::pair<Scene*, bool> _nextScene;
        
        Orientation _orientation;
        Vec2i _screenSize; // in points
        
        std::string _resourcePath;
        bool _retinaDisplay;
        
        Matrix _worldTransform;
        
        Manager() = default;
        ~Manager() = default;
    };
    
}

#endif