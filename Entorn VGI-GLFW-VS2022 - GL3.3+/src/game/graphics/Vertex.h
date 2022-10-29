#pragma once
#include "../src/shader.h"

// Estructures de la classe Mesh.
// Vertex: Estructura amb atributs d�un vertex de la malla.
struct Vertex {
	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 tex_coords, glm::vec4 color) :
		Position(position), Normal(normal), TexCoords(tex_coords), Color(color) {}
	Vertex() : Position(), Normal(), TexCoords(), Color() {}

	glm::vec3 Position; // Posici� (x,y,z) del vertex de la malla.
	glm::vec3 Normal; // Vector normal (nx,ny,nz) del vertex de la malla.
	glm::vec2 TexCoords; // Coordenada textura (s,t) del vertex de la malla.
	glm::vec4 Color; // Color (r, g, b, a) del vertex de la malla.
};
