#pragma once
#include "UIElement.h"
#include "../entities/InteractableEntity.h"

class InteractionIndicator : public UIElement
{
public:
	InteractionIndicator(Transform transform) : UIElement(transform)
	{

	}

	void change_indicator(InteractionType type);

private:
	UIElement* sit_indicator = nullptr;
	UIElement* open_close_indicator = nullptr;
	UIElement* close_up_indicator = nullptr;
};
