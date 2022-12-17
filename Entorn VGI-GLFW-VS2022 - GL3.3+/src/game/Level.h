#pragma once

#include "entities/Vago.h"
#include "entities/Cucaracha.h"
#include "entities/Maleta.h"
#include "entities/Libro1.h"
#include "entities/Crypt.h"
#include "entities/Panel.h"
#include "entities/Rail.h"
#include "entities/Lever.h"
#include "entities/Via.h"
#include "entities/Terreny.h"


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


	

	Via* via;
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
	Rail* exterior_tren;
	GameEntity* megaphone;
	GameEntity* clock;
	GameEntity* clock2;
	GameEntity* clock3;
	GameEntity* biblia;
	Lever* lever;

	//llums
	bool* llumAmbient;
	bool* iFixe;

	InteractableEntity* my_entity_under_cursor;

	static Level CURRENT_LEVEL;

	void MaybeSpawnSlender();
	void despawnSlender();
};