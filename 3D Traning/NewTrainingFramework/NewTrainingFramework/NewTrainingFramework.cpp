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
#include "ParticleEffects.h"


GLuint vboId;//vertex
GLuint iboId;
GLuint uvboId;
GLuint cboId;//texure

GLuint WVPId;
GLuint vertexArrayObject;

Camera myCamera;
GLfloat globalAngle;

Shaders myShaders;
Shaders myFireShader;

SpriteModel mySprite;
ParticleEffect myFireEffect;

Matrix WorldObj;


Vector3* vertextBuff;
index* indiceBuff;
Vector2* uvBuff;


int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );

	int result = myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	int resultFire = myFireShader.Init("../Resources/Shaders/FireSample.vs", "../Resources/Shaders/FireSample.fs");

	mySprite.Init("../../NewResourcesPacket/Models/bus.nfg", myShaders.GetShaderInfo());
	myFireEffect.Init("../../NewResourcesPacket/Models/fire.nfg", myFireShader.GetShaderInfo());
	return result&&resultFire;
}

void Draw ( ESContext *esContext )
{
	GLuint offset = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//mySprite.Draw();
	myFireEffect.Draw();


	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );

	
}



void Update ( ESContext *esContext, float deltaTime )
{
	globalAngle += (deltaTime/2);

	myCamera.Update(deltaTime);
	mySprite.Update(deltaTime);
	myFireEffect.Update(deltaTime);
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

