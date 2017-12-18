#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "../Utilities/Math.h"


enum Direction
{
	FORWARD = 0,
	BACKWARD = 1,
	LEFT = 2,
	RIGHT = 3,
	UP = 4,
	DOWN = 5
};
class Camera
{
public:
	Vector3 m_Vec3Position;
	Vector3 m_Vec3Target; //pending
	Vector3 m_Vec3Up;
	//
	Matrix m_matTranslation;
	Matrix m_matRotaion;
	//
	Matrix m_matWVP;
	Matrix m_projection;
	//const Vector4 WORLDMATRIX;
	float m_fSpeed;
public:
	Camera();
	//~Camera();
	bool moveCamera(Direction direc);
	bool rotationCamera(Direction direc);
	Matrix calculateViewMatrix();
	Matrix calculateWorldMatrix();
	Matrix getWVPMatrix(Matrix);
	float	delta;
	void Update(float dt);
	void setSpeed(float sp)
	{
		m_fSpeed = sp;
	}

	float getSpeed()
	{
		return m_fSpeed;
	}

};
#endif