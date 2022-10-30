#pragma once
#include <iostream>
#include "../src/stdafx.h"
#include <bullet/btBulletDynamicsCommon.h>

using namespace std;

class Camera {
public:

	void setupColliders();
	void syncColliders();
	

	// Variables de control de l'opci� C�mera->Personalitzada?
	float horizontal_angle = 0;
	float vertical_angle = 0;
	float move_speed = 0.075;
	float turn_speed = PI / 20;
	float mouse_speed = 0.001;
	glm::vec3 position;

	btRigidBody* my_rigid_body;

	static Camera MAIN_CAMERA;
};