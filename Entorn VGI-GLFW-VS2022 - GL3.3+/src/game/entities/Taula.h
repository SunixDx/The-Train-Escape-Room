#include "../src/stdafx.h"
#include "../graphics/Transform.h"


class Taula
{
public:
	Taula(Transform transform, GLuint shader_program_id) : my_transform(transform), my_shader_program_id(shader_program_id) {};

	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG);
private:

	Transform my_transform;
	GLuint my_shader_program_id;
};
