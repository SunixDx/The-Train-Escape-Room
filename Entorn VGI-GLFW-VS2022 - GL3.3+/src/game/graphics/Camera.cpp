#include "Camera.h"

Camera Camera::MAIN_CAMERA;
/*
void show_cam_vectors()
{
	glm::vec3 direction(
		cos(vertical_angle) * cos(horizontal_angle),
		sin(horizontal_angle),
		sin(vertical_angle)
	);

	glm::vec3 left = glm::vec3(
		cos(horizontal_angle + PI / 2),
		sin(horizontal_angle + PI / 2),
		0
	);

	glm::vec3 up = glm::cross(direction, left);

	cout << "DIRECTION:" << std::endl;
	cout << "x " << direction[0] << ", y " << direction[1] << ", z " << direction[2] << endl;
	cout << "RIGHT:" << std::endl;
	cout << "x " << left[0] << ", y " << left[1] << ", z " << left[2] << endl;
	cout << "UP:" << std::endl;
	cout << "x " << up[0] << ", y " << up[1] << ", z " << up[2] << endl;
}
*/