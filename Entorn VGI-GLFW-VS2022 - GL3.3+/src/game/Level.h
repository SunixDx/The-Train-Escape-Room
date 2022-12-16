#pragma once

#include "entities/Vago.h"
#include "entities/Cucaracha.h"
#include "entities/Maleta.h"
#include "entities/Libro1.h"
#include "entities/Crypt.h"
#include "entities/Panel.h"
#include "entities/Rail.h"

class Level {
public:
	static void buildFirstLevel(GLuint sh_programID);
	Vago* my_vago;
	Cucaracha* cucaracha;
	Maleta* maleta;
	GameEntity* maletaTapa;
	Libro1* libro1;
	
	//tren exterior
	Rail* rail;

	//railes
	Rail* rail1;
	Rail* rail_1;
	Rail* rail2;
	Rail* rail_2;
	Rail* rail3;
	Rail* rail_3;
	Rail* rail4;
	Rail* rail_4;
	Rail* rail5;
	Rail* rail_5;
	Rail* rail6;
	Rail* rail_6;
	//monstres
	Rail* padlock;
	Rail* billy;

	Crypt* crypt;
	Panel* panel;
	Rail* exterior_tren;
	Rail* megaphone;

	//llums
	bool* llumAmbient;
	bool* iFixe;

	InteractableEntity* my_entity_under_cursor;

	static Level CURRENT_LEVEL;


	void MaybeSpawnSlender();
	void despawnSlender();
};