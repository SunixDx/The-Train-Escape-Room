#pragma once

#include <chrono>
#include "entities/Vago.h"
#include "entities/Cucaracha.h"
#include "entities/Maleta.h"
#include "entities/Libro1.h"
#include "entities/Crypt.h"
#include "entities/Panel.h"
#include "entities/Rail.h"
#include "audio/AudioFunctions.h"
#include "entities/Lever.h"
#include "entities/Via.h"
#include "entities/Terreny.h"
#include "entities/tren_passant.h"


class Level {
public:
	static void buildFirstLevel(GLuint sh_programID);
	static void slender_offset(GLuint sh_programID, glm::vec3 offset_slenderman);
	static void exterior_train_offset(GLuint sh_programID, glm::vec3 offset_exterior);
	Vago* my_vago;
	Vago* my_vago_2;
	Cucaracha* cucaracha;
	Maleta* maleta;
	GameEntity* maletaTapa;
	Libro1* libro1;
	
	//tren exterior
	Rail* rail;	
	//tren passant
	Tren_passant* tren_passant;

	Via* via;
	Via* via_secundaria;
	Terreny* terreny;
	//railes
	Rail* rail1;
	Rail* rail2;
	Rail* rail3;
	Rail* rail4;
	Rail* rail5;
	Rail* rail6;
	//monstres
	Rail* slenderman;
	Rail* billy;

	Crypt* crypt;
	Panel* panel;
	GameEntity* panel_color;
	GameEntity* megaphone;
	GameEntity* clock;
	GameEntity* clock2;
	GameEntity* clock3;
	GameEntity* biblia;
	Lever* lever;

	//llums
	bool flicker = false;
	bool setScaryLights = false;
	bool* llumAmbient;
	bool* iFixe;
		//combinacions de llums per l'efecte de parpadeig -> first = llumAmbient, second = ifixe
	vector <pair<bool, bool>> lights{ make_pair(false, true), make_pair(false, false), make_pair(true, false), make_pair(true, true) };

	//control de partida 
	bool gameStarted = false;

	//temps
	chrono::steady_clock::time_point gameTimer; //comença a contar al clicar start
	chrono::steady_clock::time_point gameTimer2;

	//sons
	vector<irrklang::ISound*> sonsSlenderman;

	irrklang::ISound* trainSound;
	irrklang::ISound* audioExplicacion;

	InteractableEntity* my_entity_under_cursor;

	static Level CURRENT_LEVEL;

	void MaybeSpawnSlender();
	void despawnSlender();
};