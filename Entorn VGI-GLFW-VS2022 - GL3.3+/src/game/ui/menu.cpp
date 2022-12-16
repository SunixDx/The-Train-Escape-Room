#include "menu.h"

Menu Menu::instance = Menu(Transform());

void Menu::change_indicator(InteractionType type)
{
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
