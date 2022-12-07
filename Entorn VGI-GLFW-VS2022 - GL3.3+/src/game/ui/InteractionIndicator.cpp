#include "InteractionIndicator.h"

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
	case InteractionType::CLOSE_UP:
		my_children.push_back(close_up_indicator);
		break;
	default:
		break;
	}
}