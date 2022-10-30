#include "../src/stdafx.h"
#include "../src/game/graphics/Mesh.h"

class Crosshair
{
public:
	Crosshair(Mesh* mesh, GLuint shader_id) : my_mesh(mesh), my_shader_id(shader_id) {};
	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG);
private:
	Mesh* my_mesh;
	GLuint my_shader_id;
};