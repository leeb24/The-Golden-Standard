#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include <iostream>
#include <cmath>
#include "Person.h"
#include "Miner.h"
#include "Game_Object.h"

using namespace std;

Miner::Miner() :Person('M') //Default constructor for Miner
{
    state = 's'; //initially at stop
    
	amount = 0; //has no gold initially
	
	mine = 0; //pointers are set to NULL(0)

	home = 0;

	cout << "Miner default constructed." << endl;
}

Miner::Miner(int in_id, Cart_Point in_loc) :Person('M', in_id, in_loc)
{
    state = 's';
    
	amount = 0;

	mine = 0;
	
	home = 0;

	cout << "Miner constructed." << endl;
    
    
}

bool Miner::update() //uses switch statements for varying states
{	
	
	int check;
	int check2;
	int check3;
	int check4;
    
	switch (state)
	{
        case 's':              // do nothin if its in stop
            break;
	
        case 'm':
            
            check = update_location(); // invoke update_location to see if the miner is at destination
			  if (check == 1)
		      {
					state = 's'; //if at destination, stop
			
					return true;
		      }
            break;

        case 'o':
            
            check2 = update_location(); //checks the location to the destination every update
		     if (check2 == 1)
		     {
				 state = 'g'; // if at destination, start digging
			
					return true;
		     }
            break;

        case 'g':
            amount = mine->dig_gold(); //invokes dig_gold function to dig gold from mine
            cout << display_code << get_id() << ": Got " << amount << " gold " << endl;
            setup_destination(home->get_location()); // Sets home to destination
			
            state = 'i'; // state inbound to home
            mine->update();
            return true;
			break;
	
        case 'i':
            check3 = update_location(); //check location to see if the miner is at home
            if (check3 == 1)
            {
				  state = 'd'; // if at home, deposit gold
                  return true;
            }
            break;

        case 'd':
            cout << display_code << get_id() << ": Deposit " << amount << " of gold." << endl;
            home->deposit_gold(amount); //deposit the gold carried from gold mine
            amount = 0; //resets gold amount
            check4 = mine->is_empty();
            if (check4 == 1) // if the gold mine is empty
            {
                state = 's';
                cout << display_code << get_id() << ": More work?" << endl;
                home->update();
                return true;
            }
            else if (check4 == 0) // if the gold mine is not empty
            {
                setup_destination(mine->get_location());
                state = 'o';
                cout << display_code << get_id() << ": Going back for more." << endl;
                home->update();
                return true;

            }
            break;

		case'x':
			return false;
	
	}
    
    return 0;
	
}

void Miner::start_mining(Gold_Mine* inputMine, Town_Hall* inputHome)
{	
	if (state == 'x')
	{
		cout << "I'm dead" << endl;
		return;
	}
    
    mine = inputMine; // set pointers to the input Gold_Mine and Town_Hall
    home = inputHome;
    
	setup_destination(inputMine->get_location()); // set destination to the input Gold_Mine

	state = 'o'; //outbound to mine

	cout << "Miner " << get_id() << " mining at Gold_Mine " << inputMine->get_id() << " and depositing at Town_Hall " << inputHome->get_id() << "." << endl;

	cout << display_code << get_id() << ": Yes, my lord." << endl;

}

Cart_Point Miner::get_location()
{
	return location;
}

void Miner::show_status()
{
    
	switch (state) //different cout statements for varying states
	{
        case 's':
		cout << "Miner status: " << display_code << get_id() << " at " << location;
		
		cout << " is stopped." << endl;
            break;

        case 'm':
            cout << "Miner status: " << display_code << get_id() << " at " << location ;
		Person::show_status();
            cout << endl;
            break;
        case 'o':
		cout << "Miner status: " << display_code << get_id() << " at " << location;
		Person::show_status();
		cout << " is outbound to mine. " << endl;
            break;
        case 'g':
		cout << "Miner status: " << display_code << get_id() << " at " << location;
		Person::show_status();
		cout << " getting gold from mine. " << endl;
            break;
        case 'i':
		cout << "Miner status: " << display_code << get_id() << " at " << location;
		Person::show_status();
		cout << " is inbound to home with load: "<< amount << endl;
            break;
        case 'd':
		cout << "Miner status: " << display_code << get_id() << " at " << location;
		Person::show_status();
		cout << " is despositing gold." << endl;
            break;
	}
}

Miner::~Miner()
{
	cout << "Miner destructed." << endl;
}
