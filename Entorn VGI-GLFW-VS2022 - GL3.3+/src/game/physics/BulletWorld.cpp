#include "BulletWorld.h"

#include <iostream>

BulletWorld* BulletWorld::WORLD = nullptr;

BulletWorld::BulletWorld()
{
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	my_dynamics_world = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

}

void* BulletWorld::rayCast(glm::vec3 origin, glm::vec3 direction, float distance)
{
	glm::vec3 end = origin + direction * distance;

	btCollisionWorld::ClosestRayResultCallback RayCallback(
		btVector3(origin.x, origin.y, origin.z),
		btVector3(end.x, end.y, end.z)
	);
	BulletWorld::WORLD->my_dynamics_world->rayTest(
		btVector3(origin.x, origin.y, origin.z),
		btVector3(end.x, end.y, end.z),
		RayCallback
	);

	if (RayCallback.hasHit()) {
		return RayCallback.m_collisionObject->getUserPointer();
	}
	else {
		return nullptr;
	}
}

void BulletWorld::performCollisionDetection()
{
	my_dynamics_world->performDiscreteCollisionDetection();
}

bool BulletWorld::testCollision(btRigidBody* rigid_body)
{
	struct rCallBack : public btCollisionWorld::ContactResultCallback
	{
		virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
		{
			btVector3 ptA = cp.getPositionWorldOnA();
			btVector3 ptB = cp.getPositionWorldOnB();
			std::cout << "COLISION" << std::endl;
			return 0;
		}
	};

	struct rCallBack resultCallback;

	my_dynamics_world->contactTest(rigid_body, resultCallback);

	int numManifolds = my_dynamics_world->getDispatcher()->getNumManifolds();
	if (numManifolds > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}