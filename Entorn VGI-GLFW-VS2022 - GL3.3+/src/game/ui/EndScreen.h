#include "UIElement.h"

class EndScreen : public UIElement
{
public:
	static EndScreen* instance;

	EndScreen(Transform transform, UIElement* win_screen, UIElement* loss_screen)
		: UIElement(transform), win_screen(win_screen), loss_screen(loss_screen) {
		loss_screen->disable();
		win_screen->disable();

		add_child(win_screen);
		add_child(loss_screen);
	}

	void win()
	{
		loss_screen->disable();
		win_screen->enable();
	}

	void lose()
	{
		win_screen->disable();
		loss_screen->enable();
	}

private:
	UIElement* win_screen;
	UIElement* loss_screen;
};
