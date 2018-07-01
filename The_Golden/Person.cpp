#include "Cart_Point.h"
#include "Cart_Vector.h"
#include <iostream>
#include <cmath>
#include "Person.h"
#include "Game_Object.h"
#include "Town_Hall.h"
#include "Gold_Mine.h"

using namespace std;

Person::Person()
{

}

Person::Person(char in_code): Game_Object(in_code,0)
{
	speed = 5; //initial speed of 5

	health = 5;

	cout << "Person default constructed." << endl;
}

Person::Person(char in_code, int in_id, Cart_Point in_loc):Game_Object(in_code, in_id, in_loc)
{
	speed = 5;

	health = 5;

	cout << "Person contructed." << endl;

}

void Person::start_moving(Cart_Point dest)
{	
	if (state == 'x')
	{	
		cout << "I'm dead" << endl;
		return;
	}

	setup_destination(dest);

	state = 'm';

	//“Moving (id) to (destination).” and another message “(display_code)(id): On my way.”

	//cout << "Moving " << display_code << get_id() << " to " << dest << endl;
    
    if ( location.x != dest.x || location.y != dest.y)
    {
        cout << display_code << get_id() << ": On my way." << endl;
    }
    if ( location.x == dest.x && location.y == dest.y)
    {
        cout << display_code << get_id() << ": I'm already there. see?" << endl;

    }
    
    if (location.x == dest.x && location.y == dest.y )
    {
        state = 's';
    }

}

void Person::stop()
{
	state = 's';
    

	//Prints “Stopping (id).” and another message “(display_code)(id): All right.”

	//cout << "Stopping " << display_code << get_id() << endl;

	cout << display_code << get_id() << ": Stopped" <<endl;



}

void Person::show_status()
{
	
	//Game_Object::show_status(); ???

	//Miner status: M1 at (10,20) moving at speed of 5 towards (10,20) at each step of <1.27247,4.83537> is stopped.

	cout << " moving at speed of " << speed << " towards " << destination << " at each step of " << delta;

	//dead or alive

	if (state == 'x')
	{
		cout << " is dead." <<endl;;
	}

	/*else
		cout << " Health is: " << health<<endl;*/
}

bool Person::update_location()
{	
	Cart_Vector check = destination - get_location();
    
	if (abs(check.x) <= abs(delta.x) && abs(check.y) <= abs(delta.y))
    {
		location = destination;

		cout << display_code << get_id() << ": I'm there!"<< endl;

		return true;

	}


	else
	{
		location = location + delta;

		cout << display_code << get_id() << ": step..."<< endl;

		return false;
	}


}

void Person::setup_destination(Cart_Point dest)
{	
	destination = dest;
    
    Cart_Vector v1;

	delta = (destination - get_location())*(speed / cart_distance(destination, get_location()));
    
    if (cart_distance(destination, get_location()) == 0)
    {
        delta = v1;
    }
    
    
}

void Person::start_mining(Gold_Mine*, Town_Hall*)
{
    cout << " Sorry, I cant work a mine " <<endl;
}

Person::~Person()
{
	cout << "Person destructed." << endl;
}

void Person::take_hit(int attack_strength)
{
	health = health - attack_strength;

	if (health <= 0)
	{
        cout << display_code << get_id() << ": Arrggh!" << endl;

		state = 'x';
	}

	else
		cout << display_code << get_id() << ": Ouch!" << endl;

}

void Person::start_attack(Person* target)
{
	cout << "I can't attack" << endl;
}

bool Person::is_alive()
{
	if (state == 'x')
		return false;
	else
		return true;
}
