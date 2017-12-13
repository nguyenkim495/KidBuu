// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Camera.h"
#include "SpriteModel.h"
#include "../Utilities/TGA.h"


GLuint vboId;//vertex
GLuint iboId;
GLuint uvboId;
GLuint cboId;//texure

GLuint WVPId;
GLuint vertexArrayObject;

Shaders myShaders;
Camera myCamera;
GLfloat globalAngle;
SpriteModel mySprite;
Matrix WorldObj;


Vector3* vertextBuff;
index* indiceBuff;
Vector2* uvBuff;


int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	mySprite.LoadModelFile("../../NewResourcesPacket/Models/witch.nfg");

	WorldObj.SetScale(3.5);

	//vertex buffer
	vertextBuff = mySprite.GetVertexModel();
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, mySprite.m_iNumVertices*sizeof(Vector3), vertextBuff, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//release

	//index buffer
	indiceBuff = mySprite.GetIndicesModel();
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mySprite.m_iNumIndices*sizeof(index), indiceBuff, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//release

	//uv buffer
	uvBuff = mySprite.GetUVModel();
	glGenBuffers(1, &uvboId);
	glBindBuffer(GL_ARRAY_BUFFER, uvboId);
	glBufferData(GL_ARRAY_BUFFER, mySprite.m_iNumVertices*sizeof(Vector2), uvBuff, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//release

	//texture load
	glGenBuffers(1, &cboId);
	glBindTexture(GL_TEXTURE_2D, cboId);
	int w,h, bpp;
	LoadTGA("../../NewResourcesPacket/Textures/Witch.tga", 0, &w, &h, &bpp);
	char* bufferTGA = new char[w*h*bpp/8];
	LoadTGA("../../NewResourcesPacket/Textures/Witch.tga", bufferTGA, &w, &h, &bpp);

	if(bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);
	}
	else//32?
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA);
	}
	delete[] bufferTGA;// free buffer on RAM after binded to VRAM
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);
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

	//test statge
	glEnable(GL_SCISSOR_TEST); //order Scissors Test -> Stencil Test -> Depth Test.
	//glEnable(GL_DEPTH_TEST);

	int result = myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	return result;
}

void Draw ( ESContext *esContext )
{
	GLuint offset = 0;
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders.program);

	//enable vertex buff to position in shader
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glEnableVertexAttribArray(myShaders.positionAttribute);
	glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//uv
	glBindBuffer(GL_ARRAY_BUFFER, uvboId);
	glEnableVertexAttribArray(myShaders.uvAttribute);
	glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cboId);
	glUniform1i(myShaders.samplerTextUniform, 0);
	
	//WVP matrix
	WorldObj.SetRotationY(globalAngle);
	glUniformMatrix4fv(myShaders.WVPMatrix, 1, false, myCamera.getWVPMatrix(WorldObj));

	//bind index then draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glDrawElements(GL_TRIANGLES, mySprite.m_iNumIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	


	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );

	
}



void Update ( ESContext *esContext, float deltaTime )
{
	//myCamera.setSpeed(deltaTime*5.0f);
	globalAngle += deltaTime;

	//esLogMessage("deltatime: %f\n", deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	bool test;
	switch (key)
	{
		//movement
	case 'W':
		myCamera.moveCamera(Direction::FORWARD);
		break;
	case 'S':
		myCamera.moveCamera(Direction::BACKWARD);
		break;
	case 'A':
		myCamera.moveCamera(Direction::LEFT);
		break;
	case 'D':
		myCamera.moveCamera(Direction::RIGHT);
		break;
		//rotation
	case 0x26:
		myCamera.rotationCamera(Direction::UP);
		break;
	case 0x28:
		myCamera.rotationCamera(Direction::DOWN);
		break;
	case 0x25:
		myCamera.rotationCamera(Direction::LEFT);
		break;
	case 0x27:
		myCamera.rotationCamera(Direction::RIGHT);
		break;
	default:
		break;
	}
}

void CleanUp()
{
	mySprite.Release();
	if(vertextBuff)
		delete[] vertextBuff;
	if(indiceBuff)
		delete[] indiceBuff;
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

