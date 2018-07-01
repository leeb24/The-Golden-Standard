#include "Cart_Point.h"
#include <iostream>
#include "Gold_Mine.h"
#include "Game_Object.h"
using namespace std;

Gold_Mine::Gold_Mine():Game_Object('G',0)
{	
	
	state = 'f'; // Default state of the gold mine(Full)

	amount =  100; //default amount of the gold it stores

    cout << "Gold Mine default constructed." <<endl;
	
}

Gold_Mine::Gold_Mine(int inputId, Cart_Point inputLoc):Game_Object('G',inputId , inputLoc)

{	

	state = 'f';
	amount =  100;
    
    cout << "Gold Mine constructed." <<endl;
 	
}


bool Gold_Mine::is_empty()

{
	if ( amount == 0 ) //if the amount of the gold mine is 0 return true
		return true;
	else
		return false; //if not, return false
}

double Gold_Mine::dig_gold(double amount_to_dig )
{
	if ( amount >= amount_to_dig ) // if the amount is bigger than 35, it deducts 35 from the its quantity
	{
		
		amount = amount - amount_to_dig;

		return amount_to_dig;
	}	
	else if ( amount < amount_to_dig ) //if the amount is less than 35, it deducts the remaining gold
	{
		double a = amount;
		
		amount = 0;
		
		return a; //returns the remaining amount of the gold
	}

    return 0;
	
}
void Gold_Mine::show_status()
{
	cout << "Gold Mine status: " << this->display_code <<this->get_id() <<" at location " << this->get_location()<< " contains " << amount <<"." <<endl;

}
bool Gold_Mine::update()
{
	if ( amount == 0 && display_code=='G') //returns true only if the previous state was 'G'
	{
		state = 'e'; //if the goldmine is empty, state changes to 'e'

		display_code = 'g'; //changes the state from G to g

		cout << "Gold_Mine"<<  this->get_id() <<" has been depleted." <<endl;

		return true;
	}

	else 
		return false;
}

Gold_Mine::~Gold_Mine()
{
	cout << "Gold_Mine destructed." << endl;
}
