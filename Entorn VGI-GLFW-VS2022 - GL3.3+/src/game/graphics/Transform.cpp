#include "Transform.h"

mat4 Transform::apply(mat4 matriu_transformacions)
{
	matriu_transformacions = glm::translate(matriu_transformacions, position);
	matriu_transformacions = glm::scale(matriu_transformacions, scale);
	mat4 rotation = glm::toMat4(orientation);
	matriu_transformacions = matriu_transformacions * rotation;

	return matriu_transformacions;
}
