#pragma once
#include "InteractableEntity.h"
#include "../graphics/Transform.h"
#include "../graphics/Model.h"


class GameEntity : public InteractableEntity
{
public:
	GameEntity(Transform transform, Model* model, GLuint shader_id): my_transform(transform), my_model(model), my_shader_id(shader_id), my_enabled(true) { };
	void virtual mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG);
	void addChild(GameEntity* child);

	virtual ~GameEntity()
	{
		for (GameEntity* child : my_children)
		{
			delete child;
		}

		my_children.clear();
	}

//protected:
	Transform my_transform;
	Model* my_model;
	GLuint my_shader_id;
	bool my_enabled;

	std::vector<GameEntity*> my_children;
};
