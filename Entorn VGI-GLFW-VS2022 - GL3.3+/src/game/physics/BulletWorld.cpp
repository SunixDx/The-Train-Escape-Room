#include "BulletWorld.h"

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
