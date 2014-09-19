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

#ifndef SOL_AUDIO_H
#define SOL_AUDIO_H

#include <vector>
#include "SolFile.h"
#include "SolResourceManager.h"
#include "SolSceneNode.h"

#if SOL_USE_REFERENCE_VORBIS
#   include "vorbisfile.h"
#else
#   include "stb_vorbis.h"
#endif

namespace sol
{
    
    class Audio : public Resource, public SceneNode
    {
        friend class ResourceManager;
        
    public:
        static void init();
        static void deinit();
        
        bool isPlaying() const { return _playing; }
        bool isLooping() const { return _looping; }
        
        virtual void play();
        virtual void loop();
        void pause();
        virtual void stop();
                
    protected:
        File _f;
        
#if SOL_USE_REFERENCE_VORBIS
        OggVorbis_File _vorbis;
        vorbis_info* _info;
        std::vector<char> _buffer;
#else
        stb_vorbis* _vorbis = nullptr;
        stb_vorbis_info _info;
        std::vector<short> _buffer;
#endif
        
        unsigned int _sourceHandle = 0;
        
        bool _playing = false;
        bool _looping = false;
                
        Audio(const std::string& filename);
        virtual ~Audio();
        
        virtual bool load();
        
        // internal use
        void close();
        bool fillBuffer(unsigned int bufferHandle);
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class BufferedAudio : public Audio
    {
        friend class ResourceManager;
        
    public:
        void play() override;
        void loop() override;
        
    private:
        unsigned int _bufferHandle;
        
        // called by friend ResourceManager
        BufferedAudio(const std::string& filename) : Audio(filename) {}
        ~BufferedAudio();
        
        bool load() override;
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class StreamedAudio : public Audio
    {
        friend class Conductor;
        friend class ResourceManager;
        
    public:
        std::function<void ()> onEnd;
    
        void play() override;
        void loop() override;
        void stop() override;
        
        void update() override;
        
    private:
        unsigned int _bufferHandles[2];
        
        // called by friend ResourceManager
        StreamedAudio(const std::string& filename) : Audio(filename) {}
        ~StreamedAudio();
        
        bool load() override;
    };
    
}

#endif