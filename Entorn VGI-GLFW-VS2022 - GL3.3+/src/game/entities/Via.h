#pragma once
#include "GameEntity.h"

class Via : public GameEntity
{
public:
	Via(Transform transform, Model* model_rail, GLuint shader_id, float speed);
	void update(float delta_time);
	void stop(float delta);

private:
	int n_rails;
	float longitud_rail;
	float speed;
};
