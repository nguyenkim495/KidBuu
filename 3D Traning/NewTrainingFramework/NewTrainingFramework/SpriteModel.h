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

//struct IndiceFormat
//{
//	int first;
//	int second;
//	int third;
//};

struct index
{
	//GLushort id;
	GLint first;
	GLint second;
	GLint third;
};


class SpriteModel
{
public:
	SpriteModel();
	~SpriteModel();
	bool LoadModelFile(char*);
	bool ClearModelData();
	void Release();

	//Vector3* vertexArray;
	//index* indexArray;

	Vector3 * GetVertexModel();
	index * GetIndicesModel();
	Vector2* GetUVModel();

	char *m_cFileName;
	int m_iNumVertices;
	int m_iNumIndices;
	Vertexv5 * m_vertexv5ArrVertices;
	index * m_indiceFormatArrIndices;

private:
	
};
#endif