#include "Vago.h"

void mostrarPared(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id, glm::vec3 displacement)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	ModelMatrix = glm::translate(MatriuTG, displacement);
	ModelMatrix = glm::scale(MatriuTG, vec3(20.0f, 1.0f, 3.0f));
	

	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);	//draw_TriVAO_Object(GLUT_CUBE);  //glutSolidCube(1.0);
}

void Vago::mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	mostrarPared(MatriuVista, MatriuTG, my_shader_program_id, glm::vec3(0.0f, 0.0f, 0.0f));

	ModelMatrix = glm::scale(MatriuTG, vec3(5.0f, 5.0f, 5.0f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(my_shader_program_id, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(my_shader_program_id, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);	//draw_TriVAO_Object(GLUT_CUBE);  //glutSolidCube(1.0);
}
