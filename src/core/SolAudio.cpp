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

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include "SolAudio.h"
#include "SolNative.h"
#include "SolScene.h"
#include "SolUtil.h"

namespace sol
{
    
    using std::string;
    
    ALCdevice* gDevice = nullptr;
    ALCcontext* gContext = nullptr;
        
    void Audio::init()
    {
        if (!gDevice)
        {
            gDevice = alcOpenDevice(nullptr);
            gContext = alcCreateContext(gDevice, nullptr);
            alcMakeContextCurrent(gContext);
        }
    }
    
    void Audio::deinit()
    {
        if (gContext) alcDestroyContext(gContext);
        if (gDevice) alcCloseDevice(gDevice);
    }
    
    Audio::Audio(const string& filename) :
        Resource(filename)
    {
        alGenSources(1, &_sourceHandle);
    }
    
    Audio::~Audio()
    {
        close();
        alDeleteSources(1, &_sourceHandle);
    }
    
    bool Audio::load()
    {
        if (!_f.open(Manager::instance().getResourcePath() + _filename, "rb")) return false;
        
#if SOL_USE_REFERENCE_VORBIS
        if (ov_open(_f.getHandle(), &_vorbis, nullptr, 0) < 0)
        {
            SOL_ERROR("Failed to open audio file " << _filename);
            return false;
        }
        
        _info = ov_info(&_vorbis, -1);
#else        
        _vorbis = stb_vorbis_open_file(_f.getHandle(), 0, 0, 0);
        
        if (!_vorbis)
        {
            SOL_ERROR("Failed to open ogg vorbis file " << _filename);
            return false;
        }
        
        _info = stb_vorbis_get_info(_vorbis);
#endif
        
        return true;
    }
    
    void Audio::close()
    {
#if SOL_USE_REFERENCE_VORBIS
        _f.close();
        ov_clear(&_vorbis);
        _info = nullptr;
#else
        if (_vorbis)
        {
            _f.close();
            stb_vorbis_close(_vorbis);
            _vorbis = nullptr;
        }
#endif
    }
    
    void Audio::play()
    {
        alSourcePlay(_sourceHandle);
        _playing = true;        
        _looping = false;
    }
    
    void Audio::loop()
    {
        alSourcePlay(_sourceHandle);
        _playing = true;
        _looping = true;
    }
    
    void Audio::pause()
    {
        alSourcePause(_sourceHandle);
        _playing = false;
    }
    
    void Audio::stop()
    {
        alSourceStop(_sourceHandle);
        _playing = false;
    }
    
    bool Audio::fillBuffer(unsigned int bufferHandle)
    {
        int size = 0;
        
        while (size < _buffer.capacity())
        {
#if SOL_USE_REFERENCE_VORBIS
            int tmp;
            int result = ov_read(&_vorbis, _buffer.data() + size, _buffer.capacity() - size, 0, 2, 1, &tmp);
            if (result > 0) size += result;
#else
            int result = stb_vorbis_get_samples_short_interleaved(_vorbis, _info.channels, _buffer.data() + size, _buffer.capacity() - size);
            if (result > 0) size += result * _info.channels;
#endif
            else break;
        }
        
        if (size == 0) return false;
        
#if SOL_USE_REFERENCE_VORBIS
        alBufferData(bufferHandle, _info->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, _buffer.data(), _buffer.capacity(), _info->rate);
#else
        alBufferData(bufferHandle, _info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, _buffer.data(), size * sizeof(short), _info.sample_rate);
#endif
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    BufferedAudio::~BufferedAudio()
    {
        alDeleteBuffers(1, &_bufferHandle);
    }
    
    bool BufferedAudio::load()
    {
        if (Audio::load())
        {
#if SOL_USE_REFERENCE_VORBIS
            _buffer.reserve(ov_pcm_total(&_vorbis, -1) * _info->channels << 1);
#else
            _buffer.reserve(stb_vorbis_stream_length_in_samples(_vorbis) * _info.channels << 1);
#endif
            
            alGenBuffers(1, &_bufferHandle);
            fillBuffer(_bufferHandle);
            alSourcei(_sourceHandle, AL_BUFFER, _bufferHandle);
            
            close();
            _buffer.clear(); // data is with OpenAL now, so this can be freed
            
            return true;
        }
        
        return false;
    }
    
    void BufferedAudio::play()
    {
        alSourcei(_sourceHandle, AL_LOOPING, AL_FALSE);
        Audio::play();
    }
    
    void BufferedAudio::loop()
    {
        alSourcei(_sourceHandle, AL_LOOPING, AL_TRUE);
        Audio::loop();
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    StreamedAudio::~StreamedAudio()
    {
        alDeleteBuffers(2, _bufferHandles);
    }
    
    bool StreamedAudio::load()
    {
        if (Audio::load())
        {
            _buffer.reserve(SOL_AUDIO_STREAM_BUFFER_SIZE);
            
            alGenBuffers(2, _bufferHandles);
            fillBuffer(_bufferHandles[0]);
            fillBuffer(_bufferHandles[1]);
            alSourceQueueBuffers(_sourceHandle, 2, _bufferHandles);
            
            return true;
        }
        
        return false;
    }
    
    void StreamedAudio::play()
    {
        alSourcei(_sourceHandle, AL_LOOPING, AL_FALSE);
        Audio::play();
    }
    
    void StreamedAudio::loop()
    {
        alSourcei(_sourceHandle, AL_LOOPING, AL_FALSE); // we'll loop streams by refilling the buffers
        Audio::loop();
    }
    
    void StreamedAudio::stop()
    {
#if SOL_USE_REFERENCE_VORBIS
        ov_raw_seek(&_vorbis, 0);
#else
        stb_vorbis_seek_start(_vorbis);
#endif
        Audio::pause();
    }
    
    void StreamedAudio::update()
    {
        if (!_playing) return;
        
        int buffersProcessed;
        
        alGetSourcei(_sourceHandle, AL_BUFFERS_PROCESSED, &buffersProcessed);
        
        while (buffersProcessed--)
        {
            unsigned int bufferHandle;
            
            alSourceUnqueueBuffers(_sourceHandle, 1, &bufferHandle);
            
            if (fillBuffer(bufferHandle))
            {
                alSourceQueueBuffers(_sourceHandle, 1, &bufferHandle);
            }
            else
            {
                if (_looping)
                {
#if SOL_USE_REFERENCE_VORBIS
                    ov_raw_seek(&_vorbis, 0);
#else
                    stb_vorbis_seek_start(_vorbis);
#endif
                    assert(fillBuffer(bufferHandle));
                    alSourceQueueBuffers(_sourceHandle, 1, &bufferHandle);
                }
                else if (onEnd) onEnd();
            }
        }
    }
    
}