#include "SoundManager.h"


SoundManager* SoundManager::m_soundSingleton = nullptr;
SoundManager::SoundManager()
{
	
}

///////////////////////////////////////////////////////////////////////////
SoundManager::~SoundManager()
{
	//return;
}

///////////////////////////////////////////////////////////////////////////
bool SoundManager::createEngineSound()
{
	m_engineSound = createIrrKlangDevice();
	if(m_engineSound)
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////
bool SoundManager::dropEngineSound()
{
	if(m_engineSound)
	{
		m_engineSound->drop();
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
ISoundEngine* SoundManager::getEngineSound()
{
	if(m_engineSound)
		return m_engineSound;
}

///////////////////////////////////////////////////////////////////////////
bool SoundManager::createSingleton()
{
	if (!m_soundSingleton)
	{
		m_soundSingleton = new SoundManager();
		return true;
	}
}

///////////////////////////////////////////////////////////////////////////
SoundManager* SoundManager::getSingleton()
{
	if(m_soundSingleton)
		return m_soundSingleton;
	else
		nullptr;
}