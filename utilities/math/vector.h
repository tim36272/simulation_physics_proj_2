/**
 * @file  vector.h
 * @brief <b>A Class for Vector Creation and Manipulation</b>
 * 
 * @author  Gamino/Sweet
 * @ingroup utilities - math
 */  
#ifndef VECTOR
#define VECTOR
#include <cmath>
#include "vmath.h"
#define X 0
#define Y 1
#define Z 2

class vector {
	public:
		float *data;
		
		// this is used to make the object generic for different coordinate systems. 
		// It is synonymous with the number of components in that system 
		// (ie in cartesian, mode==3
		int mode; 
		/*-------------------------------------------------------------------------
		Purpose: constructor
		Action: creates a vector object with values (0,0,0)
		parameters: none
		*/
		vector();
		/*-------------------------------------------------------------------------
		Purpose: constructor
		Action: creates a vector object with values (x,y,z)
		parameters: floats x,y,z: the vector components
		*/
		vector(float x, float y, float z);
		/*-------------------------------------------------------------------------
		Purpose: copy constructor
		Action: obvious
		parameters: the object to be coppied
		*/
		vector(const vector& rhs);
		/*-------------------------------------------------------------------------
		Purpose: destructor
		Action: obvious
		parameters: none
		*/
		~vector();
		/*-------------------------------------------------------------------------
		Purpose: assignment operator
		Action: coppies the values from rhs to *this
		parameters: the object to be coppied
		returns: this, AKA the left side of the assignment
		*/
		vector operator = (const vector &rhs);
		/*-------------------------------------------------------------------------
		Purpose: addition operator
		Action: adds the component values of rhs to *this and stores them in *this
		parameters: the object to be added from
		returns: this, AKA the left side of the addition
		*/
		vector operator + (const vector &rhs);
		/*-------------------------------------------------------------------------
		Purpose: division operator
		Action: divides the vector by a scalar
		parameters: the scalar divisor
		returns: this, AKA the result side of the division
		*/
		vector operator / (const float factor);
		/*-------------------------------------------------------------------------
		Purpose: subtraction operator
		Action: subtracts the component values of rhs to *this and stores them in 
						*this
		parameters: the object to be subtracted
		returns: self, AKA the left side of the subtraction
		*/
		vector operator - (const vector &rhs);
		/*-------------------------------------------------------------------------
		Purpose: subtraction operator
		Action: subtracts the component values of rhs to *this and stores them in 
						*this
		parameters: the object to be subtracted
		returns: self, AKA the left side of the subtraction
		*/
		vector operator * (const float factor);
		/*-------------------------------------------------------------------------
		Purpose: alternative assignment operator
		Action: makes ALL components of *this equal to the input (normally you'd use
						this for zeroing the vector)
		parameters: one float
		returns: the input float
		*/
		float operator = (const float rhs);
		/*-------------------------------------------------------------------------
		Purpose: compares two vectors
		Action: compares the components of each vector
		parameters: right hand side of the comparison
		returns: true if same, false if not
		*/
//		bool operator == (const vector rhs);
		/*-------------------------------------------------------------------------
		Purpose: sets the values of the vector components
		Action: sets this.data[X] to x, etc.
		parameters: the three vector components to be assigned
		notes: this function will only work in cartesian mode. 
					 There will need to be an overloaded function for other coordinate 
					 systems
		*/
		void set(float x, float y, float z);
		/*-------------------------------------------------------------------------
		Purpose: gives values to the calling function
		Action: passes the vector values of the object back by reference
		parameters: three floats to store the values in
		returns: none, but the values are passed back by reference
		*/
		void get(float& x, float& y, float& z);
		/*-------------------------------------------------------------------------
		Purpose: replaces *this with a random vector in the given parameters
		Action: calculates random values between the given parameters and sets *this
		parameters: six ints
		returns: none, modifies *this
		*/
		void randomVector(int xMin,int xMax,int yMin, int yMax, int zMin, int zMax); 
				/*-------------------------------------------------------------------------
		Purpose: replaces *this with a random unit vector
		Action: calls randomVector(-100,100,-100,100,-100,100) then normalize()
		parameters: none
		returns: none, modifies *this
		*/
		void randomUnitVector();
		/*-------------------------------------------------------------------------
		Purpose: determines the magnitude of the vector
		Action: takes the sqrt of magnitudeSquared()
		parameters: none
		returns: the magnitude (as a float)
		*/
		float magnitude();
		/*-------------------------------------------------------------------------
		Purpose: determines the squared magnitude of the vector
		Action: sums the squares of each vector component
		parameters: none
		returns: the squared magnitude (as a float)
		*/
		float magnitudeSquared();
		/*-------------------------------------------------------------------------
		Purpose: makes *this a unit vector
		Action: gets the magnitude() and divides each component by that
		parameters: none
		returns: none, it modifies *this
		*/
		void normalize();
		/*-------------------------------------------------------------------------
		Purpose: returns the distance between (*this-rhs)
		Action: returns sqrt(distanceSquared())
		parameters: the righthand side of the vector subtraction
		returns: the distance as a float
		*/
		float distance(const vector &rhs);
		/*-------------------------------------------------------------------------
		Purpose: returns the squared distance between (*this-rhs)
		Action: subtracts *this-rhs and finds the magnitude
		parameters: the righthand side of the vector subtraction
		returns: the distance^2 as a float
		*/
		float distanceSquared(const vector &rhs);
		/*-------------------------------------------------------------------------
		Purpose: finds the interpolation from *this to rhs
		Action: calculates *this-rhs and creates the new vector (point)
		parameters: the righthand side of the vector interpolation
		returns: the interpolated vector (point)
		*/
		vector linearInterpolation(const vector &rhs,float);
		/*-------------------------------------------------------------------------
		Purpose: calculates the cross product (*this x rhs)
		Action: see http://en.wikipedia.org/wiki/Cross_product
		parameters: rhs, the righthand parameter of the cross product
		returns: the cross product as a vector
		*/
		vector crossProduct(const vector &rhs);
		/*-------------------------------------------------------------------------
		Purpose: calculates the dot product (*this . rhs)
		Action: see http://en.wikipedia.org/wiki/Dot_product
		parameters: rhs, the righthand parameter of the dot product
		returns: the dot product as a float
		*/
		float dotProduct(const vector &rhs);
	};
#endif
