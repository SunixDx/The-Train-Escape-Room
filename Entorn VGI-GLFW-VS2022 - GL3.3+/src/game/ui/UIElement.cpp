#include "UIElement.h"
#include "../graphics/Model.h"

UIElement::UIElement(Transform transform, Texture texture): my_transform(transform), my_mesh(nullptr)
{

	std::vector<Vertex> plane_vertices = {
		Vertex({-0.5f, -0.5f,  0.0f}, {0.0,  0.0,  1.0}, {0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f, -0.5f,  0.0f}, {0.0,  0.0,  1.0}, {1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f,  0.5f,  0.0f}, {0.0,  0.0,  1.0}, {1.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f,  0.5f,  0.0f}, {0.0,  0.0,  1.0}, {0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
	};

	std::vector<unsigned int> plane_indices = {
		//0, 1, 2, 2, 3, 0,			// v0-v1-v2-v3 (front)
		//2, 1, 0, 0, 3, 2,			// v0-v1-v2-v3 (front)
		0, 2, 1, 0, 3, 2,			// v0-v1-v2-v3 (front)
		//2, 3, 0, 1, 2, 0,			// v0-v1-v2-v3 (front)
	};

	std::vector<Texture> plane_textures = {
		texture,
	};

	my_mesh = new Mesh(plane_vertices, plane_indices, plane_textures);
}

UIElement::UIElement(Transform transform) : my_transform(transform), my_mesh(nullptr)
{
}

void UIElement::mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG, Shader& shader)
{
	if (!enabled)
		return;

	if (my_mesh != nullptr)
		my_mesh->Draw(MatriuVista, MatriuTG, my_transform, shader.getProgramID());

	MatriuTG = my_transform.apply(MatriuTG);

	for (UIElement* child : my_children)
		child->mostrar(MatriuVista, MatriuTG, shader);
}