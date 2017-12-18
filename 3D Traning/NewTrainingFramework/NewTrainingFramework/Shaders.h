#pragma once
#include "../Utilities/utilities.h"

struct programShaderInfo
{
	GLuint	programID;
	GLuint	a_Position;
	GLuint	a_Color;
	GLuint	a_UV;
	GLuint	a_Normal;
	GLuint	u_s_Texture;
	GLuint	u_s_Texture2;//Displ
	GLuint	u_s_Texture3;//Mask
	GLuint	u_WVP;
	GLuint	u_other1;//dMax
	GLuint	u_other2;//u_Time
	//
	GLuint	a_PosW;
	GLuint	u_CameraPosition;
	GLuint	u_LightDirection;
	//
public:
	void Init()
	{
		programID = -1;
		a_Position = -1;
		a_Color = -1;
		a_UV = -1;
		u_s_Texture = -1;
		u_s_Texture2 = -1;
		u_s_Texture3 = -1;
		u_WVP = -1;
		u_other1 = -1;
		u_other2 = -1;
	}
};

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];

	GLint positionAttribute;
	GLint colorAttribute;
	GLint uvAttribute;
	GLint samplerTextUniform;
	GLint WVPMatrix;

	programShaderInfo m_ShaderInfo;
	programShaderInfo GetShaderInfo();

	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};
