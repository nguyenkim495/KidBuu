#include "Sound.h"
#include "SoundManager.h"

Sound::Sound(char* filename):
	m_filename(filename), m_isPlaying(false), m_isPausing(false), m_isStoped(false)
{
	m_music = nullptr;
	if(!m_music)
		m_music =  SoundManager::getSingleton()->getEngineSound()->play2D(m_filename, false, false);
}

Sound::~Sound()
{
	if(m_music)
	{
		m_music->drop();
		//m_music = nullptr;
	}
	
}

bool Sound::play()
{
	if(m_music)
	{
		m_music->setIsPaused(false);
		m_isPausing = true;
		return true;
	}
	return false;
}

bool Sound::pause()
{
	if(m_music && m_isPlaying)
	{
		m_music->setIsPaused(true);
		m_isPausing = true;
		return true;
	}
	return false;
}

bool Sound::stop()
{
	if(m_music)
	{
		m_music->stop();
		m_isStoped = true;
		return true;
	}
	return false;
}