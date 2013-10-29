#include "rigid_body.h"
#include <iostream>
using namespace std;

vec operator+(vec lhs, point rhs) {
	vec out;
	out.x = lhs.x+rhs.x;
	out.y = lhs.y+rhs.y;
	out.z = lhs.z+rhs.z;
	return out;
}
inline ostream& operator<<(ostream &out,point data) {
	out<<"("<<data.x<<","<<data.y<<","<<data.z<<")";
	return out;
}
rigid_body::rigid_body ( vec p, double l,vec inLinearVelocity,vec inAngularVelocity )
{
    COM.x = p.x;
    COM.y = p.y;
    COM.z = p.z;
    edgeLength = l;
    collision = false;
		linearVelocity = inLinearVelocity;
		angularVelocity = inAngularVelocity;

    mass = l ;
		inverseMass = 1/l;
    energy = mass * COM.y * (9.81)+(0.5*mass*linearVelocity.x)+(0.5*mass*linearVelocity.y)+(0.5*mass*linearVelocity.z);
		double params[4];
		params[0]=1.0;
		params[1]=params[2]=params[3]=0.0;
		rotationOrientation.set(params);
		orientation = 0;

		//setup collision members
		normals.push_back(vec(1,0,0));
		normals.push_back(vec(0,1,0));
		normals.push_back(vec(0,0,1));

		//order is:
			//0: SE close
			//1: SE far
			//2: NE far
			//3: NE close
			//4: SW close
			//5: SW far
			//6: NW far
			//7: NW close
		
		verticies.push_back(vec(edgeLength/2.0, -edgeLength/2.0,-edgeLength/2.0));
		verticies.push_back(vec(edgeLength/2.0, -edgeLength/2.0, edgeLength/2.0));
		verticies.push_back(vec(edgeLength/2.0,  edgeLength/2.0, edgeLength/2.0));
		verticies.push_back(vec(edgeLength/2.0,  edgeLength/2.0,-edgeLength/2.0));
		verticies.push_back(vec(-edgeLength/2.0,-edgeLength/2.0,-edgeLength/2.0));
		verticies.push_back(vec(-edgeLength/2.0,-edgeLength/2.0, edgeLength/2.0));
		verticies.push_back(vec(-edgeLength/2.0, edgeLength/2.0, edgeLength/2.0));
		verticies.push_back(vec(-edgeLength/2.0, edgeLength/2.0,-edgeLength/2.0));


}

rigid_body::~rigid_body()
{
}

void rigid_body::draw()
{
//		static double callCount=0;
//		callCount+=0.1;
//		glRotatef(callCount,angularVelocity.x,angularVelocity.y,angularVelocity.z);
		glTranslatef(COM.x,COM.y,COM.z);
		double params[16];
		rotationOrientation.getRotationMatrix(params);
		glMultMatrixd(params);
		glutSolidCube(edgeLength);

		//draw orientation vectors
		glBegin(GL_LINES);
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(5.0f,0.0f,0.0f);

			glColor3f(0.5f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(-5.0f,0.0f,0.0f);

			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,5.0f,0.0f);

			glColor3f(0.0f,0.5f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,-5.0f,0.0f);

			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,5.0f);

			glColor3f(0.0f,0.0f,0.5f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,-5.0f);
		glEnd();
}
void rigid_body::updateVelocity(double delta_time)
{
    linearVelocity.y += delta_time * (-9.81);

}

void rigid_body::updatePosition (double delta_time)
{
//		updateRotation(delta_time);

    if (COM.y <=0.0)
    {
//        energy *= 0.8;
        COM.y = 0;
        linearVelocity.y = sqrt ( 2.0* energy/mass);
    }
    COM.y+= (linearVelocity.y * delta_time);
		COM.x += (linearVelocity.x * delta_time);
		COM.z += (linearVelocity.z * delta_time);

}

//for rotating the box
void rigid_body::updateRotation (double delta_time)
{
		Quaternion rotation;
		orientation.x = angularVelocity.x*delta_time;
		orientation.y = angularVelocity.y*delta_time;
		orientation.z = angularVelocity.z*delta_time;
		rotation.set(orientation.x,orientation.y,orientation.z);
		rotationOrientation = (rotationOrientation * rotation);
		rotationOrientation.rectifyIfNeeded();
}

// Collision Response
//upon returning from this function, bool rigid_body::collision will be set for *this, not otherBody
void rigid_body::handleCollisions(rigid_body& otherBody)
{
//cout <<"in collision checking"<<endl;
//cout <<"normals size: "<<normals.size()<<endl;
		//loop through seperating axis of *this and find extrema on each axis
		for (unsigned int i=0;i<normals.size();i++) {
			//rigid_body::collision = ask if there is a collision with the choosen axis and extrema with any axis of otherBody(loop on axis of otherBody)
cout <<"normal: "<<i<<endl;
			this->collision = this->isCollisionOnAxis(this->normals[i],this->verticies,otherBody.verticies,rotationOrientation,otherBody.COM);
			//break if there was no this->collision
			if (!collision)
				break;
		}
}

