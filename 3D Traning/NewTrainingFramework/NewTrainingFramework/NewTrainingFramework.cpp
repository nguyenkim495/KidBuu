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
Shaders myShadersLighted;
Shaders myFireShader;

SpriteModel mySprite;
SpriteModel mySpriteLighted;
ParticleEffect myFireEffect;

Matrix WorldObj;


Vector3* vertextBuff;
index* indiceBuff;
Vector2* uvBuff;

Vector4 posLight = Vector4(10.0f, 10.0f, 10.0f, 1.0f);


int Init ( ESContext *esContext )
{
	glClearColor ( 0.7f, 0.7f, 0.7f, 1.0f );

	int result = myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	int resultFire = myFireShader.Init("../Resources/Shaders/FireSample.vs", "../Resources/Shaders/FireSample.fs");
	int resultLighted = myShadersLighted.Init("../Resources/Shaders/ModelsLighted.vs", "../Resources/Shaders/ModelsLighted.fs");

	mySprite.Init("../../NewResourcesPacket/Models/Croco.nfg", myShaders.GetShaderInfo());
	mySpriteLighted.Init("../../NewResourcesPacket/Models/Croco.nfg", myShadersLighted.GetShaderInfo());
	//mySprite.Init("../../NewResourcesPacket/Models/Marine.nfg", myShaders.GetShaderInfo());
	//mySprite.Init("../../NewResourcesPacket/Models/Woman1.nfg", myShaders.GetShaderInfo());
	myFireEffect.Init("../../NewResourcesPacket/Models/fire.nfg", myFireShader.GetShaderInfo());
	
	mySprite.SetPosition(Vector3(300, 0, 0));
	mySpriteLighted.SetPosition(Vector3(-300, 0, 0));

	return result&&resultFire&&resultLighted;
}

void Draw ( ESContext *esContext )
{
	GLuint offset = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	


	mySprite.Draw();
	myFireEffect.Draw();

	Vector4 worldPos =  posLight*myCamera.calculateWorldMatrix();

	glUseProgram(myShadersLighted.program);
	//glUniform3f(mySpriteLighted.m_shaderInfo.u_LightDirection, worldPos.x, worldPos.y, worldPos.z);
	glUniform3f(mySpriteLighted.m_shaderInfo.u_LightDirection, 10.0f, 10.0f, 10.0f);
	glUniformMatrix4fv(mySpriteLighted.m_shaderInfo.u_World, 1, false, myCamera.calculateWorldMatrix().getDataMembers());

	mySpriteLighted.Draw();


	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );

	
}



void Update ( ESContext *esContext, float deltaTime )
{
	globalAngle += (deltaTime/2);

	myCamera.Update(deltaTime);

	mySprite.Update(deltaTime);
	mySpriteLighted.Update(deltaTime);

	myFireEffect.Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
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
	case 32: //space
		mySprite.keyDown(key, bIsPressed);
		mySpriteLighted.keyDown(key, bIsPressed);
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

	esCreateWindow ( &esContext, "OpenGL", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

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

