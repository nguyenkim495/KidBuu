#pragma once

#include "Shaders.h"
#include "SpriteModel.h"

class ParticleEffect : public SpriteModel
{
public:
	ParticleEffect();
	~ParticleEffect();

	float m_deltaTime;

	void Init(char* fileName, programShaderInfo shaderinfor);
	void Draw();
	void Update(float dt);

private:

};