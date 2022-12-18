#include "Level.h"
#include "../src/game/graphics/Model.h"
#include "audio/AudioFunctions.h"
#include "tots_els_rails.cpp"

Level Level::CURRENT_LEVEL;

//----------------------------------------------Railes----------------------------------------------
//en tots_els_rails.cpp
// Funcion para imprimir todos los railes
//-------------------------------------------------------------------------------------------------

Mesh make_panel_mesh(Texture texture)
{
	std::vector<Vertex> plane_vertices = {
	Vertex({-0.5f, -0.5f,  0.0f}, {0.0,  0.0,  1.0}, {0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
	Vertex({0.5f, -0.5f,  0.0f}, {0.0,  0.0,  1.0}, {1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
	Vertex({0.5f,  0.5f,  0.0f}, {0.0,  0.0,  1.0}, {1.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
	Vertex({-0.5f,  0.5f,  0.0f}, {0.0,  0.0,  1.0}, {0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
	};

	std::vector<unsigned int> plane_indices = {
		//0, 1, 2, 2, 3, 0,			// v0-v1-v2-v3 (front)
		//2, 1, 0, 0, 3, 2,			// v0-v1-v2-v3 (front)
		0, 2, 1, 0, 3, 2,			// v0-v1-v2-v3 (front)
		//2, 3, 0, 1, 2, 0,			// v0-v1-v2-v3 (front)
	};

	std::vector<Texture> plane_textures = {
		texture,
	};

	return Mesh(plane_vertices, plane_indices, plane_textures);
}

std::array<Model*, 10> load_panel_digit_models()
{
	std::array<Model*, 10> models;
	for (int i = 0; i < models.size(); i++)
	{
		Texture texture = LoadTexture("./textures/panel", std::to_string(i) + "_display.png", "texture_diffuse");
		std::vector<Mesh> meshes;
		meshes.push_back(make_panel_mesh(texture));
		models[i] = new Model(meshes);
	}

	return models;
}

void Level::exterior_train_offset(GLuint sh_programID, glm::vec3 exterior_offset)
{/*
	//exterior tren
	Transform trExterior = Transform();
	trExterior.position() = vec3(0.0f, 11.814f, -1.2f);
	trExterior.scale() = vec3(0.022f);

	trExterior.rotate(glm::pi<float>() / 2, vec3(1.0f, 0.0f,0.0f));
	//trExterior.rotate(glm::pi<float>() / 2, vec3(1.0f, 0.0f, 0.0f));

	Rail* exterior = new Rail(trExterior, new Model("./textures/tren_exterior/scene.gltf"), sh_programID);
	Level::CURRENT_LEVEL.exterior_tren = exterior;
 */
}


void Level::slender_offset(GLuint sh_programID, glm::vec3 offset_slenderman)
{
	int posicio = 1;
	Transform trPadlock = Transform();
	if (posicio == 1) {
		trPadlock.position() = offset_slenderman;
		trPadlock.scale() = vec3(0.5f);
		trPadlock.rotate((glm::pi<float>() / 2), vec3(1.0f, 0.0f, 0.0f));
	}
	else if (posicio == 2) {
		trPadlock.position() = vec3(-1.0f, 0.0f, -0.1f);
		trPadlock.scale() = vec3(0.5f);
		trPadlock.rotate((glm::pi<float>() / 2), vec3(1.0f, 0.0f, 0.0f));
	}
	else if (posicio == 3) {
		trPadlock.position() = vec3(3.5f, 0.9f, -0.1f);
		trPadlock.scale() = vec3(0.5f);
	}
	else if (posicio == 4) {
		trPadlock.position() = vec3(3.5f, -0.9f, -0.1f);
		trPadlock.scale() = vec3(0.5f);
		trPadlock.rotate((glm::pi<float>() * 2), vec3(1.0f, 0.0f, 0.0f));
	}
	Rail* padlock = new Rail(trPadlock, new Model("./textures/slenderman/scene.gltf"), sh_programID);
	padlock->my_enabled = true;

	Level::CURRENT_LEVEL.slenderman = padlock;
}

void Level::buildFirstLevel(GLuint sh_programID)
{
	Transform tr = Transform();
	tr.position() = vec3(0.0f, 0.0f, -0.1f);
	tr.scale() = vec3(1.0f);
	tr.rotate(glm::pi<float>() / 2, vec3(1.0f, 0.0f, 0.0f));

	Model* model_vago = new Model("./textures/tren sin puertas y puerta/tren_sin_puertas.gltf");
	Vago* vago = new Vago(tr, model_vago, sh_programID);


	Transform tr_2 = Transform();
	tr_2.position() = vec3(19.5f, 0.0f, -0.1f);
	tr_2.scale() = vec3(1.0f);
	tr_2.rotate(glm::pi<float>() / 2, vec3(1.0f, 0.0f, 0.0f));
	tr_2.rotate(glm::pi<float>()*2, vec3(1.0f, 0.0f, 0.0f));

	Vago* vago_2 = new Vago(tr_2, model_vago, sh_programID);
	Level::CURRENT_LEVEL.my_vago_2 = vago_2;


	





	Model* model_taula = new Model({ *Mesh::BASIC_CUBE_MESH_BROWN });
	
	float xValorTaula = -110.98f;

	for (int i = 0; i < 1; i++)
	{
		if (i == 2)
			xValorTaula += 4.53f; //tercera mesa ha de llegar a 5,69
		else if (i > 0)
			xValorTaula += 2.06f;

		vago->addChild(new Taula(Transform(vec3(xValorTaula, 1.2f, -0.7f), quat(1.0f, 0.0f, 0.0f, 0.0f), vec3(1.0f)), model_taula, sh_programID));
	}

	xValorTaula = -110.98f;

	for (int i = 0; i < 1; i++)
	{
		if (i == 2)
			xValorTaula += 4.53f;
		else if (i > 0)
			xValorTaula += 2.06f;

		vago->addChild(new Taula(Transform(vec3(xValorTaula, -1.2f, -0.7f), quat(1.0f, 0.0f, 0.0f, 0.0f), vec3(1.0f)), model_taula, sh_programID));
	}

	Model* model_seient = new Model({ *Mesh::BASIC_CUBE_MESH_SOFT_BROWN });

	quat mirar_endevant = quat(1.0f, 0.0f, 0.0f, 0.0f);
	quat mirar_enrere = quat(glm::cos(glm::pi<float>() / 2), glm::sin(glm::pi<float>() / 2) * 0.0f, glm::sin(glm::pi<float>() / 2) * 0.0f, glm::sin(glm::pi<float>() / 2) * 1.0f);

	float xValorSeientEndavant = -0.31f;

	for (int i = 0; i < 4; i++)
	{
		if (i == 2)
			xValorSeientEndavant += 4.58f; //6,34 - i=3
		else if (i > 0)
			xValorSeientEndavant += 2.02f; //1,69

		vago->addChild(new Seient(Transform(vec3(xValorSeientEndavant, 1.2f, -1.2f), mirar_endevant, vec3(1.0f)), nullptr, sh_programID));
	}

	xValorSeientEndavant = -0.31f;

	for (int i = 0; i < 4; i++)
	{
		if (i == 2)
			xValorSeientEndavant += 4.58f;
		else if (i > 0)
			xValorSeientEndavant += 2.02f;

		vago->addChild(new Seient(Transform(vec3(xValorSeientEndavant, -1.2f, -1.2f), mirar_endevant, vec3(1.0f)), nullptr, sh_programID));
	}

	float xValorSeientEndarrere = -1.63f;
	
	for (int i = 0; i < 4; i++)
	{
		if (i == 2)
			xValorSeientEndarrere += 4.55f; //5,04 - i=3
		else if (i > 0)
			xValorSeientEndarrere += 2.02f; //0.39

		vago->addChild(new Seient(Transform(vec3(xValorSeientEndarrere, 1.2f, -1.2f), mirar_enrere, vec3(1.0f)), nullptr, sh_programID));
	}

	xValorSeientEndarrere = -1.63f;

	for (int i = 0; i < 4; i++)
	{
		if (i == 2)
			xValorSeientEndarrere += 4.55f;
		else if (i > 0)
			xValorSeientEndarrere += 2.02f;

		vago->addChild(new Seient(Transform(vec3(xValorSeientEndarrere, -1.2f, -1.2f), mirar_enrere, vec3(1.0f)), nullptr, sh_programID));
	}

	Model* porta = new Model("./textures/tren sin puertas y puerta/puerta.gltf");

	Transform tr_porta_fixa;
	GameEntity* porta_fixa = new GameEntity(tr_porta_fixa, porta, sh_programID);
	vago->addChild(porta_fixa);

	Transform tr_porta_mobil;

	tr_porta_mobil.rotate(PI * 2, {0, 0, 1});
	tr_porta_mobil.scale(1);
	tr_porta_mobil.translate({0, -6.41, 0});
	GameEntity* porta_mobil = new GameEntity(tr_porta_mobil, porta, sh_programID);
	vago->afegir_porta(porta_mobil, vec3(1, 0, 0));

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

	Rail* railes = new Rail(trRail, new Model("./textures/tren_final/scene.gltf INVALID"), sh_programID);
	Level::CURRENT_LEVEL.rail = railes;

	//cartel exit
	Transform trExit = Transform();
	trExit.position() = vec3(0, -8.70, 2.65f);
	trExit.scale() = vec3(0.055f);
	trExit.rotate(glm::pi<float>() * 2, vec3(1.0f, 0.0f, 0.0f));
	GameEntity* exit = new GameEntity(trExit, new Model("./textures/exit/scene.gltf"), sh_programID);

	vago->addChild(exit);

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
	trCrypt.rotate((PI / -2) * 3, vec3(0.0f, 0.0f, 1.0f));

	Crypt* crypt = new Crypt(trCrypt, new Model("./textures/placa_codi/placa_codi.obj"), sh_programID);

	//panel
	Transform trPanel = Transform();
	trPanel.translate(vec3(8.75f, -0.8f, 1.9f));
	trPanel.rotate((PI / -2) * 3, vec3(0.0f, 0.0f, 1.0f));
	trPanel.scale(vec3(0.1f));

	Panel* panel = new Panel(trPanel, new Model("./textures/panel/panel_propio.obj"), sh_programID);
	panel->set_display_digits_models(load_panel_digit_models());
	//panel_color
	Transform trPanelColor = Transform();
	trPanelColor.translate(vec3(8.75f, -0.8f, 2.15f));
	trPanelColor.rotate((PI / -2) * 3, vec3(0.0f, 0.0f, 1.0f));
	trPanelColor.scale(vec3(0.06f));

	GameEntity* panel_color = new GameEntity(trPanelColor, new Model("./textures/panel_color/panel_color.obj"), sh_programID);
	
	//slenderman
	Transform trPadlock = Transform();
	trPadlock.position() = vec3(7.0f, 0.0f, -0.1f);
	trPadlock.scale() = vec3(0.5f);

	trPadlock.rotate(-(glm::pi<float>() / 2), vec3(1.0f, 0.0f, 0.0f));

	Rail* padlock = new Rail(trPadlock, new Model("./textures/slenderman/scene.gltf"), sh_programID);
	padlock->my_enabled = false;


	Model* model_rail = new Model("./textures/rails/rail1/scene.gltf");
	Transform via_tr;
	via_tr.translate({ 17.0f, -1.736f, -1.35f });
	Via* via = new Via(via_tr, model_rail, sh_programID, 25);
	Level::CURRENT_LEVEL.via = via;

	Transform via_secundaria_tr;
	via_secundaria_tr.translate({ 17.0f, 10.0f, -1.35f });
	Via* via_secundaria = new Via(via_secundaria_tr, model_rail, sh_programID, 25);
	Level::CURRENT_LEVEL.via_secundaria = via_secundaria;

	Model* model_terreny = new Model("./textures/valley/valley.gltf");
	Transform terreny_tr;
	terreny_tr.translate({ 17.0f, 6.5f, -2.0f });
	Terreny* terreny = new Terreny(terreny_tr, model_terreny, sh_programID, 25);
	Level::CURRENT_LEVEL.terreny = terreny;
	

	//tren passant
	Model* model_exterior = new Model("./textures/tren_exterior/scene.gltf");
	Transform trExterior;
	trExterior.position() = vec3(750.0f, 11.814f, -1.2f);
	Tren_passant* tren_passant = new Tren_passant(trExterior, model_exterior, sh_programID, 80);
	Level::CURRENT_LEVEL.tren_passant = tren_passant;


	//-------------------------------------SLENDERMANS----------------------------------------------
	//pasagero
	/*
	Transform trBilly = Transform();
	trBilly.position() = vec3(8.0f, -1.5f, -0.1f);
	trBilly.scale() = vec3(0.5f);
	trBilly.rotate((glm::pi<float>() / 2), vec3(1.0f, 0.0f, 0.0f));
	Rail* billy = new Rail(trBilly, new Model("./textures/slenderman/scene.gltf"), sh_programID);
	*/

	//megafono
	Transform trMegafono = Transform();
	trMegafono.position() = vec3(-2.55f, 0.0f, 2.4f);
	trMegafono.scale() = vec3(1.6f);

	trMegafono.rotate(glm::pi<float>() / 2, vec3(0.0f, 0.0f, 1.0f));
	trMegafono.rotate(glm::pi<float>() * 2, vec3(0.0f, 0.0f, 1.0f));
	trMegafono.rotate((glm::pi<float>() / 5), vec3(0.0f, 1.0f, 0.0f));
	GameEntity* megafono = new GameEntity(trMegafono, new Model("./textures/megafono/scene.gltf"), sh_programID);

	//rellotge 1
	Transform trClock = Transform();
	trClock.scale(vec3(0.15f));
	trClock.translate(vec3(7.6, -1.6f, 0.0f));
	trClock.rotate(PI / 2, vec3(0.0f, 0.0f, 1.0f));
	//trClock.rotate(PI / -6, vec3(1.0f, 0.0f, 0.0f));

	GameEntity* clock = new GameEntity(trClock, new Model("./textures/clock/clock1.obj"), sh_programID);

	//rellotge 2
	Transform trClock2 = Transform();
	trClock2.translate(vec3(4.7f, -1.9f, 1.5f));
	trClock2.scale(vec3(0.2f));
	trClock2.rotate(PI / -6, vec3(.0f, .0f, 0.0f));
	GameEntity* clock2 = new GameEntity(trClock2, new Model("./textures/clock/clock2.obj"), sh_programID);

	//rellotge 3
	Transform trClock3 = Transform();
	trClock3.translate(vec3(-1.5, 1.45f, 0.5f));
	trClock3.scale(vec3(0.2f));
	//trClock3.rotate(PI / -4, vec3(1.0f, 0.0f, 0.0f));
	GameEntity* clock3 = new GameEntity(trClock3, new Model("./textures/clock/clock3.obj"), sh_programID);

	//biblia
	Transform trBiblia = Transform();
	trBiblia.translate(vec3(8.75f, 1.3f, 1.7f));
	trBiblia.scale(vec3(0.2f));
	trBiblia.rotate(PI / -2, vec3(1.0f, 0.0f, 0.0f));
	GameEntity* biblia = new GameEntity(trBiblia, new Model("./textures/biblia/biblia.obj"), sh_programID);

	// palanca
	Transform trLever = Transform();
	trLever.translate(vec3(20.0f, 0.0f, 0.0f));
	Lever* lever = new Lever(trLever, new Model("./textures/lever/lever.obj"), sh_programID);

	Level::CURRENT_LEVEL.slenderman = padlock;
	Level::CURRENT_LEVEL.my_vago = vago;
	Level::CURRENT_LEVEL.maleta = maleta;
	Level::CURRENT_LEVEL.maletaTapa = maletaTapa;
	Level::CURRENT_LEVEL.libro1 = libro1;
	Level::CURRENT_LEVEL.crypt = crypt;
	Level::CURRENT_LEVEL.panel = panel;
	Level::CURRENT_LEVEL.panel_color = panel_color;
	Level::CURRENT_LEVEL.my_entity_under_cursor = nullptr;
	Level::CURRENT_LEVEL.megaphone = megafono;
	Level::CURRENT_LEVEL.clock = clock;
	Level::CURRENT_LEVEL.clock2 = clock2;
	Level::CURRENT_LEVEL.clock3 = clock3;
	Level::CURRENT_LEVEL.biblia = biblia;
	Level::CURRENT_LEVEL.lever = lever;
	//Level::CURRENT_LEVEL.exterior_tren = exterior;
	
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
		//audio2.play2D("./media/light_flickering.wav", false, false);
		Audio::AUDIO_FUNCTIONS.play2D("./media/spooky_sound.wav", false, false);

		// Mostrar slenderman
		slenderman->my_enabled = true;
	}
}

void Level::despawnSlender()
{
	// return to normal lighting
	*llumAmbient = true;
	*iFixe = false;

	slenderman->my_enabled = false;
}



