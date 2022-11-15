#include "Transform2D.h"
#include "../src/game/graphics/Texture.h"

class UIElement
{
public:
	Transform2D my_transform;
	Texture my_texture;

	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG);
};