bool rigid_body::isCollisionOnAxis(const vec &seperatingAxisIn, const std::vector<vec> axisVerticiesIn, const std::vector<vec> otherVerticiesIn,const Quaternion &rotation,const point &center)
{
		std::vector<vec> axisVerticies  = axisVerticiesIn;
		std::vector<vec> otherVerticies = otherVerticiesIn;
//cout<<"way intro seperating axis: ("<<seperatingAxisIn.x<<","<<seperatingAxisIn.y<<","<<seperatingAxisIn.z<<")"<<endl;
//cout <<"ICOA input data: SA: "<<seperatingAxis<<" center: "<<COM<<endl;
		double axisMax,axisMin;
		vec seperatingAxis(seperatingAxisIn);
		double rotationMatrix[16];
//cout<<"intro seperating axis: ("<<seperatingAxis.x<<","<<seperatingAxis.y<<","<<seperatingAxis.z<<")"<<endl;

//		std::vector<vec> firstObjectAxis;
		rotation.getRotationMatrix(rotationMatrix);
//cout<<"intro2 seperating axis: ("<<&seperatingAxis.x<<","<<&seperatingAxis.y<<","<<&seperatingAxis.z<<")"<<endl;
		seperatingAxis = seperatingAxis.rotateByMatrix(rotationMatrix);
//cout<<"rotate seperating axis: ("<<seperatingAxis.x<<","<<seperatingAxis.y<<","<<seperatingAxis.z<<")"<<endl;
//cout <<"SA: rot"<<seperatingAxis<<endl;

		axisVerticies[0] = (axisVerticies[0].rotateByMatrix(rotationMatrix))+this->COM;
//cout<<"first lhs vertex: ("<<axisVerticies[0].x<<","<<axisVerticies[0].y<<","<<axisVerticies[0].z<<")"<<endl;
		axisMin=axisMax=seperatingAxis.dot(axisVerticies[0]); // be sure to get valid data
		vector<double> projectedOtherVerticies;
//cout <<"First currentValue: "<<axisMin<<endl;
		otherVerticies[0] = otherVerticies[0].rotateByMatrix(rotationMatrix)+center;
/*		glPushMatrix();
//cout <<"other verticies: "<<otherVerticies[0].x<<","<<otherVerticies[0].y<<","<<otherVerticies[0].z<<endl;
		glTranslatef(otherVerticies[0].x,otherVerticies[0].y,otherVerticies[0].z);
//		glTranslatef(0,0,0);
		glColor3f(0,0,1);
		glutSolidSphere(0.1,32,32);
		glPopMatrix();*/
//cout<<"first rhs vertex: ("<<otherVerticies[0].x<<","<<otherVerticies[0].y<<","<<otherVerticies[0].z<<")"<<endl;
//cout<<"seperating axis: ("<<seperatingAxis.x<<","<<seperatingAxis.y<<","<<seperatingAxis.z<<")"<<endl;
		double currentValue = seperatingAxis.dot(otherVerticies[0]); // this makes it all slightly more efficient, notice the i=1 below
//cout <<"dot product: "<<currentValue<<endl;
		projectedOtherVerticies.push_back(currentValue);
		for (unsigned int i=1;i<axisVerticies.size();i++) {
//			axisVerticies[i] = axisVerticies[i].rotateByMatrix(rotationMatrix); // used to find min and max on the axis
			currentValue = seperatingAxis.dot(axisVerticies[i].rotateByMatrix(rotationMatrix)+this->COM);
//cout <<"at loop: "<<i<<" currentVal: "<<currentValue<<endl;
			if (currentValue >axisMax)
				axisMax = currentValue;
			else if (currentValue < axisMin)
				axisMin = currentValue;
			projectedOtherVerticies.push_back(seperatingAxis.dot(otherVerticies[i].rotateByMatrix(rotationMatrix)+center));
/*		glPushMatrix();
		glTranslatef((otherVerticies[i].rotateByMatrix(rotationMatrix)+center).x,(otherVerticies[i].rotateByMatrix(rotationMatrix)+center).y,(otherVerticies[i].rotateByMatrix(rotationMatrix)+center).z);
//		glTranslatef(0,0,0);
		glColor3f(0,0,1);
		glutSolidSphere(0.1,32,32);
		glPopMatrix();*/
		}

//cout<<"Max: "<<axisMax<<" Min: "<<axisMin<<endl;
for (unsigned int i=0;i<projectedOtherVerticies.size();i++) {
//	cout<<"projection "<<i<<": "<<projectedOtherVerticies[i]<<endl;
	if(projectedOtherVerticies[i]>=axisMin && projectedOtherVerticies[i]<=axisMax) {
//cout <<"collision detected"<<endl;;
//char dummy;
//cin >>dummy;
		return true;
	}

}
//cout <<"no collision detected"<<endl;
	return false;
}

bool rigid_body::colliding(const rigid_body& otherBody) const
{
    // delta vector

    // radius sum

    // square distance

    // square distance > radius squared. no collision

    // find the mtd (or the amount of intersection along the delta vector).

    return true;
}

bool rigid_body::resolveIntersection(rigid_body& otherBody)
{
    // inverse mass quantities

    // resolve intersection

    return true;
}

bool rigid_body::resolveCollision(rigid_body& otherBody)
{

    // inverse mass quantities

    // impact speed

    //normal velocity

    // sphere intersecting but moving away from each other already

    // collision impulse

    // change in momentum

    return true;
}

bool rigid_body::collide(rigid_body& otherBody)
{
    // normal and mtd declarations

    // if colliding, return false

    // calculate normal, and normalize

    // resolve intersections and collisions

    return true;
}
