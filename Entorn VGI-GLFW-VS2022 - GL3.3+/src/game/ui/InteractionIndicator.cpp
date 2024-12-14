#include "InteractionIndicator.h"

InteractionIndicator InteractionIndicator::instance = InteractionIndicator(Transform());

void InteractionIndicator::change_indicator(InteractionType type)
{
	my_children.clear();

	switch (type)
	{
	case InteractionType::OPEN_CLOSE:
		my_children.push_back(open_close_indicator);
		break;
	case InteractionType::SIT:
		my_children.push_back(sit_indicator);
		break;
	case InteractionType::MALETA:
		my_children.push_back(maleta_indicator);
		break;
	case InteractionType::CLOSE_UP:
		my_children.push_back(close_up_indicator);
		break;
	case InteractionType::LEVER:
		my_children.push_back(lever_inidicator);
		break;
	default:
		break;
	}
}

void InteractionIndicator::remove_indicator()
{
	my_children.clear();
}

InteractionIndicator& InteractionIndicator::set_sit_indicator(UIElement* indicator)
{
	sit_indicator = indicator;
	return *this;
}

InteractionIndicator& InteractionIndicator::set_maleta(UIElement* indicator)
{
	maleta_indicator = indicator;
	return *this;
}

InteractionIndicator& InteractionIndicator::set_open_close_indicator(UIElement* indicator)
{
	open_close_indicator = indicator;
	return *this;
}

InteractionIndicator& InteractionIndicator::set_close_up_indicator(UIElement* indicator)
{
	close_up_indicator = indicator;
	return *this;
}

InteractionIndicator& InteractionIndicator::set_lever(UIElement* indicator)
{
	lever_inidicator = indicator;
	return *this;
}
