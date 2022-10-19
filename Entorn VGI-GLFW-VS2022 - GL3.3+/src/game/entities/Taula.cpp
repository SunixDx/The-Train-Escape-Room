#include "Taula.h"


void mostrarPlataforma(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id, glm::vec3 displacement)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	ModelMatrix = glm::translate(MatriuTG, displacement);
	ModelMatrix = glm::scale(ModelMatrix, vec3(0.8f, 1.0f, 0.02f));

	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);	//draw_TriVAO_Object(GLUT_CUBE);  //glutSolidCube(1.0);
}

void mostrarPota(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id, glm::vec3 displacement)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 0.0f, -0.35f));
	ModelMatrix = glm::translate(ModelMatrix, displacement);
	ModelMatrix = glm::scale(ModelMatrix, vec3(0.02f, 0.02f, 0.7f));

	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);	//draw_TriVAO_Object(GLUT_CUBE);  //glutSolidCube(1.0);
}

void Taula::mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
	mostrarPlataforma(MatriuVista, MatriuTG, my_shader_program_id, my_position);
	mostrarPota(MatriuVista, MatriuTG, my_shader_program_id, my_position);
}