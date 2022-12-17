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
	
	//cucaracha
	Transform trLuisa = Transform();
	trLuisa.position() = vec3(0.1f, 2.2f, 1.0f);
	trLuisa.scale() = vec3(0.04f);
	trLuisa.orientation() = quat(c, s * 1.0f, s * 0.0f, s * 0.0f);
	Cucaracha* luisa = new Cucaracha(trLuisa, new Model("./textures/locker/padlock.obj"), sh_programID);
	Level::CURRENT_LEVEL.cucaracha = luisa;

	//tren cartoon
	Transform trRail = Transform();
	trRail.position() = vec3(0.0f, 0.0f, -0.1f);
	trRail.scale() = vec3(1.0f);

	trRail.rotate(glm::pi<float>()/2, vec3(1.0f, 0.0f, 0.0f));

	Rail* railes = new Rail(trRail, new Model("./textures/tren_final/scene.gltf"), sh_programID);
	Level::CURRENT_LEVEL.rail = railes;

	//maleta
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

	//llibre
	Transform trLibro1 = Transform();
	trLibro1.translate(vec3(0.5, -1.5f, 0.5f));
	trLibro1.scale(vec3(0.2f));
	trLibro1.rotate(PI / -12, vec3(1.0f,0.0f,0.0f));

	Model* llibre_tancat = new Model("./textures/Book/ChurchBookClosedV2/ChurchBookClosedV2-DAE/ChurchBookClosedV2.dae");
	Model* llibre_obert = new Model("./textures/libro1/ChurchBookOpenV2/ChurchBookOpenV2-OBJ/libro_abierto.obj");
	Libro1* libro1 = new Libro1(trLibro1, llibre_tancat, llibre_obert, sh_programID);

	//text encriptat
	Transform trCrypt = Transform();
	trCrypt.translate(vec3(1.05f, -1.98f, 0.65f));
	trCrypt.scale(vec3(0.2f));
	trCrypt.rotate((PI / -6) * 9, vec3(0.0f, 0.0f, 1.0f));

	Crypt* crypt = new Crypt(trCrypt, new Model("./textures/placa_codi/placa_codi.obj"), sh_programID);

	//panel
	Transform trPanel = Transform();
	trPanel.translate(vec3(8.75f, -0.8f, 1.9f));
	trPanel.rotate((PI / -6) * 9, vec3(0.0f, 0.0f, 1.0f));
	trPanel.scale(vec3(0.1f));

	Panel* panel = new Panel(trPanel, new Model("./textures/panel/panel_propio.obj"), sh_programID);
	
	//slenderman
	Transform trPadlock = Transform();
	trPadlock.position() = vec3(7.0f, 0.0f, -0.1f);
	trPadlock.scale() = vec3(0.5f);

	trPadlock.rotate(-(glm::pi<float>() / 2), vec3(1.0f, 0.0f, 0.0f));

	Rail* padlock = new Rail(trPadlock, new Model("./textures/slenderman/scene.gltf"), sh_programID);
	padlock->my_enabled = false;

	//exterior tren
	Transform trExterior = Transform();
	trExterior.position() = vec3(0.0f, 0.0f, 50.0f);
	trExterior.scale() = vec3(0.2f);

	trExterior.rotate(glm::pi<float>()/2, vec3(0.0f, 0.0f, 1.0f));
	trExterior.rotate(glm::pi<float>() /2, vec3(1.0f, 0.0f, 0.0f));

	Rail* exterior = new Rail(trExterior, new Model("./textures/tren_exterior/scene.gltf"), sh_programID);

	//megafono
	Transform trMegafono = Transform();
	trMegafono.position() = vec3(9.08f, 0.0f, 2.5f);
	trMegafono.scale() = vec3(1.6f);

	trMegafono.rotate(glm::pi<float>() / 2, vec3(0.0f, 0.0f, 1.0f));
	trMegafono.rotate((glm::pi<float>() / 5), vec3(0.0f, -1.0f, 0.0f));
	Rail* megafono = new Rail(trMegafono, new Model("./textures/megafono/scene.gltf"), sh_programID);

	//rellotge 1
	Transform trClock = Transform();
	trClock.translate(vec3(-1.5, 1.45f, 0.5f));
	trClock.scale(vec3(0.15f));
	trClock.rotate((PI / 6) * 3, vec3(0.0f, 0.0f, 1.0f));
	trClock.rotate((PI / -12) * 3, vec3(1.0f, 0.0f, 0.0f));
	GameEntity* clock = new GameEntity(trClock, new Model("./textures/clock/clock1.obj"), sh_programID);

	//rellotge 2
	Transform trClock2 = Transform();
	trClock2.translate(vec3(4.7f, -1.9f, 1.5f));
	trClock2.scale(vec3(0.2f));
	trClock2.rotate((PI / -6), vec3(.0f, .0f, 0.0f));
	GameEntity* clock2 = new GameEntity(trClock2, new Model("./textures/clock/clock2.obj"), sh_programID);

	//rellotge 3
	Transform trClock3 = Transform();
	trClock3.translate(vec3(7.6, -1.6f, 0.0f));
	trClock3.scale(vec3(0.2f));
	trClock3.rotate((PI / -6), vec3(1.0f, 0.0f, 0.0f));
	GameEntity* clock3 = new GameEntity(trClock3, new Model("./textures/clock/clock3.obj"), sh_programID);

	//biblia
	Transform trBiblia = Transform();
	trBiblia.translate(vec3(7.6, -1.6f, 0.0f));
	trBiblia.scale(vec3(0.2f));
	trBiblia.rotate((PI / -6), vec3(1.0f, 0.0f, 0.0f));
	GameEntity* biblia = new GameEntity(trBiblia, new Model("./textures/biblia/biblia.obj"), sh_programID);

	// palanca
	Transform trLever = Transform();
	Lever* lever = new Lever(trLever, new Model("./textures/lever/lever.obj"), sh_programID);

	Level::CURRENT_LEVEL.padlock = padlock;
	Level::CURRENT_LEVEL.my_vago = vago;
	Level::CURRENT_LEVEL.maleta = maleta;
	Level::CURRENT_LEVEL.maletaTapa = maletaTapa;
	Level::CURRENT_LEVEL.libro1 = libro1;
	Level::CURRENT_LEVEL.crypt = crypt;
	Level::CURRENT_LEVEL.panel = panel;
	Level::CURRENT_LEVEL.my_entity_under_cursor = nullptr;
	Level::CURRENT_LEVEL.megaphone = megafono;
	Level::CURRENT_LEVEL.exterior_tren = exterior;
	Level::CURRENT_LEVEL.clock = clock;
	Level::CURRENT_LEVEL.clock2 = clock2;
	Level::CURRENT_LEVEL.clock3 = clock3;
	Level::CURRENT_LEVEL.biblia = biblia;
	Level::CURRENT_LEVEL.lever = lever;
}

