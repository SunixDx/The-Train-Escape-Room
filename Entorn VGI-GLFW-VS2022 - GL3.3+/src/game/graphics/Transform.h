#pragma once
#include "../src/stdafx.h"


class Transform
{
public:
	Transform(glm::vec3 position, glm::quat orientation, glm::vec3 scale): my_position(position), my_orientation(orientation), my_scale(scale) { };
	Transform(): my_position(glm::vec3(0.0f, 0.0f, 0.0f)), my_orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), my_scale(glm::vec3(1.0f, 1.0f, 1.0f)) { }

	static Transform blank() {
		return Transform(
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
	}

	mat4 apply(mat4 matriu_transformacions);

	void translate(glm::vec3 movement);
	void rotate(glm::quat rotation);
	void rotate(float angle, glm::vec3 axis);
	void scale(float factor);
	void scale(glm::vec3 factor);

	glm::vec3& position() {
		return my_position;
	}

	glm::vec3 position() const {
		return my_position;
	}

	glm::quat& orientation() {
		return my_orientation;
	}

	glm::quat orientation() const {
		return my_orientation;
	}

	glm::vec3& scale() {
		return my_scale;
	}

	glm::vec3 scale() const {
		return my_scale;
	}

private:
	glm::vec3 my_position;

	glm::quat my_orientation;

	glm::vec3 my_scale;
};
