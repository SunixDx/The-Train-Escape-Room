#pragma once
#include "GameEntity.h"


enum class InteractionType
{
	OPEN_CLOSE,
	SIT,
	CLOSE_UP,
};

class InteractableEntity : public GameEntity
{
public:
	InteractableEntity(Transform transform, Model* model, GLuint shader_id, InteractionType interaction_type) : GameEntity(transform, model, shader_id)
	{
		my_interactable = true;
		my_interaction_type = interaction_type;
	}

	virtual void interact()
	{

	}

	virtual InteractionType interaction_type() const
	{
		return my_interaction_type;
	}

	InteractionType my_interaction_type;
};