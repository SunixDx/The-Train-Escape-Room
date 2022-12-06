#pragma once
#include "../graphics/Transform.h"
#include "../graphics/Model.h"


class GameEntity
{
public:
	GameEntity(Transform transform, Model* model, GLuint shader_id):
		my_transform(transform), my_model(model), my_shader_id(shader_id),
		my_enabled(true), my_interactable(false)
	{ };

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

	bool is_interactable() const { return my_enabled && my_interactable; }

//protected:
	Transform my_transform;
	Model* my_model;
	GLuint my_shader_id;
	bool my_enabled;
	bool my_interactable;

	std::vector<GameEntity*> my_children;
};
