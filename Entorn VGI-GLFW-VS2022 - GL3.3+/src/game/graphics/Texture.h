#pragma once
#include <string>

// Texture: Estructura amb atributs de textures de la malla.
struct Texture {
	unsigned int id; // Identificador de l’objecte textura de la malla.
	std::string type; // Tipus de textura de la malla: diffuse map o specular map.
	std::string path; // store path of texture to compare with other texture.
};