void Level::MaybeSpawnSlender()
{
	// Activar spooky lighting
	*llumAmbient = false;
	*iFixe = true;
	*flicker = true;

	// Reproduir audio
	irrklang::vec3df position(padlock->my_transform.position().x, padlock->my_transform.position().y, padlock->my_transform.position().z);
	irrklang::ISound* snd = Audio::AUDIO_FUNCTIONS.play3D("./media/spooky_sound.wav", position, false, true);
	snd->setMinDistance(1.5f);
	Audio::AUDIO_FUNCTIONS.setVolume(snd, 0.5f);
	Audio::AUDIO_FUNCTIONS.pause_or_unpause(snd);

	irrklang::ISound* snd2 = Audio::AUDIO_FUNCTIONS.play3D("./media/slender-breathing.wav", position, false, true);
	snd->setMinDistance(1.5f);
	Audio::AUDIO_FUNCTIONS.setVolume(snd2, 1.0f);
	Audio::AUDIO_FUNCTIONS.pause_or_unpause(snd2);

	irrklang::ISound* snd3 = Audio::AUDIO_FUNCTIONS.play2D("./media/flickering-lights.mp3", false, true);
	Audio::AUDIO_FUNCTIONS.setVolume(snd3, 0.25f);
	Audio::AUDIO_FUNCTIONS.pause_or_unpause(snd3);

	sonsSlenderman.push_back(snd);
	sonsSlenderman.push_back(snd2);

	// Mostrar slenderman
	padlock->my_enabled = true;
}

void Level::despawnSlender()
{
	// return to normal lighting
	*llumAmbient = true;
	*iFixe = false;
	*flicker = false;

	for (irrklang::ISound* snd : sonsSlenderman)
	{
		snd->setIsPaused(true);
	}

	padlock->my_enabled = false;
}



