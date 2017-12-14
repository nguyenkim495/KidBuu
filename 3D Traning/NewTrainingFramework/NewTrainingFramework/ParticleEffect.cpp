#pragma once
#include <stdafx.h>
#include "ParticleEffects.h"
#include "../Utilities/TGA.h"
#include "Camera.h"


extern Camera myCamera;

ParticleEffect::ParticleEffect()
{
	m_deltaTime = 0.0f;
}

ParticleEffect::~ParticleEffect()
{

}

void ParticleEffect::Init(char* fileName, programShaderInfo shaderinfor)
{
	SpriteModel::LoadModelFile(fileName);
	
	int w, h, bpp;
	//texture 1
	LoadTGA(m_cFileTextureName[0], 0, &w, &h, &bpp);
	m_imageData[0] = new imageData();
	m_imageData[0]->data = new char[w*h*bpp/8];
	LoadTGA(m_cFileTextureName[0], m_imageData[0]->data, &m_imageData[0]->w, &m_imageData[0]->h, &m_imageData[0]->bpp);
	//texture 2
	LoadTGA(m_cFileTextureName[1], 0, &w, &h, &bpp);
	m_imageData[1] = new imageData();
	m_imageData[1]->data = new char[w*h*bpp/8];
	LoadTGA(m_cFileTextureName[1], m_imageData[1]->data, &m_imageData[1]->w, &m_imageData[1]->h, &m_imageData[1]->bpp);
	//texture 2
	LoadTGA(m_cFileTextureName[2], 0, &w, &h, &bpp);
	m_imageData[2] = new imageData();
	m_imageData[2]->data = new char[w*h*bpp/8];
	LoadTGA(m_cFileTextureName[2], m_imageData[2]->data, &m_imageData[2]->w, &m_imageData[2]->h, &m_imageData[2]->bpp);

	////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////texture 1
	glGenBuffers(1, &m_bufferIndex.textureId);
	glBindTexture(GL_TEXTURE_2D, m_bufferIndex.textureId);
	if(m_imageData[0]->bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_imageData[0]->w, m_imageData[0]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageData[0]->data);
	}
	else//32?
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_imageData[0]->w, m_imageData[0]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imageData[0]->data);
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

	////////////////////////////////////////////////////texture 2//Displ
	glGenBuffers(1, &m_bufferIndex.textureId_2);
	glBindTexture(GL_TEXTURE_2D, m_bufferIndex.textureId_2);
	if(m_imageData[1]->bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_imageData[1]->w, m_imageData[1]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageData[1]->data);
	}
	else//32?
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_imageData[1]->w, m_imageData[1]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imageData[1]->data);
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

	////////////////////////////////////////////////////texture 3
	glGenBuffers(1, &m_bufferIndex.textureId_3);
	glBindTexture(GL_TEXTURE_2D, m_bufferIndex.textureId_3);
	if(m_imageData[2]->bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_imageData[2]->w, m_imageData[2]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageData[2]->data);
	}
	else//32?
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_imageData[2]->w, m_imageData[2]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imageData[2]->data);
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

	WorldObj.SetScale(20);

}

void ParticleEffect::Update(float dt)
{
	WVPMatrix = myCamera.getWVPMatrix(WorldObj);
	m_deltaTime += dt;
}

void ParticleEffect::Draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	
	//texture 1
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_bufferIndex.textureId);
	glUniform1i(m_shaderInfo.u_s_Texture, 0);
	//Texure 2
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_bufferIndex.textureId_2);
	glUniform1i(m_shaderInfo.u_s_Texture2, 0);
	//Texture 3
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_bufferIndex.textureId_3);
	glUniform1i(m_shaderInfo.u_s_Texture3, 0);
	//WVP matrix
	//worldObj.SetRotationY(Angle);
	glUniform1f(m_shaderInfo.u_other2, m_deltaTime);
	glUniformMatrix4fv(m_shaderInfo.u_WVP, 1, false, WVPMatrix.getDataMembers());

	//bind index then draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferIndex.iboId);
	//glDrawElements(GL_LINES, m_iNumIndices, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, m_iNumIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisable(GL_BLEND);
}
