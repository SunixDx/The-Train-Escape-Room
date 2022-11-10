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

	// Variables de control de l'opci� C�mera->Personalitzada?
	float horizontal_angle = 0;
	float vertical_angle = 0;
	float move_speed = 2;
	float turn_speed = PI / 20;
	float mouse_speed = 0.001;
	glm::vec3 position;

	btRigidBody* my_rigid_body;

	bool sit = false;

	static Camera MAIN_CAMERA;
	static Camera SAVE_CAMERA;
};