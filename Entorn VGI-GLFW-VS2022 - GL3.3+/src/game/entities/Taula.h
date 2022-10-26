#pragma once
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"


class Taula
{
public:
	Taula(Transform transform, Mesh* mesh, GLuint shader_program_id);

	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG);
private:

	Transform my_transform;
	Mesh* my_mesh;
	GLuint my_shader_program_id;

	void mostrarPlataforma(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id);
	void mostrarPota(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id);
};
