#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
#include <math.h>

Camera::Camera()
{
	m_fSpeed = 20;
	{
		m_Vec3Position.x = 5;
		m_Vec3Position.y = 5;
		m_Vec3Position.z = 1000;
		//m_Vec3Position.z = 50;
	}
	m_Vec3Up = Vector3(0.0f, 1.0f, 0.0f);
	m_Vec3Target = Vector3(0.0f, 0.0f, 0.0f);
	m_matTranslation.SetTranslation(m_Vec3Position);
	m_matRotaion.SetRotationX(0);
	m_projection.SetPerspective(45.0f, Globals::screenWidth/Globals::screenHeight, 1.0f, 500000.0f);
	//m_matWVP = getWVPMatrix();
}

bool Camera::moveCamera(Direction direc)
{
	Vector3 deltaMove;
	switch (direc)
	{
	case FORWARD:
		deltaMove = -(m_Vec3Position - m_Vec3Target).Normalize()*m_fSpeed;
		break;
	case BACKWARD:
		deltaMove = (m_Vec3Position - m_Vec3Target).Normalize()*m_fSpeed;
		break;
	case LEFT:
		deltaMove.x = -m_fSpeed/2;
		break;
	case RIGHT:
		deltaMove.x = abs(m_fSpeed/2);
		break;
	case UP:
		break;
	case DOWN:
		break;
	default:
		break;
	}

	m_Vec3Position += deltaMove;
	m_Vec3Target += deltaMove;

	esLogMessage("deltaMove: %f,%f,%f\n", deltaMove.x, deltaMove.y, deltaMove.z);

	return false;
}

bool Camera::rotationCamera(Direction direc)
{
	//m_fSpeed = m_fSpeed*1.5;
	Vector4 localTarget = Vector4(0, 0, -(m_Vec3Position - m_Vec3Target).Length(), 1);
	Vector4 localNewTarget;
	switch (direc)
	{
	case FORWARD:
		break;
	case BACKWARD:
		break;
	case LEFT:
		localNewTarget = localTarget*m_matRotaion.SetRotationY(delta);
		break;
	case RIGHT:
		//m_fSpeed -= m_f
		localNewTarget = localTarget*m_matRotaion.SetRotationY(-delta);
		break;
	case UP:
		localNewTarget = localTarget*m_matRotaion.SetRotationX(m_fSpeed);
		break;
	case DOWN:
		localNewTarget = localTarget*m_matRotaion.SetRotationX(-m_fSpeed);
		break;
	default:
		break;
	}

	Vector4 worldNewTarget =  localTarget * calculateWorldMatrix();
	
	esLogMessage("localTarget: %f,%f,%f\n", localTarget.x, localTarget.y, localTarget.z);
	esLogMessage("worldNewTarget: %f,%f,%f\n", worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);


	{
		m_Vec3Target.x += worldNewTarget.x;
		m_Vec3Target.y += worldNewTarget.y;
		m_Vec3Target.z += worldNewTarget.z;
	}

	return false;
}

void Camera::Update(float dt)
{
	delta = dt;
	//Vector3 deltaMove = -(m_Vec3Position - m_Vec3Target).Normalize()*dt*m_fSpeed;
	//m_Vec3Position += deltaMove;
	//m_Vec3Target += deltaMove;
}


Matrix Camera::calculateWorldMatrix()
{
	Matrix worldMatrix;
	worldMatrix = m_matRotaion*m_matTranslation; //worldMatrix = S*R*T
	return worldMatrix;
}
Matrix Camera::calculateViewMatrix()
{
	Matrix View;
	Vector3 Zaxis = (m_Vec3Position - m_Vec3Target).Normalize();
	Vector3 Xaxis = (m_Vec3Up.Cross(Zaxis)).Normalize();
	Vector3 Yaxis = (Zaxis.Cross(Xaxis)).Normalize();
	View.m[0][0] = Xaxis.x; View.m[0][1] = Yaxis.x; View.m[0][2] = Zaxis.x; View.m[0][3] = 0;
	View.m[1][0] = Xaxis.y; View.m[1][1] = Yaxis.y; View.m[1][2] = Zaxis.y; View.m[1][3] = 0;
	View.m[2][0] = Xaxis.z; View.m[2][1] = Yaxis.z; View.m[2][2] = Zaxis.z; View.m[2][3] = 0;
	View.m[3][0] = -(m_Vec3Position.Dot(Xaxis)); View.m[3][1] = -(m_Vec3Position.Dot(Yaxis)); View.m[3][2] = -(m_Vec3Position.Dot(Zaxis)); View.m[3][3] = 1;
	return View;
}

Matrix Camera::getWVPMatrix(Matrix worldObj)
{
	m_matWVP = worldObj*calculateViewMatrix()*m_projection;
	return m_matWVP;
}