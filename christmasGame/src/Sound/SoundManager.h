#include "irrKlang.h"

using namespace irrklang;

class SoundManager //using irrKlang
{
public:

	SoundManager();
	//SoundManager();
	virtual ~SoundManager();

	static SoundManager* m_soundSingleton;
	static SoundManager* getSingleton();

	bool createSingleton();
	bool createEngineSound();
	bool dropEngineSound();
	ISoundEngine* getEngineSound();

	

private:
	ISoundEngine* m_engineSound;
	



};