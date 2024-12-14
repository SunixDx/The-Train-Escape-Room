#pragma once
#include "../src/game/graphics/Model.h"
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include  <bullet/btBulletDynamicsCommon.h>
#include "../physics/BulletWorld.h"
#include "InteractableEntity.h"
#include "GameEntity.h"
#include <array>


class Panel: public InteractableEntity
{
public:
	Panel(Transform transform, Model* model, GLuint shader_id);

	void interact();

	InteractionType interaction_type() const;

	void set_display_digits_models(std::array<Model*, 10> display_digit_models)
	{
		this->display_digit_models = display_digit_models;
	}

	void push_digit(int digit)
	{
		for (int i = 0; i < display_digits.size() - 1; i++)
		{
			display_digits[i]->my_model = display_digits[i + 1]->my_model;
		}

		display_digits.back()->my_model = display_digit_models[digit];
	}

	void clear_display()
	{
		for (int i = 0; i < display_digits.size(); i++)
		{
			display_digits[i]->my_model = nullptr;
		}
	}

private:
	btRigidBody* my_rigid_body;
	bool zoom;

	std::array<GameEntity*, 3> display_digits;
	std::array<Model*, 10> display_digit_models = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, };
};

