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
	WVPMatrix = glGetUniformLocation(program, "u_WVP");

	return 0;
}

Shaders::~Shaders()
{
	if(program)
		glDeleteProgram(program);
	if(vertexShader != 0)
		glDeleteShader(vertexShader);
	if(fragmentShader != 0)
		glDeleteShader(fragmentShader);
}