#pragma once
#include "Transform2D.h"
#include "../graphics/Transform.h"
#include "../src/game/graphics/Mesh.h"

class UIElement
{
public:
	UIElement(Transform transform, Texture texture);
	UIElement(Transform transform);


	void disable()
	{
		enabled = false;
	}

	void enable()
	{
		enabled = true;
	}

	Transform my_transform;
	Mesh* my_mesh;
	bool enabled = true;

	std::vector<UIElement*> my_children;

	virtual void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG, Shader& shader);
};
