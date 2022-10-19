#include <glm/glm.hpp>

// Estructures de la classe Mesh.
// Vertex: Estructura amb atributs d’un vertex de la malla.
struct Vertex {
	glm::vec3 Position; // Posició (x,y,z) del vertex de la malla.
	glm::vec3 Normal; // Vector normal (nx,ny,nz) del vertex de la malla.
	glm::vec2 TexCoords; // Coordenada textura (s,t) del vertex de la malla.
};
