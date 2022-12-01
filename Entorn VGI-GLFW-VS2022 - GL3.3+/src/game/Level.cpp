#include "Level.h"
#include "../src/game/graphics/Model.h"

Level Level::CURRENT_LEVEL;

void Level::buildFirstLevel(GLuint sh_programID)
{
	Transform tr = Transform();
	tr.position() = vec3(0.0f, 0.0f, Vago::Z_OFFSET); //posicionamos objeto

	Model* model_vago = new Model({ *Mesh::BASIC_CUBE_MESH });

	Vago* vago = new Vago(tr, model_vago, sh_programID);

	Model* model_taula = new Model({ *Mesh::BASIC_CUBE_MESH_BROWN });
	
	float xValorTaula = -110.98f;

	for (int i = 0; i < 1; i++)
	{
		if (i == 2)
		{
			xValorTaula += 4.53f;
			//tercera mesa ha de llegar a 5,69
		}
		else if (i > 0)
		{
			xValorTaula += 2.06f;

		}
		vago->addChild(new Taula(Transform(vec3(xValorTaula, 1.2f, -0.7f), quat(1.0f, 0.0f, 0.0f, 0.0f), vec3(1.0f)), model_taula, sh_programID));
	}

	xValorTaula = -110.98f;

	for (int i = 0; i < 1; i++)
	{
		if (i == 2)
		{
			xValorTaula += 4.53f;
		}
		else if (i > 0)
		{
			xValorTaula += 2.06f;

		}
		vago->addChild(new Taula(Transform(vec3(xValorTaula, -1.2f, -0.7f), quat(1.0f, 0.0f, 0.0f, 0.0f), vec3(1.0f)), model_taula, sh_programID));
	}
	


	Model* model_seient = new Model({ *Mesh::BASIC_CUBE_MESH_SOFT_BROWN });

	quat mirar_endevant = quat(1.0f, 0.0f, 0.0f, 0.0f);
	quat mirar_enrere = quat(glm::cos(glm::pi<float>() / 2), glm::sin(glm::pi<float>() / 2) * 0.0f, glm::sin(glm::pi<float>() / 2) * 0.0f, glm::sin(glm::pi<float>() / 2) * 1.0f);

	float xValorSeientEndavant = -0.31f;

	for (int i = 0; i < 4; i++)
	{
		if (i == 2)
		{
			xValorSeientEndavant += 4.58f;
			//6,34 - i=3
		}
		else if (i > 0)
		{
			xValorSeientEndavant += 2.02f;
			//1,69
		}
		vago->addChild(new Seient(Transform(vec3(xValorSeientEndavant, 1.2f, -1.2f), mirar_endevant, vec3(1.0f)), nullptr, sh_programID));
	}

	xValorSeientEndavant = -0.31f;

	for (int i = 0; i < 4; i++)
	{
		if (i == 2)
		{
			xValorSeientEndavant += 4.58f;
		}
		else if (i > 0)
		{
			xValorSeientEndavant += 2.02f;

		}
		vago->addChild(new Seient(Transform(vec3(xValorSeientEndavant, -1.2f, -1.2f), mirar_endevant, vec3(1.0f)), nullptr, sh_programID));
	}

	float xValorSeientEndarrere = -1.63f;

	
	for (int i = 0; i < 4; i++)
	{
		if (i == 2)
		{
			xValorSeientEndarrere += 4.55f;
			//5,04 - i=3
		}
		else if (i > 0)
		{
			xValorSeientEndarrere += 2.02f;
			//0.39

		}
		vago->addChild(new Seient(Transform(vec3(xValorSeientEndarrere, 1.2f, -1.2f), mirar_enrere, vec3(1.0f)), nullptr, sh_programID));
	}

	xValorSeientEndarrere = -1.63f;

	for (int i = 0; i < 4; i++)
	{
		if (i == 2)
		{
			xValorSeientEndarrere += 4.55f;
		}
		else if (i > 0)
		{
			xValorSeientEndarrere += 2.02f;

		}
		vago->addChild(new Seient(Transform(vec3(xValorSeientEndarrere, -1.2f, -1.2f), mirar_enrere, vec3(1.0f)), nullptr, sh_programID));
	}
	

	Level::CURRENT_LEVEL.my_vago = vago;

	float c = glm::cos(glm::pi<float>() / 4);
	float s = glm::sin(glm::pi<float>() / 4);

	
	Transform trLuisa = Transform();
	trLuisa.position() = vec3(0.1f, 2.2f, 1.0f);
	trLuisa.scale() = vec3(0.04f);
	trLuisa.orientation() = quat(c, s * 1.0f, s * 0.0f, s * 0.0f);
	Cucaracha* luisa = new Cucaracha(trLuisa, new Model("./textures/locker/padlock.obj"), sh_programID);
	Level::CURRENT_LEVEL.cucaracha = luisa;

	//el vagon
	//Transform trRail = Transform();
	//trRail.position() = vec3(0.0f, 0.0f, -2.35f);
	//trRail.scale() = vec3(0.020f);

	//trRail.rotate(glm::pi<float>()/2, vec3(1.0f, 0.0f, 0.0f));
	//Rail* railes = new Rail(trRail, new Model("./textures/vagon/scene.gltf"), sh_programID);

	//tren cartoon
	Transform trRail = Transform();
	trRail.position() = vec3(0.0f, 0.0f, -0.1f);
	trRail.scale() = vec3(1.0f);

	trRail.rotate(glm::pi<float>()/2, vec3(1.0f, 0.0f, 0.0f));

	Rail* railes = new Rail(trRail, new Model("./textures/tren_final/scene.gltf"), sh_programID);
	Level::CURRENT_LEVEL.rail = railes;

	Transform trMaletaTapa = Transform();
	trMaletaTapa.position() = vec3(3.5f, 1.0f, 0);
	trMaletaTapa.translate(vec3(0.7f, 0.2f, 0.1f));
	trMaletaTapa.scale(vec3(0.02f));

	GameEntity* maletaTapa = new GameEntity(trMaletaTapa, new Model("./textures/baul_tapa/untitled.obj"), sh_programID);

	Transform trMaleta = Transform();
	trMaleta.position() = vec3(3.5f, 1.0f, 0);
	trMaleta.translate(vec3(0.7f, 0.2f, 0.1f));
	trMaleta.scale(vec3(0.02f));

	Maleta* maleta = new Maleta(trMaleta, new Model("./textures/baul_cuerpo/untitled.obj"), sh_programID, maletaTapa);

	Transform trLibro1 = Transform();
	trLibro1.translate(vec3(0.5, -1.5f, 0.5f));
	trLibro1.scale(vec3(0.2f));
	trLibro1.rotate(PI / -12, vec3(1.0f,0.0f,0.0f));

	Model* llibre_tancat = new Model("./textures/Book/ChurchBookClosedV2/ChurchBookClosedV2-DAE/ChurchBookClosedV2.dae");
	Model* llibre_obert = new Model("./textures/libro1/ChurchBookOpenV2/ChurchBookOpenV2-OBJ/libro_abierto.obj");
	Libro1* libro1 = new Libro1(trLibro1, llibre_tancat, llibre_obert, sh_programID);

	Transform trCrypt = Transform();
	trCrypt.translate(vec3(0.9f, -2.05f, 0.7f));
	trCrypt.scale(vec3(0.2f));
	trCrypt.rotate((PI / -12) * 6, vec3(0.0f, 1.0f, 0.0f));

	Crypt* crypt = new Crypt(trCrypt, new Model("./textures/crypt/crypt.obj"), sh_programID);

	Transform trPanel = Transform();
	trPanel.translate(vec3(0.1f, -2.05f, 1.2f));
	trPanel.scale(vec3(0.02f));

	Panel* panel = new Panel(trPanel, new Model("./textures/panel/calculator.max"), sh_programID);
	
	//slenderman
	Transform trPadlock = Transform();
	trPadlock.position() = vec3(7.0f, 0.0f, -0.1f);
	trPadlock.scale() = vec3(0.5f);

	trPadlock.rotate(-(glm::pi<float>() / 2), vec3(1.0f, 0.0f, 0.0f));

	Rail* padlock = new Rail(trPadlock, new Model("./textures/slenderman/scene.gltf"), sh_programID);
	padlock->my_enabled = false;

	Level::CURRENT_LEVEL.padlock = padlock;

	Level::CURRENT_LEVEL.my_vago = vago;
	Level::CURRENT_LEVEL.maleta = maleta;
	Level::CURRENT_LEVEL.maletaTapa = maletaTapa;
	Level::CURRENT_LEVEL.libro1 = libro1;
	Level::CURRENT_LEVEL.crypt = crypt;
	Level::CURRENT_LEVEL.panel = panel;
	Level::CURRENT_LEVEL.my_entity_under_cursor = nullptr;
}

void Level::MaybeSpawnSlender()
{
	/* initialize random seed: */
	srand(time(NULL));

	/* generate random number between 1 and 10: */
	int iSecret = rand() % 10 + 1;

	std::cout << "isecret = " << iSecret << std::endl;
	iSecret = 5;
	if (iSecret == 5)
	{
		// Activar spooky lighting
		*llumAmbient = false;
		*iFixe = true;

		// Reproduir audio
		Audio::AUDIO_FUNCTIONS.play2D("./media/spooky_sound.wav", false, false);

		// Mostrar slenderman
		padlock->my_enabled = true;
	}
}

void Level::despawnSlender()
{
	// return to normal lighting
	*llumAmbient = true;
	*iFixe = false;

	padlock->my_enabled = false;
}



