#include "Vago.h"

float Vago::Z_OFFSET = 1.5f;

Vago::Vago(Transform transform, Model* model, GLuint shader_id): GameEntity(transform, nullptr, shader_id)
{
	/*
	my_children.push_back(new GameEntity(Transform(
		vec3(0.0f, 3.0f, 0.0f),
		quat(1.0f, 0.0f, 0.0f, 0.0f),
		vec3(22.0f, 0.1f, 3.0f)
	), model, my_shader_id));

	my_children.push_back(new GameEntity(Transform(
		vec3(0.0f, -3.0f, 0.0f),
		quat(1.0f, 0.0f, 0.0f, 0.0f),
		vec3(22.0f, 0.1f, 3.0f)
	), model, my_shader_id));

	my_children.push_back(new GameEntity(Transform(
		vec3(0.0f, 0.0f, -1.5f),
		quat(1.0f, 0.0f, 0.0f, 0.0f),
		vec3(22.0f, 6.0f, 0.1f)
	), model, my_shader_id));

	my_children.push_back(new GameEntity(Transform(
		vec3(0.0f, 0.0f, 1.5f),
		quat(1.0f, 0.0f, 0.0f, 0.0f),
		vec3(22.0f, 6.f, 0.1f)
	), model, my_shader_id));
	*/
}
