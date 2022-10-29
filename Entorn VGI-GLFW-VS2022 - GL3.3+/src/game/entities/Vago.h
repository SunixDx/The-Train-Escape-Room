#pragma once
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include "Taula.h"
#include "Seient.h"


class Vago
{
public:
	Vago(Transform transform, Mesh* mesh, GLuint shader_id);
	~Vago() {
		for (Taula* t : my_taules)
		{
			delete t;
		}
	}

	void afegirTaula(Taula* taula);
	void afegirSeient(Seient seient);
	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG);
private:

	Mesh* my_mesh;
	Transform my_transform;
	GLuint my_shader_id;

	std::vector<Taula*> my_taules;
	std::vector<Seient> my_seients;


	void mostrarPared(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id, glm::vec3 displacement);
	void mostrarTerra(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id);
	void mostrarSostre(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id);
};
