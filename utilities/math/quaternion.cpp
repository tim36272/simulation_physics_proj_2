#include "quaternion.h"
#include <iostream>
// Operator =
/*Quaternion& Quaternion::operator= (Quaternion q)
{
	double x,y,z,a,b,c;
	this->v.get(x,y,z);
	q.v.get(a,b,c);
    this->w = q.w;
    x = a;
    y = b;
    z = c;
	this->v.set(x,y,z);
    return *this;
}*/

// Constructor
Quaternion::Quaternion (void)
{
this->w = 0;
	this->v.set(0,0,0);

}

// Parameterized Constructor
Quaternion::Quaternion(double e0, double e1, double e2, double e3)
{
	double x,y,z;
	this->w = e0;
	x = e1;
	y = e2;
	z = e3;
	double magnitude = this->w*this->w+x*x+y*y+z*z;
	if (magnitude!=1) {
		magnitude = sqrt(magnitude);
		this->w /= magnitude;
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
	this->v.set(x,y,z);		
}
/*Quaternion Quaternion::operator=(Quaternion& rhs) {
	double x,y,z;
	rhs.v.get(x,y,z);
	this->v.set(x,y,z);
	this->w = rhs.w;
	return *this;
}*/
Quaternion Quaternion::operator=(Quaternion rhs) {
	double x,y,z;
	rhs.v.get(x,y,z);
	this->v.set(x,y,z);
	this->w = rhs.w;
	return *this;
}

// equivalency operator

bool Quaternion::operator==(Quaternion& rhs) {
	double x,y,z,a,b,c;
	this->v.get(x,y,z);
	rhs.v.get(a,b,c);
	bool firstCheck = ((this->w == rhs.w) && (x==a) && (y==b) && (z==c));
	return firstCheck;
}

	

// constructor for angle and rotation axis
Quaternion::Quaternion(double angle,vec rotationAxis) {
	this->w = cos(angle/2.0);
	double x,y,z;
	rotationAxis.get(x,y,z);
	x = x*sin(angle/2.0);
	y = y*sin(angle/2.0);
	z = z*sin(angle/2.0);
	this->v.set(x,y,z);
}

//constructor for euler angles
Quaternion::Quaternion(double phi, double theta, double gamma ) {
	this->w = cos(phi/2.0)*cos(theta/2.0)*cos(gamma/2.0) + sin(phi/2.0)*sin(theta/2.0)*sin(gamma/2.0);
	double x,y,z;
	x = sin(phi/2.0)*cos(theta/2.0)*cos(gamma/2.0) - cos(phi/2.0)*sin(theta/2.0)*sin(gamma/2.0);
	y = cos(phi/2.0)*sin(theta/2.0)*cos(gamma/2.0) + sin(phi/2.0)*cos(theta/2.0)*sin(gamma/2.0);
	z = cos(phi/2.0)*cos(theta/2.0)*sin(gamma/2.0) - sin(phi/2.0)*sin(theta/2.0)*cos(gamma/2.0);
	this->v.set(x,y,z);
}

//constructor for rotation matrix
Quaternion::Quaternion(double inputMatrix[]) {
	this->w = sqrt(1+inputMatrix[0]+inputMatrix[4]+inputMatrix[8])/2.0;
	double x,y,z;
	x = (inputMatrix[7]-inputMatrix[5])/(4*this->w);
	y = (inputMatrix[2]-inputMatrix[6])/(4*this->w);
	z = (inputMatrix[3]-inputMatrix[1])/(4*this->w);
	this->v.set(x,y,z);
}

//set for euler angles
void Quaternion::set(double phi, double theta, double gamma ) {
	this->w = cos(phi/2.0)*cos(theta/2.0)*cos(gamma/2.0) + sin(phi/2.0)*sin(theta/2.0)*sin(gamma/2.0);
	double x,y,z;
	x = sin(phi/2.0)*cos(theta/2.0)*cos(gamma/2.0) - cos(phi/2.0)*sin(theta/2.0)*sin(gamma/2.0);
	y = cos(phi/2.0)*sin(theta/2.0)*cos(gamma/2.0) + sin(phi/2.0)*cos(theta/2.0)*sin(gamma/2.0);
	z = cos(phi/2.0)*cos(theta/2.0)*sin(gamma/2.0) - sin(phi/2.0)*sin(theta/2.0)*cos(gamma/2.0);
	this->v.set(x,y,z);
}

//set for rotation matrix
void Quaternion::setRotationMatrix(double inputMatrix[]) {
	this->w = sqrt(1+inputMatrix[0]+inputMatrix[4]+inputMatrix[8])/2.0;
	double x,y,z;
	x = (inputMatrix[7]-inputMatrix[5])/(4*this->w);
	y = (inputMatrix[2]-inputMatrix[6])/(4*this->w);
	z = (inputMatrix[3]-inputMatrix[1])/(4*this->w);
	this->v.set(x,y,z);
}

//get for euler angles
void Quaternion::get(double &phi, double &theta, double &gamma) {
	double x,y,z;
	this->v.get(x,y,z);
	phi = atan(2*(this->w*x+y*z)/(1-2*(x*x+y*y)));
	theta = atan(2*(this->w*y-z*x));
	gamma = atan(2*(this->w*z+x*y)/(1-2*(y*y+z*z)));
}

//get for rotation matrices
void Quaternion::getRotationMatrix(double params[])const  {
	double q1,q2,q3;
//cout <<"GRM min: "<<params<<" max: "<<&params[15]<<endl;
	this->v.get(q1,q2,q3);
	params[0] = (1-2*(q2*q2+q3*q3));
	params[4] = 2*(q1*q2-this->w*q3);
	params[8] = 2*(this->w*q2+q1*q3);
	params[1] = 2*(q1*q2+this->w*q3);
	params[5] = 1-2*(q1*q1+q3*q3);
	params[9] = 2*(q2*q3-this->w*q1);
	params[2] = 2*(q1*q3-this->w*q2);
	params[6] = 2*(this->w*q1+q2*q3);
	params[10] = 1-2*(q1*q1+q2*q2);
//	params[0]=params[5]=params[10]=params[15]=1;
//	params[1]=params[2]=params[3]=params[4]=params[6]=params[7]=params[8]=params[9]=params[11]=params[12]=params[13]=params[14]=0;
	params[3]=params[7]=params[11]=params[12]=params[13]=params[14]=0;
	params[15]=1;
}

void Quaternion::get(double params[]) {
	params[0] = this->w;
	double x,y,z;
	this->v.get(x,y,z);
	params[1] = x;
	params[2] = y;
	params[3] = z;
}

void Quaternion::set(double params[]) {
	this->w = params[0];
	this->v.set(params[1],params[2],params[3]);
}

// Calculate Magnitude
double Quaternion::Magnitude()
{
	double x,y,z;
	v.get(x,y,z);
	double mag = pow(this->w,2)+pow(x,2)+pow(y,2)+pow(z,2);
	mag = sqrt(mag);
	return mag;
}

// Get quaternion's vec component
vec Quaternion::Getvec()
{
	vec out;
	double x,y,z;
	v.get(x,y,z);
	out.set(x,y,z);
	return out;
}

// Get the quaternion's scalar component
double Quaternion::GetScalar()
{
return this->w;
}

void Quaternion::rectify() {
	double mag = magnitude();
	double x,y,z;
	v.get(x,y,z);
	w/=mag;
	x/=mag;
	y/=mag;
	z/=mag;
	v.set(x,y,z);
}

bool Quaternion::rectifyIfNeeded() {
//static int callCount=0;
//callCount++;
	double mag = magnitude();
//std::cout <<"mag: "<<mag-1.0<<std::endl;
	if (((mag-1.0)>=0.01) || ((mag-1.0)<=-0.01) ) {
//std::cout<<"Frames since last recify: "<<callCount<<std::endl;
//callCount=0;
		double x,y,z;
		v.get(x,y,z);
		w/=mag;
		x/=mag;
		y/=mag;
		z/=mag;
		v.set(x,y,z);
		return true;
	}
	return false;
}

double Quaternion::magnitude() {
	return sqrt(magnitudeSquared());
}

double Quaternion::magnitudeSquared() {
	double x,y,z;
	v.get(x,y,z);
	return x*x+y*y+z*z+w*w;
}

void Quaternion::makeRandom() {
	srand(time(NULL));
	double x,y,z;
	w = rand();
	x = rand();
	y = rand();
	z = rand();
	v.set(x,y,z);
	rectify();
}

vec Quaternion::rotateVec(vec input) {
	vec vn(input);
	// vn.normalize();
	Quaternion vecQuat, resQuat;
	vecQuat.v.x = vn.x;
	vecQuat.v.y = vn.y;
	vecQuat.v.z = vn.z;
	vecQuat.w = 0.0f;

	resQuat = ~vecQuat;
	resQuat = *this * resQuat;
	return (vec(resQuat.v.x,resQuat.v.y,resQuat.v.z));
}
Quaternion Quaternion::slerp(Quaternion first, Quaternion second, double param) {
	{
		double dotProduct = dot(first, second);
	
			double angle = acosf(dotProduct);
			return (first*sinf(angle*(1-param)) + second*sinf(angle*param))/sinf(angle);	
	}
}
// Operator +=
Quaternion Quaternion::operator +=(Quaternion q)
{
	double x,y,z,a,b,c;
	q.v.get(a,b,c);
	this->v.get(x,y,z);
	x+=a;
	y+=b;
	z+=c;
	this->w = q.w+this->w;
	this->v.set(x,y,z);

return *this;

}

// Operator -=
Quaternion Quaternion::operator -=(Quaternion q)
{
	double x,y,z,a,b,c;
	q.v.get(a,b,c);
	this->v.get(x,y,z);
        this->w = this->w-q.w;
        x = x-a;
        y = y-b;
        z = z-c;
return *this;
}

// Operator *=
Quaternion Quaternion::operator *=(double s )
{
	double x,y,z;
	this->v.get(x,y,z);
        this->w *= s;
        x *= s;
        y *= s;
        z *= s;
	this->v.set(x,y,z);
return *this;
}

// Operator /=
Quaternion Quaternion::operator /=(double s )
{
	double x,y,z;
	this->v.get(x,y,z);
        this->w /= s;
        x /= s;
        y /= s;
        z /= s;
	this->v.set(x,y,z);
return *this;
}


Quaternion operator+ (Quaternion q1, Quaternion q2)
{
	double x,y,z,a,b,c;
	q2.v.get(x,y,z);
	q1.v.get(a,b,c);
	Quaternion out ( q1.w+q2.w, a+x , b+y , c+z );
	return out;
}

Quaternion operator- (Quaternion q1, Quaternion q2)
{
	double x,y,z,a,b,c;
	q1.v.get(a,b,c);
	q2.v.get(x,y,z);
Quaternion out (q1.w-q2.w,a-x,b-y,c-z);
return out;    
}

Quaternion operator *(Quaternion q1, Quaternion q2)
{
	Quaternion out;
	out.w = q1.w*q2.w - q1.v.dot(q2.v);
	out.v.x = q1.v.x*q2.w + q1.w*q2.v.x + q1.v.y*q2.v.z - q1.v.x*q2.v.y;
	out.v.y = q1.w*q2.v.y - q1.v.x*q2.v.z + q1.v.y*q2.w + q1.v.z*q2.v.x;
	out.v.z = q1.w*q2.v.z + q1.v.x*q2.v.y - q1.v.y*q2.v.x + q1.v.z*q2.w;
	return out;
}

Quaternion operator* (Quaternion q, double s)
{
	double x,y,z;
	q.v.get(x,y,z);
	Quaternion out;
	out.w *= s;
	x *= s;
	y *= s;
	z *= s;
	out.v.set(x,y,z);
	return out;    
}

Quaternion operator* (double s, Quaternion q)
{
	double a,b,c;
	q.v.get(a,b,c);
   Quaternion out;
        out.w = q.w*s;
        a = a*s;
        b = b*s;
        c = c*s;
	out.v.set(a,b,c);
        return out;
}

Quaternion operator/ (Quaternion q, double s)
{
	double x,y,z;
	q.v.get(x,y,z);
	Quaternion out;
        out.w = q.w/s;
        x = x/s;
        y = y/s;
        z = z/s;
	out.v.set(x,y,z);
        return out; 
}

Quaternion operator * (Quaternion qIn, vec vIn) {
	double q0,q1,q2,q3,v1,v2,v3;
	q0 = qIn.w;
	qIn.v.get(q1,q2,q3);
	vIn.get(v1,v2,v3);
	Quaternion out(-(q1*v1+q2*v2+q3*v3), q0*v1+q3*v2-q2*v3 , q0*v2+q1*v3-q3*v1 , q0*v3+q2*v1-q1*v2);
	return out;	
}

Quaternion operator * (vec vIn, Quaternion qIn)
{
	double q0,q1,q2,q3,v1,v2,v3;
	q0 = qIn.w;
	qIn.v.get(q1,q2,q3);
	vIn.get(v1,v2,v3);
	Quaternion out(-(q1*v1+q2*v2+q3*v3), q0*v1+q3*v2-q2*v3 , q0*v2+q1*v3-q3*v1 , q0*v3+q2*v1-q1*v2);
	return out;	
}

Quaternion Quaternion::operator ~ () {
	double x,y,z;
	this->v.get(x,y,z);
	Quaternion out(double(this->w),-x,-y,-z);
	return out;
}
