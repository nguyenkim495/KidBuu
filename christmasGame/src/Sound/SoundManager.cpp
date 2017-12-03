#include "SoundManager.h"


SoundManager* SoundManager::m_soundSingleton = nullptr;
SoundManager::SoundManager()
{
	m_engineSound = nullptr;
}

///////////////////////////////////////////////////////////////////////////
SoundManager::~SoundManager()
{
	//return;
	m_soundSingleton = 0;
	
}

///////////////////////////////////////////////////////////////////////////
void SoundManager::Init()
{
	if(!m_soundSingleton)
		m_soundSingleton = new SoundManager();
	if(!m_engineSound)
		createEngineSound();
}
///////////////////////////////////////////////////////////////////////////
bool SoundManager::createEngineSound()
{
	m_engineSound = irrklang::createIrrKlangDevice();
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