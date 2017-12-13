#include "stdafx.h"
#include "SpriteModel.h"
#include <../Utilities/TGA.h>
#include <cstdio>

#define PRE_LOAD "../.."

SpriteModel::SpriteModel()
{
//	m_cFileName = new char[10];
	m_cFileTextureName = new char[100];
}

SpriteModel::~SpriteModel()
{
	//delete m_cFileName;
	delete m_cFileTextureName;
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

	fscanf(pFile, "NrTexture: %s", m_cFileTextureName);
	fclose(pFile);
	return true;
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
	if(m_imageData)
		return m_imageData;
	int w, h, bpp;
	LoadTGA(m_cFileTextureName, 0, &w, &h, &bpp);
	m_imageData = new imageData();
	m_imageData->data = new char[w*h*bpp/8];
	LoadTGA(m_cFileTextureName, m_imageData->data, &m_imageData->w, &m_imageData->h, &m_imageData->bpp);

	return m_imageData;
}

void SpriteModel::Release()
{
	if(m_vertexv5ArrVertices)
		delete[] m_vertexv5ArrVertices;
	if(m_indiceFormatArrIndices)
		delete[] m_indiceFormatArrIndices;
	if(m_imageData->data)
	{
		delete m_imageData->data;
		delete m_imageData;
	}
}