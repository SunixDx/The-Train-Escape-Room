#include "Transform.h"

mat4 Transform::apply(mat4 matriu_transformacions)
{
	matriu_transformacions = glm::translate(matriu_transformacions, my_position);
	mat4 rotation = glm::toMat4(my_orientation);
	matriu_transformacions = matriu_transformacions * rotation;

	matriu_transformacions = glm::scale(matriu_transformacions, my_scale);

	return matriu_transformacions;
}

void Transform::translate(glm::vec3 translation)
{
	my_position = my_position + translation;
}

void Transform::reset_orientation()
{
	my_orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

void Transform::rotate(glm::quat rotation)
{
	my_orientation = rotation * my_orientation;
}

void Transform::rotate(float angle, glm::vec3 axis)
{
	float x = axis.x * sin(angle / 2);
	float y = axis.y * sin(angle / 2);
	float z = axis.z * sin(angle / 2);
	float w = cos(angle / 2);
	glm::quat rotation = quat(x, y, z, w);

	rotate(rotation);
}

void Transform::scale(float factor)
{
	my_scale = my_scale * factor;
}

void Transform::scale(glm::vec3 factor)
{
	my_scale.x = my_scale.x * factor.x;
	my_scale.y = my_scale.y * factor.y;
	my_scale.z = my_scale.z * factor.z;
}
