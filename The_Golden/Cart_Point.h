#ifndef CART_POINT_H
#define CART_POINT_H
#include <iostream>
#include "Cart_Vector.h"
class Cart_Point
{
public:

	double x;

	double y;

	Cart_Point();

	Cart_Point(double , double);

	friend double cart_distance(Cart_Point, Cart_Point);

	friend std::ostream& operator<<(std::ostream& out , Cart_Point); //Used Friend to overload nonmember function

	friend Cart_Point operator+(Cart_Point , Cart_Vector );

	friend Cart_Vector operator-(Cart_Point,Cart_Point);


};

#endif
