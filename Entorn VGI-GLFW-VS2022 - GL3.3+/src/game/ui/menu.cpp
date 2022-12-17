#include "menu.h"

Menu Menu::instance = Menu(Transform());

void Menu::change_indicator(MenuType type)
{
	my_children.clear();

	switch (type)
	{
	case MenuType::MENU:
		my_children.push_back(my_menu_default);
		break;
	case MenuType::START:
		my_children.push_back(my_menu_start);
		break;
	case MenuType::EXIT:
		my_children.push_back(my_menu_exit);
		break;
	default:
		break;
	}
}

void Menu::remove_indicator()
{
	my_children.clear();
}

Menu& Menu::set_menu_default(UIElement* indicator)
{
	my_menu_default = indicator;

	return *this;
}

Menu& Menu::set_menu_exit(UIElement* indicator)
{
	my_menu_exit = indicator;

	return *this;
}

Menu& Menu::set_menu_start(UIElement* indicator)
{
	my_menu_start = indicator;

	return *this;
}
