#pragma once
#include "UIElement.h"
#include "../entities/InteractableEntity.h"

class InteractionIndicator : public UIElement
{
public:
	static InteractionIndicator instance;

	InteractionIndicator(Transform transform) : UIElement(transform)
	{

	}

	void change_indicator(InteractionType type);
	void remove_indicator();

	InteractionIndicator& set_sit_indicator(UIElement* indicator);
	InteractionIndicator& set_open_close_indicator(UIElement* indicator);
	InteractionIndicator& set_maleta(UIElement* indicador);
	InteractionIndicator& set_close_up_indicator(UIElement* indicator);
	InteractionIndicator& set_lever(UIElement* indicator);

private:
	UIElement* sit_indicator = nullptr;
	UIElement* maleta_indicator = nullptr;
	UIElement* open_close_indicator = nullptr;
	UIElement* close_up_indicator = nullptr;
	UIElement* lever_inidicator = nullptr;
};
