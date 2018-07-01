#include "Cart_Point.h"
#include <iostream>
#include "Town_Hall.h"
#include "Game_Object.h"

using namespace std;

Town_Hall::Town_Hall() :Game_Object('t', 0)
{

	state = 'o';

	amount = 0;

	cout << "Town_Hall default constructed." << endl;

}

Town_Hall::Town_Hall(int inputId, Cart_Point input_Loc) :Game_Object('t', inputId, input_Loc)
{
	state = 'o';

	amount = 0;

	cout << "Town_Hall constructed." << endl;

}

void Town_Hall::deposit_gold(double deposit_amount)
{
	amount = amount + deposit_amount;
	
}

bool Town_Hall::update()
{
	if (amount >= 50 && display_code == 't')
	{
		state = 'u';

		display_code = 'T';

		cout << display_code << get_id() << " has been upgraded." << endl;

		return true;
	}

	else 
	{
		return false;
	}

}

void Town_Hall::show_status()
{
	cout << "Town Hall status: " << this->display_code << this->get_id() << " at location " << this->get_location() << " contains " << amount << " of gold. ";

	if (state == 'o')
		cout << "Not yet upgraded" << endl;
	if (state == 'u')
		cout << "Upgraded" << endl;
}

Town_Hall::~Town_Hall()
{
	cout << "Town_Hall destructed." << endl;
}
