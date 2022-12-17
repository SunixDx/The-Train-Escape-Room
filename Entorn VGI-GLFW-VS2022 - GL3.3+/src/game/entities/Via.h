#pragma once
#include "GameEntity.h"

class Via : public GameEntity
{
public:
	Via(Transform transform, Model* model_rail, GLuint shader_id);
	void update(float delta_time);

private:
	int n_rails;
	float longitud_rail;
};
