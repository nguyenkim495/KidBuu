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
private:
	Vector3 m_Vec3Position;
	float m_fRotaion;

	Vector3 m_Vec3MVP;
public:
	bool moveCamera(Direction direc);
	bool rotationCamera(Direction direc);
	Vector4 calculateViewMatrix();
	Vector4 calculateWorldMatrix();
	void Update(float dt);

};
#endif