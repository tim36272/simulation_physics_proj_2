#include "../utilities/math/vec.hpp"
#include "../utilities/math/quaternion.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <GL/glut.h>
#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glu.h>			// Header File For The GLu32 Library
#include <vector>
#ifndef RB
#define RB
struct point {
	double x,y,z;
	point() {}
	point(double inI, double inJ, double inK) {x=inI;y=inJ;z=inK;}
};

class rigid_body
{
public:
    rigid_body ( vec p, double l,vec inLinearVelocity,vec inAngularVelocity );
    ~rigid_body();

    // state update/visualize equations
    void updateVelocity(double);
    void updatePosition(double);
		void updateRotation(double);
		void draw();

    // new collision detection
    bool colliding(const rigid_body& otherBody) const;
		bool isCollisionOnAxis(const vec &seperatingAxis, const std::vector<vec> axisVerticies,const std::vector<vec> otherVerticies,const Quaternion &rotation,const point &center);

    // collision reaction
    bool resolveIntersection(rigid_body& otherBody);
    bool resolveCollision(rigid_body& otherBody);
    bool collide(rigid_body& otherBody);
		void handleCollisions(rigid_body& otherBody);

    // body specific variables
    double edgeLength;
    bool collision;

    // Standard rigid body variables
    vec linearVelocity;
		vec angularVelocity;
		vec orientation;
		Quaternion rotationOrientation;
		point COM;
    double mass;
    double energy;
		double inverseMass;

		//collision members
		std::vector<vec> normals;
		std::vector<vec> verticies;

};
#endif
