#include "Taula.h"
#include "Vago.h"

Taula::Taula(Transform transform, Mesh* mesh, GLuint shader_id)
{
	my_transform = transform;
	my_mesh = mesh;
	my_shader_program_id = shader_id;

	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(.4), btScalar(.5), btScalar(.35)));

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(my_transform.position.x, my_transform.position.y, my_transform.position.z + Vago::Z_OFFSET));

	btScalar mass(0.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		groundShape->calculateLocalInertia(mass, localInertia);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	body->setUserPointer(this);
	my_rigid_body = body;

	BulletWorld::WORLD->my_collision_shapes.push_back(groundShape);
	BulletWorld::WORLD->my_dynamics_world->addRigidBody(body);
}

void Taula::mostrarPlataforma(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	Transform transform_sostre = Transform(
		vec3(0.0f, 0.0f, 0.0f),
		quat(0.0f, 0.0f, 0.0f, 0.0f),
		vec3(0.8f, 1.0f, 0.02f)
	);

	my_mesh->Draw(MatriuVista, MatriuTG, transform_sostre, shader_program_id);
}

void Taula::mostrarPota(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id)
{
	glm::mat4 NormalMatrix(1.0);
	glm::mat4 ModelMatrix(1.0);

	Transform transform_sostre = Transform(
		vec3(0.0f, 0.0f, -0.35f),
		quat(0.0f, 0.0f, 0.0f, 0.0f),
		vec3(0.02f, 0.02f, 0.7f)
	);

	my_mesh->Draw(MatriuVista, MatriuTG, transform_sostre, shader_program_id);
}

void Taula::mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
	MatriuTG = my_transform.apply(MatriuTG);

	mostrarPlataforma(MatriuVista, MatriuTG, my_shader_program_id);
	mostrarPota(MatriuVista, MatriuTG, my_shader_program_id);
}