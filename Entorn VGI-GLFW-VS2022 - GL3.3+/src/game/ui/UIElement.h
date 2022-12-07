#pragma once
#include "Transform2D.h"
#include "../graphics/Transform.h"
#include "../src/game/graphics/Mesh.h"

class UIElement
{
public:
	UIElement(Transform transform, Texture texture);
	UIElement(Transform transform);


	Transform my_transform;
	Mesh* my_mesh;

	std::vector<UIElement*> my_children;

	virtual void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG, Shader& shader);
};
