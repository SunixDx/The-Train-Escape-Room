#pragma once
#include <iostream>
#include "../src/stdafx.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "../entities/Seient.h"

using namespace std;

class Camera {
public:

	void setupColliders();
	void syncColliders();
	void sitDown(const Seient* seient);
	void standUp();
	void zoomIn(Transform trans);
	void zoomOut();

	void fly();
	void enterTrain();
	void fly_arround(glm::vec3 center);

	// Variables de control de l'opci� C�mera->Personalitzada?
	float horizontal_angle = 0;
	float vertical_angle = 0;
	float move_speed = 2;
	float turn_speed = PI / 20;
	float mouse_speed = 0.001;
	glm::vec3 position;

	float angular_speed = PI / 10000;
	float view_angle = PI / 4;
	float flying_radius = 10;
	
	btRigidBody* my_rigid_body;

	bool sit = false;
	bool flying = false;
	bool zoom = false;

	static Camera MAIN_CAMERA;
	static Camera SAVE_CAMERA;
	const static Camera START_CAMERA;
};