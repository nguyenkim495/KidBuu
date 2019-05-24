#pragma once

#include "Shaders.h"
#include "SpriteModel.h"

class Postprocessing
{
public:
	Postprocessing();
	~Postprocessing();

	float m_deltaTime;

	void Init(programShaderInfo shaderinfor);
	void PreparePostProcessBuffer();
	void DonePostProcessBuffer();
	void Draw();
	void Update(float dt);

private:
	GLuint m_vbo_Framebuffer;
	GLuint m_vuv_Framebuffer;
	
	GLuint m_frameBufferIndexID;
	GLuint m_colorTexID;
	GLuint m_depthTexID;
	programShaderInfo m_shaderInfo;

};