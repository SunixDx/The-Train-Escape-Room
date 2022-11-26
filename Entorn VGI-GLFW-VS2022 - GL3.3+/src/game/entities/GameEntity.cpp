#include "GameEntity.h"

void GameEntity::mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
	if (!my_enabled)
		return;

	if (my_model != nullptr)
		my_model->Draw(MatriuVista, MatriuTG, my_transform, my_shader_id);

	MatriuTG = my_transform.apply(MatriuTG);

	for (GameEntity* child : my_children)
		child->mostrar(MatriuVista, MatriuTG);
}

void GameEntity::addChild(GameEntity* child)
{
	my_children.push_back(child);
}
