#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include "../src/stdafx.h"

class BulletWorld {
public:
	BulletWorld();
	void* rayCast(glm::vec3 origin, glm::vec3 direction, float distance);

	btDiscreteDynamicsWorld* my_dynamics_world;
	btAlignedObjectArray<btCollisionShape*> my_collision_shapes;
	static BulletWorld* WORLD;
};