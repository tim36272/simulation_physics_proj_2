#include "../../simulation/rigid_body.h"

namespace col {
	colliding(const rigid_body &lhs, const rigid_body &rhs) {
		bool isCollision=true;
		for (int i=0;i<3;i++) {
			for (int j=0;j<3;j++) {
				isCollision = checkCollisionOnAxis(lhs.normals[
			}
		}
	}
}
