#include <stdafx.h>
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	colorAttribute = glGetAttribLocation(program, "a_AColor");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	samplerTextUniform = glGetUniformLocation(program, "u_s_Texture");
	WVPMatrix = glGetUniformLocation(program, "u_WVP");
	m_ShaderInfo.u_World = glGetUniformLocation(program, "u_World");

	m_ShaderInfo.Init();
	////adding a new shaderInfo for all sprite
	m_ShaderInfo.programID = program;
	m_ShaderInfo.a_Position = positionAttribute;
	m_ShaderInfo.a_Color = colorAttribute;
	m_ShaderInfo.a_UV = uvAttribute;
	m_ShaderInfo.u_s_Texture = samplerTextUniform;
	m_ShaderInfo.u_WVP = WVPMatrix;
	//for particleeffect
	m_ShaderInfo.u_s_Texture2 = glGetUniformLocation(program, "u_s_TextureDispl");
	m_ShaderInfo.u_s_Texture3 = glGetUniformLocation(program, "u_s_TextureMask");
	m_ShaderInfo.u_other1 = glGetUniformLocation(program, "dMax");
	m_ShaderInfo.u_other2 = glGetUniformLocation(program, "u_Time");
	//for lighting
	m_ShaderInfo.a_PosW = glGetAttribLocation(program, "a_posW");
	m_ShaderInfo.a_Normal = glGetAttribLocation(program, "a_normal");
	m_ShaderInfo.u_CameraPosition = glGetUniformLocation(program, "u_EyePos");
	m_ShaderInfo.u_LightDirection = glGetUniformLocation(program, "u_LightDirection");




	return 0;
}


programShaderInfo Shaders::GetShaderInfo()
{
	return m_ShaderInfo;
}
Shaders::~Shaders()
{
	if(program != -1)
		glDeleteProgram(program);
	if(vertexShader != -1)
		glDeleteShader(vertexShader);
	if(fragmentShader != -1)
		glDeleteShader(fragmentShader);
}