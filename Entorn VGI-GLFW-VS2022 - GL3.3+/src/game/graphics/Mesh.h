#pragma once

#include <vector>
#include "Vertex.h"
#include "Texture.h"

#include "../src/shader.h"
#include "../graphics/Transform.h"


class Mesh
{
public:
	// Mesh data
	std::vector<Vertex> vertices; // Vector amb atributs als v�rtexs de la malla.
	std::vector<unsigned int> indices; // Vector �ndexs a v�rtexs de cares de la malla per a objecte EBO.
	std::vector<Texture> textures; // vector d�atributs de textures de la malla.
	// Functions:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures): vertices(vertices), indices(indices), textures(textures) { };
	void Draw(mat4 MatriuVista, Transform transform, Shader shader);
	private:
		// Render data:
		unsigned int my_VAO, my_VBO, my_EBO;
		// Functions:
		void setupMesh();
};


class BakedMesh
{
public:
	// Mesh data
	std::vector<Vertex> vertices; // Vector amb atributs als v�rtexs de la malla.
	std::vector<unsigned int> indices; // Vector �ndexs a v�rtexs de cares de la malla per a objecte EBO.
	std::vector<Texture> textures; // vector d�atributs de textures de la malla.
	// Functions:
	BakedMesh(unsigned int VAO, unsigned int VBO, unsigned int EBO) : my_VAO(VAO), indices(indices), textures(textures) { };
	void Draw(mat4 MatriuVista, Transform transform, Shader shader);
private:
	// Render data:
	unsigned int my_VAO, my_VBO, my_EBO;
	// Functions:
	void setupMesh();
};
