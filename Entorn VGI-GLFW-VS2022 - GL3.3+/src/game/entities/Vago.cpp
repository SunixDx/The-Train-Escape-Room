#include "Vago.h"

float Vago::Z_OFFSET = 1.5f;

Vago::Vago(Transform transform, Model* model, GLuint shader_id): GameEntity(transform, model, shader_id)
{
	btCollisionShape* groundShape_paret1 = new btBoxShape(btVector3(btScalar(6.f), btScalar(0.1), btScalar(1.f)));
	btCollisionShape* groundShape_paret2 = new btBoxShape(btVector3(btScalar(6.f), btScalar(0.1f), btScalar(1.f)));
	btCollisionShape* groundShape_porta = new btBoxShape(btVector3(btScalar(0.1), btScalar(0.5f), btScalar(1.f)));
	btCollisionShape* groundShape_paret4 = new btBoxShape(btVector3(btScalar(0.1f), btScalar(2.f), btScalar(1.f)));

	// PARET 1 (paret del libro [izquierda])
	btTransform groundTransform_paret1;
	groundTransform_paret1.setIdentity();
	groundTransform_paret1.setOrigin(btVector3(my_transform.position().x + 2.8f, my_transform.position().y - 2.1f, my_transform.position().z + Vago::Z_OFFSET));

	btScalar mass_paret1(0.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	btVector3 localInertia_paret1(0, 0, 0);
	if (mass_paret1 != 0.f)
		groundShape_paret1->calculateLocalInertia(mass_paret1, localInertia_paret1);


	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState_paret1 = new btDefaultMotionState(groundTransform_paret1);
	btRigidBody::btRigidBodyConstructionInfo rbInfo_paret1(mass_paret1, myMotionState_paret1, groundShape_paret1, localInertia_paret1);
	btRigidBody* body_paret1 = new btRigidBody(rbInfo_paret1);


	body_paret1->setUserPointer(this);
	my_rigidbodies.push_back(body_paret1);

	BulletWorld::WORLD->my_collision_shapes.push_back(groundShape_paret1);
	BulletWorld::WORLD->my_dynamics_world->addRigidBody(body_paret1);

	// PARET 2 (paret de la maleta [derecha])
	btTransform groundTransform_paret2;
	groundTransform_paret2.setIdentity();
	groundTransform_paret2.setOrigin(btVector3(my_transform.position().x + 2.8f, my_transform.position().y + 2.1f, my_transform.position().z + Vago::Z_OFFSET));

	btScalar mass_paret2(0.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	btVector3 localInertia_paret2(0, 0, 0);
	if (mass_paret2 != 0.f)
		groundShape_paret2->calculateLocalInertia(mass_paret2, localInertia_paret2);


	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState_paret2 = new btDefaultMotionState(groundTransform_paret2);
	btRigidBody::btRigidBodyConstructionInfo rbInfo_paret2(mass_paret2, myMotionState_paret2, groundShape_paret2, localInertia_paret2);
	btRigidBody* body_paret2 = new btRigidBody(rbInfo_paret2);


	body_paret2->setUserPointer(this);
	my_rigidbodies.push_back(body_paret2);

	BulletWorld::WORLD->my_collision_shapes.push_back(groundShape_paret2);
	BulletWorld::WORLD->my_dynamics_world->addRigidBody(body_paret2);

	// PARET 3 (paret megafono [delante])
	
	btTransform groundTransform_porta;
	groundTransform_porta.setIdentity();
	groundTransform_porta.setOrigin(btVector3(my_transform.position().x + 8.8f, my_transform.position().y, my_transform.position().z + Vago::Z_OFFSET));
	
	btScalar mass_porta(0.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	btVector3 localInertia_porta(0, 0, 0);
	if (mass_porta != 0.f)
		groundShape_porta->calculateLocalInertia(mass_porta, localInertia_porta);


	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState_porta = new btDefaultMotionState(groundTransform_porta);
	btRigidBody::btRigidBodyConstructionInfo rbInfo_porta(mass_porta, myMotionState_porta, groundShape_porta, localInertia_porta);
	btRigidBody* body_porta = new btRigidBody(rbInfo_porta);


	body_porta->setUserPointer(this);
	my_rigidbodies.push_back(body_porta);
	my_rigid_body_porta = body_porta;

	BulletWorld::WORLD->my_collision_shapes.push_back(groundShape_porta);
	BulletWorld::WORLD->my_dynamics_world->addRigidBody(body_porta);

	btTransform groundTransform_paret4;
	groundTransform_paret4.setIdentity();
	groundTransform_paret4.setOrigin(btVector3(my_transform.position().x - 2.3f, my_transform.position().y, my_transform.position().z + Vago::Z_OFFSET));

	btScalar mass_paret4(0.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	btVector3 localInertia_paret4(0, 0, 0);
	if (mass_paret4 != 0.f)
		groundShape_paret4->calculateLocalInertia(mass_paret4, localInertia_paret4);


	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState_paret4 = new btDefaultMotionState(groundTransform_paret4);
	btRigidBody::btRigidBodyConstructionInfo rbInfo_paret4(mass_paret4, myMotionState_paret4, groundShape_paret4, localInertia_paret4);
	btRigidBody* body_paret4 = new btRigidBody(rbInfo_paret4);


	body_paret4->setUserPointer(this);
	my_rigidbodies.push_back(body_paret4);


	BulletWorld::WORLD->my_collision_shapes.push_back(groundShape_paret4);
	BulletWorld::WORLD->my_dynamics_world->addRigidBody(body_paret4);

	my_children.push_back(new GameEntity(Transform(
		vec3(0.0f, 2.1f, 0.0f),
		quat(1.0f, 0.0f, 0.0f, 0.0f),
		vec3(16.0f, 0.1f, 3.0f)
	), nullptr, my_shader_id));
	
	
	my_children.push_back(new GameEntity(Transform(
		vec3(0.0f, -2.1f, 0.0f),
		quat(1.0f, 0.0f, 0.0f, 0.0f),
		vec3(16.0f, 0.1f, 3.0f)
	), nullptr, my_shader_id));

	/*
	my_children.push_back(new GameEntity(Transform(
		vec3(0.0f, 0.0f, -1.5f),
		quat(1.0f, 0.0f, 0.0f, 0.0f),
		vec3(22.0f, 6.0f, 0.1f)
	), model, my_shader_id));

	my_children.push_back(new GameEntity(Transform(
		vec3(0.0f, 0.0f, 1.5f),
		quat(1.0f, 0.0f, 0.0f, 0.0f),
		vec3(22.0f, 6.f, 0.1f)
	), model, my_shader_id));
	*/

}
