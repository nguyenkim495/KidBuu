#include "stdafx.h"
#include "SpriteModel.h"
#include <../Utilities/TGA.h>
#include <cstdio>
#include "Camera.h"

#define PRE_LOAD "../.."

extern Camera myCamera;

SpriteModel::SpriteModel()
{
//	m_cFileName = new char[10];
	//m_cFileTextureName = new char[100];
}

SpriteModel::~SpriteModel()
{
	//delete m_cFileName;
	//delete m_cFileTextureName;
}

bool SpriteModel::LoadModelFile(char *fileName)
{
	FILE *pFile;
	pFile = fopen(fileName, "rt");
	if(pFile == NULL)
	{
		esLogMessage("Can not open the file : %s\n", fileName);
		return false;
	}
	//vertices
	//int numberVertices;
	fscanf(pFile, "NrVertices: %d\n", &m_iNumVertices);
	m_vertexv5ArrVertices = new Vertexv5[m_iNumVertices];
	for(int i = 0; i<m_iNumVertices; i++)
	{
		int temp;
		fscanf(pFile, "   %d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n", &temp,
				&m_vertexv5ArrVertices[i].Position.x, &m_vertexv5ArrVertices[i].Position.y, &m_vertexv5ArrVertices[i].Position.z,
				&m_vertexv5ArrVertices[i].Normal.x,	 &m_vertexv5ArrVertices[i].Normal.y,   &m_vertexv5ArrVertices[i].Normal.z,
				&m_vertexv5ArrVertices[i].BiNormal.x, &m_vertexv5ArrVertices[i].BiNormal.y, &m_vertexv5ArrVertices[i].BiNormal.z,
				&m_vertexv5ArrVertices[i].tgt.x,		 &m_vertexv5ArrVertices[i].tgt.y, &m_vertexv5ArrVertices[i].tgt.z,
				&m_vertexv5ArrVertices[i].UV.x, &m_vertexv5ArrVertices[i].UV.y
			);

	}
	//indices
	//int numberIndices;
	fscanf(pFile, "NrIndices: %d\n", &m_iNumIndices);
	m_indiceFormatArrIndices = new index[m_iNumIndices];
	for(int i = 0; i<m_iNumIndices; i++)
	{
		int temp;
		fscanf(pFile, "   %*d.    %d,    %d,    %d\n",
			&m_indiceFormatArrIndices[i].first, &m_indiceFormatArrIndices[i].second, &m_indiceFormatArrIndices[i].third);
	}

	m_cFileTextureName[0] = new char[100];
	m_cFileTextureName[1] = new char[100];
	m_cFileTextureName[2] = new char[100];
	fscanf(pFile, "NrTexture: %s\n", m_cFileTextureName[0]);
	if(!feof(pFile))
	{
		fscanf(pFile, "NrDispl_Texture: %s\n", m_cFileTextureName[1]);
		fscanf(pFile, "NrMask_Texture: %s\n", m_cFileTextureName[2]);
	}

	fclose(pFile);
	return true;
}

void SpriteModel::Init(char* fileName, programShaderInfo shaderinfor)
{
	//storage->RAM
	LoadModelFile(fileName);
	GetImageData();
	//create buffer RAM->VRAM, prepare for render
	glGenBuffers(1, &m_bufferIndex.vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferIndex.vboId);
	glBufferData(GL_ARRAY_BUFFER, m_iNumVertices*sizeof(Vector3), GetVertexModel(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//release

	//index buffer
	glGenBuffers(1, &m_bufferIndex.iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferIndex.iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iNumIndices*sizeof(index), GetIndicesModel(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//release

	//uv buffer
	glGenBuffers(1, &m_bufferIndex.uvboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferIndex.uvboId);
	glBufferData(GL_ARRAY_BUFFER, m_iNumVertices*sizeof(Vector2), GetUVModel(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//release

	//texture load
	glGenBuffers(1, &m_bufferIndex.textureId);
	glBindTexture(GL_TEXTURE_2D, m_bufferIndex.textureId);
	if(GetImageData()->bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GetImageData()->w, GetImageData()->h, 0, GL_RGB, GL_UNSIGNED_BYTE, GetImageData()->data);
	}
	else//32?
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GetImageData()->w, GetImageData()->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, GetImageData()->data);
	}
	//delete[] bufferTGA;// free buffer on RAM after binded to VRAM
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (true)// (tiling == REPEAT)
    {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
	else if (false)//(tiling == CLAMP_TO_EDGE)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }


	m_shaderInfo = shaderinfor;


	WorldObj.SetTranslation(Vector3(50.0f, 0.0f, 0.0f));
}

void SpriteModel::Draw()
{
	glUseProgram(m_shaderInfo.programID);

	//enable vertex buff to position in shader
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferIndex.vboId);
	glEnableVertexAttribArray(m_shaderInfo.a_Position);
	glVertexAttribPointer(m_shaderInfo.a_Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//uv
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferIndex.uvboId);
	glEnableVertexAttribArray(m_shaderInfo.a_UV);
	glVertexAttribPointer(m_shaderInfo.a_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_bufferIndex.textureId);
	glUniform1i(m_shaderInfo.u_s_Texture, 0);
	
	//WVP matrix
	//worldObj.SetRotationY(Angle);

	glUniformMatrix4fv(m_shaderInfo.u_WVP, 1, false, WVPMatrix.getDataMembers());

	//bind index then draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferIndex.iboId);
	//glDrawElements(GL_LINES, m_iNumIndices, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, m_iNumIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SpriteModel::Update(float dt)
{
	Angle += (dt/2);
	Matrix mat4; mat4.SetRotationY(Angle);
	WVPMatrix = myCamera.getWVPMatrix(mat4);
}

bool SpriteModel::ClearModelData()
{
	if(m_vertexv5ArrVertices)
	{
		delete m_vertexv5ArrVertices;
		if(m_indiceFormatArrIndices)
			delete m_indiceFormatArrIndices;
		return true;
	}

	return false;
}

Vector3 * SpriteModel::GetVertexModel()
{
	Vector3 * res = new Vector3[m_iNumVertices];
	for(int i = 0; i<m_iNumVertices; i++)
	{
		res[i] = m_vertexv5ArrVertices[i].Position;
	}

	return res;
}


index * SpriteModel::GetIndicesModel()
{
	index * res = new index[m_iNumIndices];
	for(int i = 0; i<m_iNumIndices; i++)
	{
		res[i] = m_indiceFormatArrIndices[i];
	}

	return res;
}

Vector2* SpriteModel::GetUVModel()
{
	Vector2* res = new Vector2[m_iNumVertices];
	for(int i = 0; i < m_iNumVertices; i++)
	{
		res[i] = m_vertexv5ArrVertices[i].UV;
	}

	return res;
}

imageData* SpriteModel::GetImageData()
{
	if(m_imageData[0])
		return m_imageData[0];
	//text 1
	int w, h, bpp;
	LoadTGA(m_cFileTextureName[0], 0, &w, &h, &bpp);
	m_imageData[0] = new imageData();
	m_imageData[0]->data = new char[w*h*bpp/8];
	LoadTGA(m_cFileTextureName[0], m_imageData[0]->data, &m_imageData[0]->w, &m_imageData[0]->h, &m_imageData[0]->bpp);
}

void SpriteModel::Release()
{
	if(m_vertexv5ArrVertices)
		delete[] m_vertexv5ArrVertices;
	if(m_indiceFormatArrIndices)
		delete[] m_indiceFormatArrIndices;
	//if(m_imageData->data)
	//{
	//	delete m_imageData->data;
	//	delete m_imageData;
	//}
}