#include "Vago.h"


Vago::Vago(Transform transform, Mesh* mesh, GLuint shader_id)
{
	my_transform = transform;
	my_mesh = mesh;
	my_shader_id = shader_id;
}

void Vago::afegirTaula(Taula* taula)
{
	my_taules.push_back(taula);
}

void Vago::afegirSeient(Seient seient)
{
	my_seients.push_back(seient);
}

void Vago::mostrarPared(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id, glm::vec3 displacement)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	Transform transform_sostre = Transform(
		displacement,
		quat(0.0f, 0.0f, 0.0f, 0.0f),
		vec3(22.0f, 0.1f, 3.0f)
	);

	my_mesh->Draw(MatriuVista, MatriuTG, transform_sostre, shader_program_id);
}

void Vago::mostrarTerra(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	Transform transform_terra = Transform(
		vec3(0.0f, 0.0f, -1.5f),
		quat(0.0f, 0.0f, 0.0f, 0.0f),
		vec3(22.0f, 3.0f, 0.1f)
	);

	my_mesh->Draw(MatriuVista, MatriuTG, transform_terra, shader_program_id);
}

void Vago::mostrarSostre(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	Transform transform_sostre = Transform(
		vec3(0.0f, 0.0f, 1.5f),
		quat(0.0f, 0.0f, 0.0f, 0.0f),
		vec3(22.0f, 3.f, 0.1f)
	);

	my_mesh->Draw(MatriuVista, MatriuTG, transform_sostre, shader_program_id);
}

void Vago::mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
	MatriuTG = my_transform.apply(MatriuTG);

	mostrarPared(MatriuVista, MatriuTG, my_shader_id, glm::vec3(0.0f, 1.5f, 0.0f));
	mostrarPared(MatriuVista, MatriuTG, my_shader_id, glm::vec3(0.0f, -1.5f, 0.0f));

	mostrarTerra(MatriuVista, MatriuTG, my_shader_id);
	mostrarSostre(MatriuVista, MatriuTG, my_shader_id);

	for (Taula* taula : my_taules)
		taula->mostrar(MatriuVista, MatriuTG);

	for (Seient& seient : my_seients)
		seient.mostrar(MatriuVista, MatriuTG);
}
