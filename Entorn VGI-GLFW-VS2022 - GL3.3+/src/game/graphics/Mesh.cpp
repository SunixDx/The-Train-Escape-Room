#include "Mesh.h"

Mesh* Mesh::BASIC_CUBE_MESH = nullptr;

void Mesh::Draw(mat4 MatriuVista, mat4 MatriuTG, Transform& transform, GLuint shader_id)
{
	mat4 ModelMatrix(1.0f);
	mat4 NormalMatrix(1.0f);

	ModelMatrix = transform.apply(MatriuTG);

	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shader_id, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader_id, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

	glBindVertexArray(my_VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_EBO);
	//glDrawElements(GL_TRIANGLES, VAOList[k].nVertexs, GL_UNSIGNED_INT, nullptr);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::Draw(Shader &shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate texture unit first
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		shader.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);
	// draw mesh
	glBindVertexArray(my_VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &my_VAO);
	glGenBuffers(1, &my_VBO);
	glGenBuffers(1, &my_EBO);

	glBindVertexArray(my_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, my_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(
		Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(
		Vertex, TexCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(
		Vertex, Color));

	glBindVertexArray(0);
}
