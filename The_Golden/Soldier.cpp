#include <iostream>
#include "Person.h"
#include "Soldier.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
using namespace std;

Soldier::Soldier() : Person('S')
{
	attack_strength = 2;

	range = 2.0;

	//target = 0; //Null

	state = 's';

	cout << "Soldier default constructed " << endl;
}
Soldier::Soldier(int in_id, Cart_Point in_loc) :Person('S', in_id, in_loc)
{
    attack_strength = 2;

	range = 2.0;

	//target = 0;

	state = 's';
    
	cout << "Soldier constructed " << endl;
}

void Soldier::start_attack(Person* in_target)
{	
	if (state == 'x')
	{
		cout << "I'm dead" << endl;
		return;
	}
	
	double dis;

	dis = cart_distance(location, in_target->get_location());

	if (dis <= range)
	{
		//cout << "Clang!" << endl;

		target = in_target;

		state = 'a';

	}

	else
		cout << display_code << get_id() << ": Target is out of range." <<endl;
}

bool Soldier::update()
{	
	int check;

	switch (state)
	{
		case 'x': 
			return false;
			break;

		case 's': 
			return false;
			break;
				
		case 'm':
			check = update_location(); // invoke update_location to see if the miner is at destination
			if (check == 1)
			{
				state = 's'; //if at destination, stop

				return true;
			}
			break;

		case 'a':
			double dis;
			dis = cart_distance(location, target->get_location());
			if (dis > range)
			{
				state = 's';
				return true;
			}
			else if (dis <= range)
			{
				if (target->is_alive() == true )
				{
					cout << display_code << get_id() << ": Clang!" << endl;

					target->take_hit(attack_strength);

					return false;
				}

				else if (target->is_alive() == false)
				{
					//cout << "I triumph!" << endl;

					state = 's';

					return true;
				}
			}
        default:
        return false;
            break;

	}
    return false;
}

void Soldier::show_status()
{
	cout << "Soldier status: ";
    if (state == 's')
    {
        cout << display_code << get_id() << " at " << location;
        
        cout << " is stopped." << endl;
        
        return;
    }
	//Person::show_status();
	if (state == 'a')
	{
        cout << display_code << get_id() << " at " << location;

        
		cout << " is attacking." << endl;
        return;
	}
    cout <<endl;
}

Soldier::~Soldier()
{
	cout << "Soldier destructed." << endl;
}
