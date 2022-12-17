#pragma once
#include "GameEntity.h"

class Terreny : public GameEntity
{
public:
	Terreny(Transform transform, Model* model_terreny, GLuint shader_id, float speed);
	void update(float delta_time);

private:
	int n_terrenys;
	float longitud_terreny;
	float speed;
};