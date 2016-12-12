#include "irrKlang.h"

class Sound //using irrKlang
{
public:

	Sound();
	Sound(char* filename);
	virtual ~Sound();
	void play();
	void stop();
	void pause();

private:
	bool m_isPlaying;
	bool m_isStoped;
	bool m_isPausing;
	



};