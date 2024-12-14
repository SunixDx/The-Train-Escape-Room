#include "../src/game/ui/UIElement.h"

class Crosshair: public UIElement
{
public:
	Crosshair() : UIElement(Transform()) { };
	Crosshair(Transform transform, Texture texture) : UIElement(transform, texture) { };


	static Crosshair instance;
};