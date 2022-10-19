#include "../src/stdafx.h"


class Transform
{
public:
	Transform(glm::vec3 position, glm::quat orientation, glm::vec3 scale): position(position), orientation(orientation), scale(scale) { };
	Transform(): position(glm::vec3(0.0f, 0.0f, 0.0f)), orientation(glm::quat(0.0f, 0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f, 1.0f, 1.0f)) { }

	static Transform blank() {
		return Transform(
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat(0.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
	}

	glm::vec3 position;

	glm::quat orientation;

	glm::vec3 scale;
};
