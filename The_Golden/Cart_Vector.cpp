#include "Cart_Vector.h"
#include <iostream>
#include <cmath>

using namespace std;

Cart_Vector::Cart_Vector() //Sets default Cart_Vector to <0,0>
{
	x= 0.0;

	y= 0.0;
}

Cart_Vector::Cart_Vector(double inputx, double inputy) //Sets Cart_Vector to User input
{
	x= inputx;

	y= inputy;
}

ostream& operator<<(ostream& out , Cart_Vector v1) //Overloading Operator of  << (Different bracket)
{
	out << "<" << v1.x << "," << v1.y << ">" ;

	return out;
}

Cart_Vector operator* (Cart_Vector v1, double d) 
{
	Cart_Vector v2;

	v2.x = v1.x * d;

	v2.y = v1.y * d;

	return v2;
}

Cart_Vector operator/ (Cart_Vector v1, double d)
{	
	if (d == 0)
	{
		return v1;
	}

	Cart_Vector v2;

	v2.x = v1.x / d;

	v2.y = v1.y / d;
	
		return v2;
}
