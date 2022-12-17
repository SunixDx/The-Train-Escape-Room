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

class Level {
public:
	static void buildFirstLevel(GLuint sh_programID);
	Vago* my_vago;
	Cucaracha* cucaracha;
	Maleta* maleta;
	GameEntity* maletaTapa;
	Libro1* libro1;
	Rail* rail;
	Rail* padlock;
	Crypt* crypt;
	Panel* panel;
	Rail* exterior_tren;
	Rail* megaphone;
	GameEntity* clock;
	GameEntity* clock2;
	GameEntity* clock3;
	GameEntity* biblia;
	Lever* lever;

	//llums
	bool* flicker;
	bool* setSpookyLights;
	bool* llumAmbient;
	bool* iFixe;

	bool gameStarted = false;

	//temps
	chrono::steady_clock::time_point gameTimer; //comença a contar al clicar start
	chrono::steady_clock::time_point gameTimer2;
	chrono::steady_clock::time_point lightTimer;

	//sons
	vector<irrklang::ISound*> sonsSlenderman;
	irrklang::ISound* trainSound;

	InteractableEntity* my_entity_under_cursor;

	static Level CURRENT_LEVEL;

	void MaybeSpawnSlender();
	void despawnSlender();
};