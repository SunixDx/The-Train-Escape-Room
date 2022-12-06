#include "Seient.h"
#include "Vago.h"
#include "../Level.h"
#include "../graphics/Camera.h"
#include <iostream>

Seient::Seient(Transform transform, Model* model, GLuint shader_id): InteractableEntity(transform, nullptr, shader_id, InteractionType::SIT)
{
	btCollisionShape* groundShape_banc = new btBoxShape(btVector3(btScalar(.25), btScalar(.5), btScalar(.25)));
	btCollisionShape* groundShape_respatller = new btBoxShape(btVector3(btScalar(.001), btScalar(.5), btScalar(.25)));

	btTransform groundTransform_banc;
	groundTransform_banc.setIdentity();
	groundTransform_banc.setOrigin(btVector3(my_transform.position().x, my_transform.position().y, my_transform.position().z + Vago::Z_OFFSET));

	btTransform groundTransform_respatller;
	groundTransform_respatller.setIdentity();
	groundTransform_respatller.setOrigin(btVector3(my_transform.position().x, my_transform.position().y, my_transform.position().z + Vago::Z_OFFSET + 0.25));

	btScalar mass_banc(0.);
	btScalar mass_respatller(0.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	btVector3 localInertia_banc(0, 0, 0);
	if (mass_banc != 0.f)
		groundShape_banc->calculateLocalInertia(mass_banc, localInertia_banc);

	btVector3 localInertia_respatller(0, 0, 0);
	if (mass_respatller != 0.f)
		groundShape_respatller->calculateLocalInertia(mass_respatller, localInertia_respatller);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState_banc = new btDefaultMotionState(groundTransform_banc);
	btRigidBody::btRigidBodyConstructionInfo rbInfo_banc(mass_banc, myMotionState_banc, groundShape_banc, localInertia_banc);
	btRigidBody* body_banc = new btRigidBody(rbInfo_banc);

	btDefaultMotionState* myMotionState_respatller = new btDefaultMotionState(groundTransform_respatller);
	btRigidBody::btRigidBodyConstructionInfo rbInfo_respatller(mass_respatller, myMotionState_respatller, groundShape_respatller, localInertia_respatller);
	btRigidBody* body_respatller = new btRigidBody(rbInfo_respatller);

	body_banc->setUserPointer(this);
	my_rigid_body_banc = body_banc;

	body_respatller->setUserPointer(this);
	my_rigid_body_respatller = body_respatller;

	BulletWorld::WORLD->my_collision_shapes.push_back(groundShape_banc);
	BulletWorld::WORLD->my_dynamics_world->addRigidBody(body_banc);

	BulletWorld::WORLD->my_collision_shapes.push_back(groundShape_respatller);
	BulletWorld::WORLD->my_dynamics_world->addRigidBody(body_respatller);

	my_children.push_back(new GameEntity(Transform(
		vec3(0.0f, 0.0f, 0.0f),
		quat(1.0f, 0.0f, 0.0f, 0.0f),
		vec3(0.5f, 1.0f, 0.5f)
	), model, my_shader_id));


	my_children.push_back(new GameEntity(Transform(
		vec3(0.25f, 0.0f, 0.5f),
		quat(1.0f, 0.0f, 0.0f, 0.0f),
		vec3(0.02f, 1.0f, 0.5f)
	), model, my_shader_id));
}

void Seient::interact()
{
	Camera::MAIN_CAMERA.sitDown(this);
	Level::CURRENT_LEVEL.MaybeSpawnSlender();
}
