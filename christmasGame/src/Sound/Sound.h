#ifndef Sound
#include "irrKlang.h"

using namespace irrklang;

class Sound //using irrKlang
{
public:

	Sound();
	Sound(char* filename);
	virtual ~Sound();
	bool play();
	bool stop();
	bool pause();

private:
	ISound* m_music;
	char* m_filename;
	bool m_isPlaying;
	bool m_isStoped;
	bool m_isPausing;

};

#endif