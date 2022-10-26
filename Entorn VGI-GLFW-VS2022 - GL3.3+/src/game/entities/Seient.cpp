#include "Seient.h"

Seient::Seient(Transform transform, Mesh* mesh, GLuint shader_id)
{
	my_transform = transform;
	my_mesh = mesh;
	my_shader_program_id = shader_id;
}

void Seient::mostrarBanc(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	Transform transform_sostre = Transform(
		vec3(0.0f, 0.0f, 0.0f),
		quat(0.0f, 0.0f, 0.0f, 0.0f),
		vec3(0.5f, 1.0f, 0.5f)
	);

	my_mesh->Draw(MatriuVista, MatriuTG, transform_sostre, shader_program_id);
}

void Seient::mostrarRespatller(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	Transform transform_sostre = Transform(
		vec3(0.25f, 0.0f, 0.5f),
		quat(0.0f, 0.0f, 0.0f, 0.0f),
		vec3(0.02f, 1.0f, 0.5f)
	);

	my_mesh->Draw(MatriuVista, MatriuTG, transform_sostre, shader_program_id);
}

void Seient::mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
	MatriuTG = my_transform.apply(MatriuTG);

	mostrarBanc(MatriuVista, MatriuTG, my_shader_program_id);
	mostrarRespatller(MatriuVista, MatriuTG, my_shader_program_id);
}