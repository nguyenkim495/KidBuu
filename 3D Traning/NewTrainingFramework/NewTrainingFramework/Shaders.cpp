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
	samplerTextUniform = glGetUniformLocation(program, "u_s_texture");
	WVPMatrix = glGetUniformLocation(program, "u_WVP");

	return 0;
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