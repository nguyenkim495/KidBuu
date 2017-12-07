#ifndef _SPRITE_MODEL_H_
#define _SPRITE_MODEL_H_
#include "../Utilities/Math.h"


struct Vertexv5 //*.nfg format
{
	Vector3 Position;
	Vector3 Normal;
	Vector3 BiNormal;
	Vector3 tgt;
	Vector2 UV;
};

struct IndiceFormat
{
	GLuint first;
	GLuint second;
	GLuint third;
};

class SpriteModel
{
public:
	SpriteModel();
	~SpriteModel();
	bool LoadModelFile(char*);
	bool ClearModelData();
	Vector3 * GetVertexModel();
	IndiceFormat * GetIndicesModel();

	char *m_cFileName;
	int m_iNumVertices;
	int m_iNumIndices;
	Vertexv5 * m_vertexv5ArrVertices;
	IndiceFormat * m_indiceFormatArrIndices;

private:
	
};
#endif