#pragma once
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include  <bullet/btBulletDynamicsCommon.h>
#include "../physics/BulletWorld.h"


class Taula
{
public:
	Taula(Transform transform, Mesh* mesh, GLuint shader_program_id);
	~Taula() { 
		BulletWorld::WORLD->my_dynamics_world->removeRigidBody(my_rigid_body);
		delete my_rigid_body; }

	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG);
private:

	Transform my_transform;
	Mesh* my_mesh;
	GLuint my_shader_program_id;
	btRigidBody* my_rigid_body;

	void mostrarPlataforma(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id);
	void mostrarPota(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id);
};
