#include "BulletWorld.h"

#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1, 20);


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

void BulletWorld::simulate(btScalar timeStep)
{
	my_dynamics_world->stepSimulation(timeStep);
}

void BulletWorld::performCollisionDetection()
{
	my_dynamics_world->performDiscreteCollisionDetection();
}

std::tuple<bool, btVector3> BulletWorld::testCollision(btRigidBody* rigid_body)
{
	bool colision = false;
	btVector3 direction(0.0f, 0.0f, 0.0f);
	struct rCallBack : public btCollisionWorld::ContactResultCallback
	{
		bool* has_colided;
		btVector3* colision_direction;

		rCallBack(bool* colision, btVector3* direction)
		{
			has_colided = colision;
			colision_direction = direction;
		}

		virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
		{
			btVector3 ptA = cp.getPositionWorldOnA();
			btVector3 ptB = cp.getPositionWorldOnB();

			int d20_roll = distribution(generator);
			std::cout << "COLISION " << d20_roll << std::endl;
			std::cout << "ptA (" << ptA.x() << ", " << ptA.y() << ", " << ptA.z()  <<")" << std::endl;
			std::cout << "ptB (" << ptB.x() << ", " << ptB.y() << ", " << ptB.z() << ")" << std::endl;
			*has_colided = true;
			*colision_direction = ptB - ptA;
			return 1;
		}
	};

	struct rCallBack resultCallback(&colision, &direction);

	my_dynamics_world->contactTest(rigid_body, resultCallback);

	return std::make_tuple(colision, direction);
}