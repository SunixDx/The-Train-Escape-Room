/*
#include "Mesh.h"

void Mesh::Draw(mat4 MatriuVista, Transform transform, Shader shader)
{
	mat4 ModelMatrix(1.0f);
	mat4 NormalMatrix(1.0f);

	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

	glBindVertexArray(my_VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_EBO);
	//glDrawElements(GL_TRIANGLES, VAOList[k].nVertexs, GL_UNSIGNED_INT, nullptr);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
*/