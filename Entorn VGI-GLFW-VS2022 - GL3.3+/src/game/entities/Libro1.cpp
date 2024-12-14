#include "Libro1.h"

Libro1::Libro1(Transform transform, Model* model_tancat, Model* model_obert, GLuint shader_id) : InteractableEntity(transform, model_tancat, shader_id, InteractionType::OPEN_CLOSE)
{
	my_model_obert = model_obert;
	my_model_tancat = model_tancat;

	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(.15), btScalar(0.1), btScalar(.1))); //definir collider

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(my_transform.position().x, my_transform.position().y, my_transform.position().z));// + Vago::Z_OFFSET)); //posicion donde va el objeto

	btScalar mass(0.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		groundShape->calculateLocalInertia(mass, localInertia);

	//rigidbody
	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	body->setUserPointer(this); //cogemos el body
	my_rigid_body = body;

	BulletWorld::WORLD->my_collision_shapes.push_back(groundShape);
	BulletWorld::WORLD->my_dynamics_world->addRigidBody(body);
}

void Libro1::interact()
{
	if (!abierto)
	{
		my_model = my_model_obert;
		abierto = true;
		my_transform.rotate((PI / 6) * 3, vec3(1.0f, 0.0f, 0.0f));
		std::cout << "HAS ABIERTO EL LIBRO" << std::endl;
	}
	else
	{
		my_model = my_model_tancat;
		abierto = false;
		my_transform.rotate((PI / 6) * -3, vec3(1.0f, 0.0f, 0.0f));
		std::cout << "HAS CERRADO EL LIBRO" << std::endl;
	}
}
