#ifndef TOWN_HALL_H
#define TOWN_HALL_H
#include "Cart_Point.h"
#include "Game_Object.h"

class Town_Hall : public Game_Object
{
private:

	double amount;

public:

	Town_Hall();

	Town_Hall(int, Cart_Point);

	
	void deposit_gold(double);

	bool update();

	void show_status();

	~Town_Hall();

};
#endif