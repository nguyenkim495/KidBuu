#ifndef _SPRITE_MODEL_H_
#define _SPRITE_MODEL_H_
#include "../Utilities/Math.h"
#include "Shaders.h"

struct Vertexv5 //*.nfg format
{
	Vector3 Position;
	Vector3 Normal;
	Vector3 BiNormal;
	Vector3 tgt;
	Vector2 UV;
};

struct index
{
	GLint first;
	GLint second;
	GLint third;
};

struct imageData
{
	int w;
	int h;
	int bpp;
	char* data;
};

struct bufferIndex
{
	GLuint vboId;
	GLuint iboId;
	GLuint uvboId;
	GLuint nboId;
	GLuint textureId; //can replace by GLuint* textureId
	GLuint textureId_2;
	GLuint textureId_3;

};



class SpriteModel
{
public:
	SpriteModel();
	~SpriteModel();
	///////////////////////////////////////////////////////////
	void Init(char*, programShaderInfo);
	void Draw();
	void Update(float dl);
	
	///////////////////////////////////////////////////////////
	bool LoadModelFile(char*);
	bool ClearModelData();
	void Release();

	///////////////////////////////////////////////////////////
	bool m_bPause;
	bool keyDown(unsigned char, bool);

	Vector3* GetVertexModel();
	Vector3* GetNormalVector();
	index * GetIndicesModel();
	Vector2* GetUVModel();
	imageData* GetImageData();

	void SetPosition(Vector3 position);

	bufferIndex m_bufferIndex;
	programShaderInfo m_shaderInfo;

	char *m_cFileName;
	char *m_cFileTextureName[3];
	imageData* m_imageData[3];
	int m_iNumVertices;
	int m_iNumIndices;
	Vertexv5 * m_vertexv5ArrVertices;
	index * m_indiceFormatArrIndices;

	float Angle;
	Matrix WVPMatrix;
	Matrix WorldObj;

	Vector3 m_Position;
	

private:
	
};
#endif