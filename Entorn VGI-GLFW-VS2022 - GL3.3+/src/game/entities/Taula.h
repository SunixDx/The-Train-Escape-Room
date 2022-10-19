#include "../src/stdafx.h"


class Taula
{
public:
	Taula(glm::vec3 position, GLuint shader_program_id) : my_position(position), my_shader_program_id(shader_program_id) {};

	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG);
private:

	glm::vec3 my_position;
	GLuint my_shader_program_id;
};
