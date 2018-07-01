#ifndef CART_VECTOR_H
#define CART_VECTOR_H
#include <iostream>

class Cart_Vector
{
public:

	
	double x;

	double y;

	Cart_Vector();

	Cart_Vector(double , double);

    friend std::ostream& operator<<(std::ostream& out , Cart_Vector);//Used Friend to overload nonmember function


	friend Cart_Vector operator*(Cart_Vector,double);

	friend Cart_Vector operator/(Cart_Vector,double);



};

#endif
