#include "Level.h"

Level Level::CURRENT_LEVEL;

void Level::buildFirstLevel(GLuint sh_programID)
{
	Transform tr = Transform();
	tr.position = vec3(0.0f, 0.0f, 1.5f);

	Vago* vago = new Vago(tr, Mesh::BASIC_CUBE_MESH, sh_programID);

	int xValorTaula = 12.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorTaula -= 3;
		vago->afegirTaula(new Taula(Transform(vec3(xValorTaula, 1.0f, -0.7f), quat(0.0f, 0.0f, 0.0f, 0.0f), vec3(1.0f)), Mesh::BASIC_CUBE_MESH, sh_programID));
	}

	xValorTaula = 12.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorTaula -= 3;
		vago->afegirTaula(new Taula(Transform(vec3(xValorTaula, -1.0f, -0.7f), quat(0.0f, 0.0f, 0.0f, 0.0f), vec3(1.0f)), Mesh::BASIC_CUBE_MESH, sh_programID));
	}

	quat mirar_endevant = quat(0.0f, 0.0f, 0.0f, 0.0f);
	quat mirar_enrere = quat(glm::cos(glm::pi<float>() / 2), glm::sin(glm::pi<float>() / 2) * 0.0f, glm::sin(glm::pi<float>() / 2) * 0.0f, glm::sin(glm::pi<float>() / 2) * 1.0f);

	int xValorSeientEndavant = 13.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndavant -= 3;
		vago->afegirSeient(Seient(Transform(vec3(xValorSeientEndavant, 1.0f, -1.2f), mirar_endevant, vec3(1.0f)), Mesh::BASIC_CUBE_MESH, sh_programID));
	}

	xValorSeientEndavant = 13.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndavant -= 3;
		vago->afegirSeient(Seient(Transform(vec3(xValorSeientEndavant, -1.0f, -1.2f), mirar_endevant, vec3(1.0f)), Mesh::BASIC_CUBE_MESH, sh_programID));
	}

	int xValorSeientEndarrere = 11.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndarrere -= 3;
		vago->afegirSeient(Seient(Transform(vec3(xValorSeientEndarrere, 1.0f, -1.2f), mirar_enrere, vec3(1.0f)), Mesh::BASIC_CUBE_MESH, sh_programID));
	}

	xValorSeientEndarrere = 11.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndarrere -= 3;
		vago->afegirSeient(Seient(Transform(vec3(xValorSeientEndarrere, -1.0f, -1.2f), mirar_enrere, vec3(1.0f)), Mesh::BASIC_CUBE_MESH, sh_programID));
	}

	Level::CURRENT_LEVEL.my_vago = vago;
}
