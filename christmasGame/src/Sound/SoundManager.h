#include "irrKlang.h"

class SoundManager //using irrKlang
{
public:

	SoundManager();
	SoundManager(char* filename);
	virtual ~SoundManager();

	static SoundManager* soundSinglerton;
	bool createSinglerton();//?
	SoundManager* getSingleton();//?

private:

	



};