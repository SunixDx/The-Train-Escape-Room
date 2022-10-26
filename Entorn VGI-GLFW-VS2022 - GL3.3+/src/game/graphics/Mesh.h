#include <vector>
#include "Vertex.h"
#include "Texture.h"

#include "../src/shader.h"
#include "bt3/btBulletCollisionCommon.h"
#include "bt3/btBulletDynamicsCommon.h"
class Mesh{
public:
	// Mesh data
	std::vector<Vertex> vertices; // Vector amb atributs als vèrtexs de la malla.
	std::vector<unsigned int> indices; // Vector índexs a vèrtexs de cares de la malla per a objecte EBO.
	std::vector<Texture> textures; // vector d’atributs de textures de la malla.
	// Functions:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
	private:
		// Render data:
		unsigned int VAO, VBO, EBO;
		// Functions:
		void setupMesh();
};
