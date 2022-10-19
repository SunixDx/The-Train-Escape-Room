#include "Seient.h"

void mostrarBanc(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id, glm::vec3 displacement)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	ModelMatrix = glm::translate(MatriuTG, displacement);
	ModelMatrix = glm::scale(ModelMatrix, vec3(0.5f, 1.0f, 0.5f));

	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);	//draw_TriVAO_Object(GLUT_CUBE);  //glutSolidCube(1.0);
}

void mostrarRespatller(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id, glm::vec3 displacement)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	ModelMatrix = glm::translate(MatriuTG, vec3(0.25f, 0.0f, 0.5f));
	ModelMatrix = glm::translate(ModelMatrix, displacement);
	ModelMatrix = glm::scale(ModelMatrix, vec3(0.02f, 1.0f, 0.5f));

	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);	//draw_TriVAO_Object(GLUT_CUBE);  //glutSolidCube(1.0);
}

void Seient::mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
	mostrarBanc(MatriuVista, MatriuTG, my_shader_program_id, my_position);
	mostrarRespatller(MatriuVista, MatriuTG, my_shader_program_id, my_position);
}