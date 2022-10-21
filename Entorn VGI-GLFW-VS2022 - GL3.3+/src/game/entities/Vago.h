#pragma once
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "Taula.h"
#include "Seient.h"


class Vago
{
public:
	Vago(Transform transform, GLuint shader_program_id);

	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG);
private:

	Transform my_transform;
	GLuint my_shader_program_id;

	std::vector<Taula> my_taules;
	std::vector<Seient> my_seients;
};
