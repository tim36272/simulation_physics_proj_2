#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <ostream>
#include <iostream>
#ifndef utilities_math_vec
#define utilities_math_vec
using namespace std;

class vec
{
public:
    vec ()
    {
        x = 0;
        y = 0;
        z = 0;
    }
		vec (const vec &rhs) {
//cout<<"vector constructor"<<endl;
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		}
    vec (double px, double py, double pz)
    {
        x = px;
        y = py;
        z = pz;
    }
    ~vec() {}

    void normalize()
    {
        double m = sqrt (x*x + y*y + z*z);
        x /= m;
        y /= m;
        z /= m;

    }

    inline vec& operator += (vec u )
    {
        x += u.x;
        y += u.y;
        z += u.z;
				return *this;
    }
    inline vec& operator + (vec u )
    {
        x += u.x;
        y += u.y;
        z += u.z;
				return *this;
    }
/*    inline vec& operator * (double input )
    {
		    vec out;
				out.x = x*input;
				out.y = y*input;
				out.z = z*input;
				return out;
    }*/	
    inline vec& operator -= (vec u )
    {
        x -= u.x;
        y -= u.y;
        z -= u.z;
				return *this;
    }
		inline vec& operator=(int input) {
			x=input;
			y=input;
			z=input;
			return *this;
		}
		inline vec& operator=(const vec &rhs) {
//cout<<"in assignment vector: ";
			x=rhs.x;
			y=rhs.y;
			z=rhs.z;
			return *this;
		}
		inline void set(double inX,double inY,double inZ) {
			x=inX;
			y=inY;
			z=inZ;
		}
		inline void get(double &inX,double &inY,double &inZ) const {
			inX=x;
			inY=y;
			inZ=z;
		}
		inline vec crossProduct(const vec &rhs) {
			vec crossProduct;
				crossProduct.x = y*rhs.z-rhs.y*z;
				crossProduct.y = x*rhs.z-rhs.x*z;
				crossProduct.z = x*rhs.y-rhs.x*y;
			return crossProduct;
		}
		inline double dot (const vec &rhs)
		{
				double newX, newY, newZ;
				newX = x*rhs.x;
				newY = y*rhs.y;
				newZ = z*rhs.z;
				return (newX+newY+newZ);
		}
		inline vec rotateByMatrix(double const params[15]) {
			vec out;
//cout <<"this vector: "<<x<<","<<y<<","<<z<<endl;
//cout<<"Matrix:"<<endl;
//cout<<"|"<<params[0]<<" "<<params[1]<<" "<<params[2]<<"|"<<endl;
//cout<<"|"<<params[4]<<" "<<params[5]<<" "<<params[6]<<"|"<<endl;
//cout<<"|"<<params[8]<<" "<<params[9]<<" "<<params[10]<<"|"<<endl;

			out.x = params[0]*this->x+params[1]*this->y+params[2]*this->z;
//cout<<"got x: "<<out.x;
			out.y = params[4]*this->x+params[5]*this->y+params[6]*this->z;
//cout<<" y: "<<out.y;
			out.z = params[8]*this->x+params[9]*this->y+params[10]*this->z;
//cout<<" z: "<<out.z<<endl;
			return out;
		}

    double x, y,z;
};

inline ostream& operator<<(ostream &out,vec data) {
	out<<"("<<data.x<<","<<data.y<<","<<data.z<<")";
	return out;
}

// overloaded operators
inline vec operator- (vec u, vec v)
{
    return vec(u.x - v.x, u.y - v.y, u.z - v.z);
}
inline vec operator* (double s, vec u)
{
    return vec (u.x*s, u.y*s, u.z*s);
}
inline vec operator* (vec u, double s)
{
    return vec (u.x*s, u.y*s, u.z*s);
}
inline vec operator/ (vec u, double s)
{
    return vec(u.x/s, u.y/s, u.z/s);
}
#endif
