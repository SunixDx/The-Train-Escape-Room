#pragma once
#include <iostream>
#include "../src/stdafx.h"

using namespace std;

class Camera {
public:
	// Variables de control de l'opci� C�mera->Personalitzada?
	float horizontal_angle = 0;
	float vertical_angle = 0;
	float move_speed = 0.5;
	float turn_speed = PI / 20;
	float mouse_speed = 0.001;
	glm::vec3 position;

	static Camera MAIN_CAMERA;

};