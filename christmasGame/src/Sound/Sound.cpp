#include "Sound.h"
#include "SoundManager.h"

///////////////////////////////////////////////////////////////////////////
/*Currently we just run 2D sound, 3D sound will implemetn in furture
*/
Sound::Sound(char* filename, bool isSound2D = true):
	m_filename(filename), m_isPlaying(false), m_isPausing(false), m_isStoped(false), m_sound2D(isSound2D)
{
	m_music = nullptr;
	m_music =  isSound2D ?
		(SoundManager::getSingleton()->getEngineSound()->play2D(m_filename, false, true)) : 
		(SoundManager::getSingleton()->getEngineSound()->play3D(m_filename, irrklang::vec3df(0, 0, 0), false, true, true));
}

///////////////////////////////////////////////////////////////////////////
Sound::~Sound()
{
	if(m_music)
	{
		m_music->drop();
	}
	
}

bool Sound::play()
{
	if(m_music)
	{
		m_music->setIsPaused(false);
		m_isPlaying = true;
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

bool Sound::resume()
{
	if(!m_isStoped && m_isPausing)
	{
		m_music->setIsPaused(false);
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