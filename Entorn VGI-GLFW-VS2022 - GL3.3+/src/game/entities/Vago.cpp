#include "Vago.h"


Vago::Vago(Transform transform, GLuint shader_program_id)
{
	my_transform = transform;
	my_shader_program_id = shader_program_id;

	my_taules = {
		Taula(vec3(9.0f, 1.0f, -0.7f), shader_program_id),
		Taula(vec3(6.0f, 1.0f, -0.7f), shader_program_id),
		Taula(vec3(3.0f, 1.0f, -0.7f), shader_program_id),
		Taula(vec3(0.0f, 1.0f, -0.7f), shader_program_id),
		Taula(vec3(-3.0f, 1.0f, -0.7f), shader_program_id),
		Taula(vec3(-6.0f, 1.0f, -0.7f), shader_program_id),
		Taula(vec3(-9.0f, 1.0f, -0.7f), shader_program_id),

		Taula(vec3(9.0f, -1.0f, -0.7f), shader_program_id),
		Taula(vec3(6.0f, -1.0f, -0.7f), shader_program_id),
		Taula(vec3(3.0f, -1.0f, -0.7f), shader_program_id),
		Taula(vec3(0.0f, -1.0f, -0.7f), shader_program_id),
		Taula(vec3(-3.0f, -1.0f, -0.7f), shader_program_id),
		Taula(vec3(-6.0f, -1.0f, -0.7f), shader_program_id),
		Taula(vec3(-9.0f, -1.0f, -0.7f), shader_program_id),
	};

	my_seients = {
		Seient(vec3(10.0f, 1.0f, -1.2f), shader_program_id),
		Seient(vec3(8.0f, 1.0f, -1.2f), shader_program_id),

		Seient(vec3(7.0f, 1.0f, -1.2f), shader_program_id),
		Seient(vec3(5.0f, 1.0f, -1.2f), shader_program_id),

		Seient(vec3(4.0f, 1.0f, -1.2f), shader_program_id),
		Seient(vec3(2.0f, 1.0f, -1.2f), shader_program_id),

		Seient(vec3(1.0f, 1.0f, -1.2f), shader_program_id),
		Seient(vec3(-1.0f, 1.0f, -1.2f), shader_program_id),

		Seient(vec3(-2.0f, 1.0f, -1.2f), shader_program_id),
		Seient(vec3(-4.0f, 1.0f, -1.2f), shader_program_id),

		Seient(vec3(-5.0f, 1.0f, -1.2f), shader_program_id),
		Seient(vec3(-7.0f, 1.0f, -1.2f), shader_program_id),

		Seient(vec3(-8.0f, 1.0f, -1.2f), shader_program_id),
		Seient(vec3(-10.0f, 1.0f, -1.2f), shader_program_id),


		Seient(vec3(10.0f, -1.0f, -1.2f), shader_program_id),
		Seient(vec3(8.0f, -1.0f, -1.2f), shader_program_id),

		Seient(vec3(7.0f, -1.0f, -1.2f), shader_program_id),
		Seient(vec3(5.0f, -1.0f, -1.2f), shader_program_id),

		Seient(vec3(4.0f, -1.0f, -1.2f), shader_program_id),
		Seient(vec3(2.0f, -1.0f, -1.2f), shader_program_id),

		Seient(vec3(1.0f, -1.0f, -1.2f), shader_program_id),
		Seient(vec3(-1.0f, -1.0f, -1.2f), shader_program_id),

		Seient(vec3(-2.0f, -1.0f, -1.2f), shader_program_id),
		Seient(vec3(-4.0f, -1.0f, -1.2f), shader_program_id),

		Seient(vec3(-5.0f, -1.0f, -1.2f), shader_program_id),
		Seient(vec3(-7.0f, -1.0f, -1.2f), shader_program_id),

		Seient(vec3(-8.0f, -1.0f, -1.2f), shader_program_id),
		Seient(vec3(-10.0f, -1.0f, -1.2f), shader_program_id),
	};
}

void mostrarPared(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id, glm::vec3 displacement)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	ModelMatrix = glm::translate(MatriuTG, displacement);
	ModelMatrix = glm::scale(ModelMatrix, vec3(20.0f, 0.1f, 3.0f));

	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);	//draw_TriVAO_Object(GLUT_CUBE);  //glutSolidCube(1.0);
}

void mostrarTerra(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 0.0f, -1.5f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(20.0f, 3.0f, 0.1f));

	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);	//draw_TriVAO_Object(GLUT_CUBE);  //glutSolidCube(1.0);
}

void mostrarSostre(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 0.0f, 1.5f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(20.0f, 3.f, 0.1f));

	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);	//draw_TriVAO_Object(GLUT_CUBE);  //glutSolidCube(1.0);
}

void Vago::mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
	MatriuTG = glm::translate(MatriuTG, my_transform.position);

	mat4 rotation = glm::toMat4(my_transform.orientation);
	MatriuTG = rotation * MatriuTG;
	MatriuTG = glm::scale(MatriuTG, my_transform.scale);

	glm::mat4 matriu_transformacions_vago = glm::translate(MatriuTG, my_transform.position);

	mostrarPared(MatriuVista, matriu_transformacions_vago, my_shader_program_id, glm::vec3(0.0f, 1.5f, 0.0f));
	mostrarPared(MatriuVista, matriu_transformacions_vago, my_shader_program_id, glm::vec3(0.0f, -1.5f, 0.0f));

	mostrarTerra(MatriuVista, matriu_transformacions_vago, my_shader_program_id);
	mostrarSostre(MatriuVista, matriu_transformacions_vago, my_shader_program_id);

	for (Taula& taula : my_taules)
		taula.mostrar(MatriuVista, matriu_transformacions_vago);

	for (Seient& seient : my_seients)
		seient.mostrar(MatriuVista, matriu_transformacions_vago);
}
