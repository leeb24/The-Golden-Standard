#include "Cart_Point.h"
#include "Cart_Vector.h"
#include <iostream>
#include <cmath>

using namespace std;

Cart_Point::Cart_Point()
{
	x= 0.0; // sets the default Cart_Point to (0,0)

	y= 0.0;
}

Cart_Point::Cart_Point(double inputx, double inputy)
{
	x= inputx; //sets the Cart_Point to the User input coordinate

	y= inputy;
}

double cart_distance(Cart_Point p1, Cart_Point p2)
{
	double distance;
	double sum;

	sum = ((p2.x-p1.x)*(p2.x-p1.x))+((p2.y-p1.y)*(p2.y-p1.y)); // calculates the distance between two points

	distance = sqrt (sum);

	return  distance; //returns the distance value
}

ostream& operator<<(ostream& out , Cart_Point p1) //Overloading Operator of <<
{
	out << "(" << p1.x << "," << p1.y << ")" ; //How overloaded operator behaves

	return out;
}

Cart_Point operator+ (Cart_Point p1, Cart_Vector v1) // Overloading operator +
{
	Cart_Point p3;

	p3.x = p1.x + v1.x; // adding to coordinates

	p3.y = p1.y + v1.y;

	return p3;
}

Cart_Vector operator- (Cart_Point p1, Cart_Point p2) //Overloding Operator - (Produces Cart Vector)
{
	Cart_Vector v3;


	v3.x = p1.x - p2.x;

	v3.y = p1.y - p2.y;

	return v3;

}


