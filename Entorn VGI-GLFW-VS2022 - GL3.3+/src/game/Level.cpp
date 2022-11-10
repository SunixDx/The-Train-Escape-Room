#include "Level.h"
#include "../src/game/graphics/Model.h"

Level Level::CURRENT_LEVEL;

void Level::buildFirstLevel(GLuint sh_programID)
{
	Transform tr = Transform();
	tr.position = vec3(0.0f, 0.0f, Vago::Z_OFFSET);

	Model* model_vago = new Model({ *Mesh::BASIC_CUBE_MESH });

	Vago* vago = new Vago(tr, model_vago, sh_programID);

	Model* model_taula = new Model({ *Mesh::BASIC_CUBE_MESH_BROWN });

	int xValorTaula = 12.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorTaula -= 3;
		vago->addChild(new Taula(Transform(vec3(xValorTaula, 2.3f, -0.7f), quat(0.0f, 0.0f, 0.0f, 0.0f), vec3(1.0f)), model_taula, sh_programID));
	}

	xValorTaula = 12.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorTaula -= 3;
		vago->addChild(new Taula(Transform(vec3(xValorTaula, -2.3f, -0.7f), quat(0.0f, 0.0f, 0.0f, 0.0f), vec3(1.0f)), model_taula, sh_programID));
	}


	Model* model_seient = new Model({ *Mesh::BASIC_CUBE_MESH_SOFT_BROWN });

	quat mirar_endevant = quat(0.0f, 0.0f, 0.0f, 0.0f);
	quat mirar_enrere = quat(glm::cos(glm::pi<float>() / 2), glm::sin(glm::pi<float>() / 2) * 0.0f, glm::sin(glm::pi<float>() / 2) * 0.0f, glm::sin(glm::pi<float>() / 2) * 1.0f);

	int xValorSeientEndavant = 13.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndavant -= 3;
		vago->addChild(new Seient(Transform(vec3(xValorSeientEndavant, 2.3f, -1.2f), mirar_endevant, vec3(1.0f)), model_seient, sh_programID));
	}

	xValorSeientEndavant = 13.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndavant -= 3;
		vago->addChild(new Seient(Transform(vec3(xValorSeientEndavant, -2.3f, -1.2f), mirar_endevant, vec3(1.0f)), model_seient, sh_programID));
	}

	int xValorSeientEndarrere = 11.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndarrere -= 3;
		vago->addChild(new Seient(Transform(vec3(xValorSeientEndarrere, 2.3f, -1.2f), mirar_enrere, vec3(1.0f)), model_seient, sh_programID));
	}

	xValorSeientEndarrere = 11.0f;

	for (int i = 0; i < 7; i++)
	{
		xValorSeientEndarrere -= 3;
		vago->addChild(new Seient(Transform(vec3(xValorSeientEndarrere, -2.3f, -1.2f), mirar_enrere, vec3(1.0f)), model_seient, sh_programID));
	}

	Level::CURRENT_LEVEL.my_vago = vago;

	float c = glm::cos(glm::pi<float>() / 4);
	float s = glm::sin(glm::pi<float>() / 4);


	Transform trLuisa = Transform();
	trLuisa.position = vec3(0.1f, 2.2f, 1.0f);
	trLuisa.scale = vec3(0.04f);
	trLuisa.orientation = quat(c, s * 1.0f, s * 0.0f, s * 0.0f);
	Cucaracha* luisa = new Cucaracha(trLuisa, new Model("./textures/locker/padlock.obj"), sh_programID);
	Level::CURRENT_LEVEL.my_vago = vago;
	Level::CURRENT_LEVEL.cucaracha = luisa;


	Level::CURRENT_LEVEL.my_entity_under_cursor = nullptr;
}
