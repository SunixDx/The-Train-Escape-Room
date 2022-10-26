#include "Taula.h"


Taula::Taula(Transform transform, Mesh* mesh, GLuint shader_id)
{
	my_transform = transform;
	my_mesh = mesh;
	my_shader_program_id = shader_id;
}

void Taula::mostrarPlataforma(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	Transform transform_sostre = Transform(
		vec3(0.0f, 0.0f, 0.0f),
		quat(0.0f, 0.0f, 0.0f, 0.0f),
		vec3(0.8f, 1.0f, 0.02f)
	);

	my_mesh->Draw(MatriuVista, MatriuTG, transform_sostre, shader_program_id);
}

void Taula::mostrarPota(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	Transform transform_sostre = Transform(
		vec3(0.0f, 0.0f, -0.35f),
		quat(0.0f, 0.0f, 0.0f, 0.0f),
		vec3(0.02f, 0.02f, 0.7f)
	);

	my_mesh->Draw(MatriuVista, MatriuTG, transform_sostre, shader_program_id);
}

void Taula::mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
	MatriuTG = my_transform.apply(MatriuTG);

	mostrarPlataforma(MatriuVista, MatriuTG, my_shader_program_id);
	mostrarPota(MatriuVista, MatriuTG, my_shader_program_id);
}