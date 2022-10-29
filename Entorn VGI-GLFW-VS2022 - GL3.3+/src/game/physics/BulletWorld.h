#include <bullet/btBulletDynamicsCommon.h>

class BulletWorld {
public:
	BulletWorld();

	btDiscreteDynamicsWorld* my_dynamics_world;
	btAlignedObjectArray<btCollisionShape*> my_collision_shapes;
	static BulletWorld* WORLD;
};