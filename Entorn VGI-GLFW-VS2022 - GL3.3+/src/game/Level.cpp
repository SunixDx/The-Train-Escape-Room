#include "Level.h"
#include "../src/game/graphics/Model.h"

Level Level::CURRENT_LEVEL;

void Level::buildFirstLevel(GLuint sh_programID)
{
	Transform tr = Transform();
	tr.position = vec3(0.0f, 0.0f, Vago::Z_OFFSET); //posicionamos objeto

	Vago* vago = new Vago(tr, Mesh::BASIC_CUBE_MESH, sh_programID);

	int xValorTaula = 12.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorTaula -= 3;
		vago->afegirTaula(new Taula(Transform(vec3(xValorTaula, 2.3f, -0.7f), quat(0.0f, 0.0f, 0.0f, 0.0f), vec3(1.0f)), Mesh::BASIC_CUBE_MESH_BROWN, sh_programID));
	}

	xValorTaula = 12.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorTaula -= 3;
		vago->afegirTaula(new Taula(Transform(vec3(xValorTaula, -2.3f, -0.7f), quat(0.0f, 0.0f, 0.0f, 0.0f), vec3(1.0f)), Mesh::BASIC_CUBE_MESH_BROWN, sh_programID));
	}

	quat mirar_endevant = quat(0.0f, 0.0f, 0.0f, 0.0f);
	quat mirar_enrere = quat(glm::cos(glm::pi<float>() / 2), glm::sin(glm::pi<float>() / 2) * 0.0f, glm::sin(glm::pi<float>() / 2) * 0.0f, glm::sin(glm::pi<float>() / 2) * 1.0f);

	int xValorSeientEndavant = 13.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndavant -= 3;
		vago->afegirSeient(new Seient(Transform(vec3(xValorSeientEndavant, 2.3f, -1.2f), mirar_endevant, vec3(1.0f)), Mesh::BASIC_CUBE_MESH_SOFT_BROWN, sh_programID));
	}

	xValorSeientEndavant = 13.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndavant -= 3;
		vago->afegirSeient(new Seient(Transform(vec3(xValorSeientEndavant, -2.3f, -1.2f), mirar_endevant, vec3(1.0f)), Mesh::BASIC_CUBE_MESH_SOFT_BROWN, sh_programID));
	}

	int xValorSeientEndarrere = 11.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndarrere -= 3;
		vago->afegirSeient(new Seient(Transform(vec3(xValorSeientEndarrere, 2.3f, -1.2f), mirar_enrere, vec3(1.0f)), Mesh::BASIC_CUBE_MESH_SOFT_BROWN, sh_programID));
	}

	xValorSeientEndarrere = 11.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndarrere -= 3;
		vago->afegirSeient(new Seient(Transform(vec3(xValorSeientEndarrere, -2.3f, -1.2f), mirar_enrere, vec3(1.0f)), Mesh::BASIC_CUBE_MESH_SOFT_BROWN, sh_programID));
	}

	Level::CURRENT_LEVEL.my_vago = vago;

	float c = glm::cos(glm::pi<float>() / 4);
	float s = glm::sin(glm::pi<float>() / 4);


	Transform trLuisa = Transform();
	trLuisa.position = vec3(0.1f, 2.2f, 1.0f);
	trLuisa.scale = vec3(0.04f);
	trLuisa.orientation = quat(c, s * 1.0f, s * 0.0f, s * 0.0f);
	Cucaracha* luisa = new Cucaracha(trLuisa, new Model("./textures/locker/padlock.obj"), sh_programID);

	Transform trMaleta = Transform();
	trMaleta.position = vec3(0.7f, 0.2f, 0.4f);
	trMaleta.scale = vec3(0.05f);

	Maleta* maleta = new Maleta(trMaleta, new Model("./textures/maleta/SA_LD_Steel_Case.3ds"), sh_programID);

	Transform trLibro1 = Transform();
	trLibro1.position = vec3(0.05f, 0.2f, 0.8f);
	trLibro1.scale = vec3(0.2f);

	Libro1* libro1 = new Libro1(trLibro1, new Model("./textures/libro1/uploads_files_2794075_book.blend"), sh_programID);

	Level::CURRENT_LEVEL.my_vago = vago;
	Level::CURRENT_LEVEL.cucaracha = luisa;
	Level::CURRENT_LEVEL.maleta = maleta;
	Level::CURRENT_LEVEL.libro1 = libro1;


	Level::CURRENT_LEVEL.my_entity_under_cursor = nullptr;
}
