#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <gl/SOIL.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Mesh.h"
#include "../src/shader.h"
#include "Texture.h"

using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
	static Model* BACKPACK;

	Model(string path)
	{
		loadModel(path);
	}
	void Draw(mat4 MatriuVista, mat4 MatriuTG, Transform& transform, GLuint shader_id);
private:
	// model data
	std::vector<Mesh> meshes;
	std::string directory;
	vector<Texture> textures_loaded;
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat,
		aiTextureType type, std::string typeName);
};

#endif // !MODEL_H