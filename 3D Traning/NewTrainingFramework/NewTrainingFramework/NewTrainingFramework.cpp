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


GLuint vboId;
GLuint cboId;
GLuint iboId;
GLuint WVPId;
GLuint vertexArrayObject;
Matrix WorldObj;


Shaders myShaders;
Camera myCamera;
GLfloat globalAngle;
SpriteModel mySprite;

Vector3* vetexBuf;
IndiceFormat* indices;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	mySprite.LoadModelFile("../../NewResourcesPacket/Models/Marine.nfg");
	//WorldObj.SetScale(0.1, 0.1, 0.1);
	vetexBuf = mySprite.GetVertexModel();
	indices = mySprite.GetIndicesModel();


	//vertex buffer
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, mySprite.m_iNumVertices*sizeof(Vector3), vetexBuf, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//index buffer
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mySprite.m_iNumIndices*sizeof(IndiceFormat), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//creation of shaders and program 
	//esLogMessage("creation of shaders and program");
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	

}

void Draw ( ESContext *esContext )
{
	GLuint offset = 0;
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glEnableVertexAttribArray(myShaders.positionAttribute);
	glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glUniformMatrix4fv(myShaders.WVPMatrix, 1, GL_FALSE, myCamera.getWVPMatrix(WorldObj));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glDrawElements(GL_TRIANGLES, mySprite.m_iNumIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}


void Update ( ESContext *esContext, float deltaTime )
{
	myCamera.setSpeed(deltaTime*5.0f);
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
	//MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

