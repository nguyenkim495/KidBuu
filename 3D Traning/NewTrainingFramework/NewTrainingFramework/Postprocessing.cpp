#pragma once
#include <stdafx.h>
#include "Postprocessing.h"
#include "../Utilities/TGA.h"
#include "Camera.h"
#include "Globals.h"

extern Camera myCamera;

Postprocessing::Postprocessing()
{
	m_deltaTime = 0.0f;
}

Postprocessing::~Postprocessing()
{

}

void Postprocessing::Init(programShaderInfo shaderinfor)
{
	////////////////////////////////////////////////////
	//create FBO and set current FBO to use
	glGenFramebuffers(1, &m_frameBufferIndexID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferIndexID);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
	////////////////////////////////////////////////////IMAGE TEXTURE (texture obj)
	//generate color texture
	glGenTextures(1, &m_colorTexID);
	glBindTexture(GL_TEXTURE_2D, m_colorTexID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//initialize an empty texture with screen width & height
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Globals::screenWidth, Globals::screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	//attach texture to GL_COLOR_ATTACHMENT0
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferIndexID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTexID, 0);

	//bind system default texture
	glBindTexture(GL_TEXTURE_2D, 0);

	////////////////////////////////////////////////////Renderbuffer (rederbufferImage)
	//generate depth texture – same as color texture 
	glGenTextures(1, &m_depthTexID);
	glBindTexture(GL_TEXTURE_2D, m_depthTexID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//initialize an empty texture with screen width & height
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Globals::screenWidth, Globals::screenHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

	//attach texture to GL_DEPTH_ATTACHMENT
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferIndexID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexID, 0);

	//bind system default texture
	glBindTexture(GL_TEXTURE_2D, 0);


	//vertext array
	GLfloat fbo_vertices[] = {
	-1, -1,
	 1, -1,
	-1,  1,
	 1,  1,
	};
	glGenBuffers(1, &m_vbo_Framebuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_Framebuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertices), fbo_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//uv
	GLfloat fbo_uv[] = {
	0, 0,
	 1, 0,
	0,  1,
	 1,  1,
	};
	glGenBuffers(1, &m_vuv_Framebuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vuv_Framebuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertices), fbo_uv, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//release

	m_shaderInfo = shaderinfor;
}

void Postprocessing::Update(float dt)
{
	//WVPMatrix = myCamera.getWVPMatrix(WorldObj);
	//m_deltaTime += dt;
}

void Postprocessing::PreparePostProcessBuffer()
{
	glUseProgram(m_shaderInfo.programID);

	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferIndexID);
}

void Postprocessing::DonePostProcessBuffer()
{
	
}

void Postprocessing::Draw()
{
	glUseProgram(m_shaderInfo.programID);

	glBindTexture(GL_TEXTURE_2D, m_colorTexID);
	glUniform1i(m_shaderInfo.u_s_Texture, 0);

	//enable vertex buff to position in shader
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_Framebuffer);
	glEnableVertexAttribArray(m_shaderInfo.a_Position);
	glVertexAttribPointer(m_shaderInfo.a_Position, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_colorTexID);
	glUniform1i(m_shaderInfo.u_s_Texture, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}