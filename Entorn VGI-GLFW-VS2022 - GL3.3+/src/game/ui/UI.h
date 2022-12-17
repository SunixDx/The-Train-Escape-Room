#pragma once
#include <vector>

#include "UIElement.h"

class UI
{
public:
	static UI instance;

	void mostrar(Shader& shader)
	{
		mat4 id(1.0f);
		for (UIElement* child : elements)
			child->mostrar(id, id, shader);
	};

	std::vector<UIElement*> elements;
};