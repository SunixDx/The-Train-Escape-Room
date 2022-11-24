#include "Rail.h"

void Rail::interact()
{
	std::cout << "HAS INTERACTUADO CON RAIL, ¡¡¡FELICIDADES!!!" << std::endl;

	my_transform.position().x += 0.5f; //movemos la mesa
}
