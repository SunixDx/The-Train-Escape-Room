#include "Camera.h"
#include "../physics/BulletWorld.h"
#include "../Level.h"
#include <bullet/btBulletDynamicsCommon.h>

Camera Camera::MAIN_CAMERA;
Camera Camera::SAVE_CAMERA;

void Camera::setupColliders()
{
	//btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(.4), btScalar(.5), btScalar(.35)));
	btCollisionShape* groundShape = new btCylinderShapeZ(btVector3(btScalar(.1), btScalar(.1), btScalar(4)));

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(position.x, position.y, position.z));

	btScalar mass(1.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	
	/*
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		groundShape->calculateLocalInertia(mass, localInertia);
	*/

	btVector3 localInertia(0, 0, 0);
	//groundShape->calculateLocalInertia(mass, localInertia);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	body->setGravity(btVector3(0, 0, 0));

	body->setUserPointer(this);
	my_rigid_body = body;

	BulletWorld::WORLD->my_collision_shapes.push_back(groundShape);
	BulletWorld::WORLD->my_dynamics_world->addRigidBody(body);
}

void Camera::syncColliders()
{
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(position.x, position.y, position.z));

	my_rigid_body->setWorldTransform(groundTransform);
	my_rigid_body->getMotionState()->setWorldTransform(groundTransform);
}
void Camera::sitDown(const Seient* seient)
{
	if (!sit)
	{
		SAVE_CAMERA = MAIN_CAMERA;
		MAIN_CAMERA.sit = true;
	}

	MAIN_CAMERA.position.x = seient->my_transform.position().x;
	MAIN_CAMERA.position.y = seient->my_transform.position().y;
	MAIN_CAMERA.position.z = 1.25;
	//TODO angle things

	my_rigid_body->setCollisionFlags(my_rigid_body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

void Camera::standUp()
{
	SAVE_CAMERA.horizontal_angle = MAIN_CAMERA.horizontal_angle;
	SAVE_CAMERA.vertical_angle = MAIN_CAMERA.vertical_angle;


	MAIN_CAMERA = SAVE_CAMERA;
	MAIN_CAMERA.sit = false;
	
	Level::CURRENT_LEVEL.despawnSlender();
	syncColliders();

	my_rigid_body->setCollisionFlags(my_rigid_body->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

void Camera::fly()
{
	if (!flying)
	{
		SAVE_CAMERA = MAIN_CAMERA;

		MAIN_CAMERA.flying = true;
		MAIN_CAMERA.horizontal_angle = 0;
		MAIN_CAMERA.vertical_angle = 0-(PI/4);
		MAIN_CAMERA.position.x = 0-MAIN_CAMERA.flying_radius;
		MAIN_CAMERA.position.y = 0;
		MAIN_CAMERA.position.z = MAIN_CAMERA.flying_radius;
	}
}

void Camera::enterTrain()
{
	if (flying)
	{
		MAIN_CAMERA = SAVE_CAMERA;
		MAIN_CAMERA.flying = false;
	}
}

void Camera::fly_arround(glm::vec3 center)
{
	MAIN_CAMERA.position.x = 0 - (cos(MAIN_CAMERA.horizontal_angle) * MAIN_CAMERA.flying_radius) + center.x;
	MAIN_CAMERA.position.y = 0 - (sin(MAIN_CAMERA.horizontal_angle) * MAIN_CAMERA.flying_radius) + center.y;
}

void Camera::fly_behind()
{
	MAIN_CAMERA.endcam = true;
	MAIN_CAMERA.flying = true;

	MAIN_CAMERA.horizontal_angle = 0;
	MAIN_CAMERA.vertical_angle = 0 - (PI / 10);
	MAIN_CAMERA.position.x = 15 - MAIN_CAMERA.flying_radius;
	MAIN_CAMERA.position.y = 0;
	MAIN_CAMERA.position.z = MAIN_CAMERA.flying_radius/2;
}

void Camera::zoomIn(Transform trans)
{
	if (!zoom)
	{
		SAVE_CAMERA = MAIN_CAMERA;
		MAIN_CAMERA.zoom = true;
	}

	MAIN_CAMERA.position.x = trans.position().x - 0.35;
	MAIN_CAMERA.position.y = trans.position().y;
	MAIN_CAMERA.position.z = trans.position().z;

	MAIN_CAMERA.horizontal_angle = 0;
	MAIN_CAMERA.vertical_angle = 0;
	
}

void Camera::zoomOut()
{
	SAVE_CAMERA.horizontal_angle = MAIN_CAMERA.horizontal_angle;
	SAVE_CAMERA.vertical_angle = MAIN_CAMERA.vertical_angle;


	MAIN_CAMERA = SAVE_CAMERA;
	MAIN_CAMERA.zoom = false;
}



/*
void show_cam_vectors()
{
	glm::vec3 direction(
		cos(vertical_angle) * cos(horizontal_angle),
		sin(horizontal_angle),
		sin(vertical_angle)
	);

	glm::vec3 left = glm::vec3(
		cos(horizontal_angle + PI / 2),
		sin(horizontal_angle + PI / 2),
		0
	);

	glm::vec3 up = glm::cross(direction, left);

	cout << "DIRECTION:" << std::endl;
	cout << "x " << direction[0] << ", y " << direction[1] << ", z " << direction[2] << endl;
	cout << "RIGHT:" << std::endl;
	cout << "x " << left[0] << ", y " << left[1] << ", z " << left[2] << endl;
	cout << "UP:" << std::endl;
	cout << "x " << up[0] << ", y " << up[1] << ", z " << up[2] << endl;
}
*/