//#ifndef RK
//#define RK
#include "rungeKutta.h"
/**
*rungeKutta function
*
* @brief Does the Runge Kutta approximation
*/
	void rungeKutta(vector (*force)(vector),float deltaTime,vector &velocity,vector &position,float mass) {
		vector k1,k2,k3,k4,forceVal,acceleration;
		// k1
			forceVal = force(velocity);
			acceleration = forceVal/mass;
			k1 = acceleration * deltaTime;
		// k2
			forceVal = force(velocity + k1/2);
			acceleration = forceVal/mass;
			k2 = acceleration * deltaTime/2.0;
		// k3
			forceVal = force(velocity + k2/2);
			acceleration = forceVal/mass;
			k2 = acceleration * deltaTime/2.0;
		// k4
			forceVal = force(velocity + k3);
			acceleration = forceVal/mass;
			k2 = acceleration * deltaTime;
		// calculate new velocity at time t+dt
			velocity = velocity + (( k1 + k2*2 + k3*2 + k4)/6);
		// calculate new displacement at time t+dt
			position = position + (velocity) * deltaTime;
	}
//#endif
