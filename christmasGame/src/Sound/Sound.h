#ifndef Sound
#include "irrKlang.h"

using namespace irrklang;

class Sound //using irrKlang
{
public:

	Sound();
	Sound(char* filename, bool isSound2D);
	virtual ~Sound();
	bool play();
	bool stop();
	bool pause();
	bool resume();

private:
	ISound* m_music;
	char* m_filename;
	bool m_sound2D;
	bool m_isPlaying;
	bool m_isStoped;
	bool m_isPausing;

};

#endif