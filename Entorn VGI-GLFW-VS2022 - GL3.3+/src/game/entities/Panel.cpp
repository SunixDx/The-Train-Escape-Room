#include "Panel.h"
#include "../graphics/Camera.h"
#include "../ui/InteractionIndicator.h"
#include "../Level.h"


Panel::Panel(Transform transform, Model* model, GLuint shader_id) : InteractableEntity(transform, model, shader_id, InteractionType::CLOSE_UP)
{
	zoom = false;

	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(.1), btScalar(.15), btScalar(.1))); //definir collider

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


	for (int i = 0; i < display_digits.size(); i++)
	{
		auto tr = Transform();
		tr.scale(1.0f / 2.0f);
		tr.rotate(PI / 2, {0, 1, 0});
		tr.rotate(PI, { 0, 1, 0 });
		float offset = (float) i / 2.5f;

		tr.translate({0.025, 1.05, -0.2 - offset});
		auto digit = new GameEntity(tr, nullptr, shader_id);
		display_digits[i] = digit;
		addChild(digit);
	}
}

void Panel::interact()
{
	cout << "soy el panel" << endl;

	Camera::MAIN_CAMERA.zoomIn(my_transform);
	//zoom = true;

	InteractionIndicator::instance.change_indicator(InteractionType::NONE);

}

InteractionType Panel::interaction_type() const
{
	if (!zoom)
	{
		return my_interaction_type;
	}
	else
	{
		return InteractionType::NONE;
	}
}
