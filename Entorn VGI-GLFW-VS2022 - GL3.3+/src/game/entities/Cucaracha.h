#pragma once
#include "../src/game/graphics/Model.h"

class Cucaracha
{
public:
	Cucaracha(Transform transform, Model* model, GLuint shader_program_id): my_model(model), my_transform(transform), 
		my_shader_program_id(shader_program_id) {}

	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG) {
		my_model->Draw(MatriuVista, MatriuTG, my_transform, my_shader_program_id);
	}

	void interact();

private:

	Transform my_transform;
	Model* my_model;
	GLuint my_shader_program_id;
};

