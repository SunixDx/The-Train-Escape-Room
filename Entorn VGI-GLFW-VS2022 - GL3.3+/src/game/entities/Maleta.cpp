#include "Maleta.h"

Maleta::Maleta(Transform transform, Model* model, GLuint shader_program_id, GameEntity* tapa) : InteractableEntity(transform, model, shader_program_id, InteractionType::MALETA), my_aixecada(false)
{
	my_tapa = tapa;
	addChild(tapa);

	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(.5), btScalar(.5), btScalar(.35))); //definir collider

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(my_transform.position().x, my_transform.position().y, my_transform.position().z)); //posicion donde va el objeto

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

void Maleta::interact()
{
	std::cout << "HAS INTERACTUADO CON LA MALETA, ¡¡¡FELICIDADES!!!" << std::endl;

	if (my_aixecada)
		my_tapa->my_transform.orientation().y -= 0.5f;
	else 
		my_tapa->my_transform.orientation().y += 0.5f;

	my_aixecada = !my_aixecada;
}
