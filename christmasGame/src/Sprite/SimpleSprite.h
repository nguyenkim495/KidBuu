#include <ITexture.h>
#include <irrList.h>


using namespace irr;
using namespace core;

using namespace video;
using namespace io;

class SimpleSprite
{
public:

	SimpleSprite();
	SimpleSprite(char* filename, vector3df pos);
	virtual ~SimpleSprite();

	bool	m_isVisible;
	void	DrawSprite();
	void	Render();

private:

	ITexture* m_texture;
	vector3df m_position;
	dimension2d<s32> m_textureRegion;
	



};