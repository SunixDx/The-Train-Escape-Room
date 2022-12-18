#pragma once
#include "GameEntity.h"

class Tren_passant : public GameEntity
{
public:
	Tren_passant(Transform transform, Model* model_terreny, GLuint shader_id, float speed);
	void update(float delta_time);

private:
	int n_trens;
	float longitud_tren;
	float speed;
};