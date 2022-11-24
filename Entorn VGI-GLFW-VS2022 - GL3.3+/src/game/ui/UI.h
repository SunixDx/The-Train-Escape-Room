#pragma once
#include <vector>

#include "UIElement.h"

class UI
{
public:
	void mostrar() {
		mat4 id(1.0f);

		for (UIElement* child : elements)
			child->mostrar(id, id);
	};

	std::vector<UIElement*> elements;
};