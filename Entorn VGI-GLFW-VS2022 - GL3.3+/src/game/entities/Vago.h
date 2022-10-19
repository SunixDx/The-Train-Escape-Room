#include "../src/stdafx.h"
#include "Taula.h"
#include "Seient.h"


class Vago
{
public:
	Vago(glm::vec3 position, GLuint shader_program_id);

	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG);
private:

	glm::vec3 my_position;
	GLuint my_shader_program_id;

	std::vector<Taula> my_taules;
	std::vector<Seient> my_seients;
};
