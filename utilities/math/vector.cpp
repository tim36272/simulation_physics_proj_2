#include "vector.h"
#define CARTESIAN 3

vector::vector() {
	mode = CARTESIAN;
	data = new float[3];
	(*this)=0;
}
vector::vector(float x, float y, float z) {
	mode = CARTESIAN;
	data = new float[3];
	data[X] = x;
	data[Y] = y;
	data[Z] = z;
}
vector::vector (const vector& rhs) {
	mode = CARTESIAN;
	data = new float[3];
	for (int i=0;i<mode;i++) {
		data[i] = (rhs.data)[i];
	}
}
vector vector::operator = (const vector &rhs) {
	if ((&rhs)!=this) {
		for (int i=0;i<mode;i++) {
		data[i] = (rhs.data)[i];
		}
	}
return *this;
}

float vector::operator = (const float rhs) {
	for (int i=0;i<mode;i++) {
		data[i] = (rhs);
	}
return rhs;
}
/*bool operator == (const vector rhs) {
	float comparison=0;
	for (int i=0;i<mode;i++) {
		comparison+=(data[i]-(rhs.data[i]));
	}
	return (comparison == 0.0);
}*/
vector vector::operator + (const vector &rhs) {
	float x,y,z;
	x = data[0]+rhs.data[0];
	y = data[1]+rhs.data[1];
	z = data[2]+rhs.data[2];
	vector dummy(x,y,z);
	return dummy;
}
vector vector::operator / (const float factor) {
	float x,y,z;
	x = data[0]/factor;
	y = data[1]/factor;
	z = data[2]/factor;
	vector dummy(x,y,z);
	return dummy;
}
vector vector::operator - (const vector &rhs) {
	float x,y,z;
	x = data[0]-rhs.data[0];
	y = data[1]-rhs.data[1];
	z = data[2]-rhs.data[2];
	vector dummy(x,y,z);
	return dummy;
}
vector vector::operator * (const float factor) {
	float x,y,z;
	x = data[0]*factor;
	y = data[1]*factor;
	z = data[2]*factor;
	vector dummy(x,y,z);
	return dummy;
}
void vector::set(float x, float y, float z) {
	data[X] = x;
	data[Y] = y;
	data[Z] = z;
}
void vector::get(float& x, float& y, float& z) {
	x = data[X];
	y = data[Y];
	z = data[Z];
}
void vector::randomVector(int xMin, int xMax, int yMin, int yMax, int zMin, int zMax) {
	int xVal = randNum(xMin,xMax);
	int yVal = randNum(yMin,yMax);
	int zVal = randNum(zMin,zMax);
	data[X] = xVal;
	data[Y] = yVal;
	data[Z] = zVal;
}
void vector::randomUnitVector() {
	randomVector(-100,100,-100,100,-100,100);
	normalize();
}
float vector::magnitude() {
	return sqrt(magnitudeSquared());
}
float vector::magnitudeSquared() {
	float magnitude = 0;
	for (int i=0;i<mode;i++) {
		magnitude+=pow(data[i],2);
	}
	return magnitude;
}
void vector::normalize() {
	float calcMagnitude = magnitude();
	for (int i=0;i<mode;i++) {
		data[i] = (data[i]/calcMagnitude);
	}
}
float vector::distance(const vector &rhs) {
	return sqrt(distanceSquared(rhs));	
}
float vector::distanceSquared(const vector &rhs) {
	vector distanceVector(rhs.data[X] - data[X],rhs.data[Y] - data[Y],rhs.data[Z] - data[Z]);
	return distanceVector.magnitudeSquared();
}
vector vector::linearInterpolation(const vector &rhs, float interpolation) {
	float innerX = data[X]-rhs.data[X];
	float innerY = data[Y]-rhs.data[Y];
	float innerZ = data[Z]-rhs.data[Z];
	vector interpolatedVector(data[X]+(innerX*interpolation),
								 data[Y]+(innerY*interpolation),data[Z]+(innerZ*interpolation));
	return interpolatedVector;
	
}
vector vector::crossProduct(const vector &rhs) {
	vector crossProduct;
	if (mode==CARTESIAN) {
		crossProduct.data[X] = data[Y]*rhs.data[Z]-rhs.data[Y]*data[Z];
		crossProduct.data[Y] = data[X]*rhs.data[Z]-rhs.data[X]*data[Z];
		crossProduct.data[Z] = data[X]*rhs.data[Y]-rhs.data[X]*data[Y];
	}
	return crossProduct;
}
float vector::dotProduct(const vector &rhs) {
	float dotProduct;
	for (int i=0;i<mode;i++) {
		dotProduct+=data[i]*rhs.data[i];
	}
	return dotProduct;
}
vector::~vector() {
	delete[] data;
}
