#include "Game_Object.h"

#include <iostream>

using namespace std;

Game_Object::Game_Object()
{

}

Game_Object::Game_Object(char in_code,int in_id)
{
	
	Cart_Point p1; // creates a (0,0) default Cart_Point

	

	display_code = in_code; //sets the game objects display_code to the input code

	id_num = in_id; //sets id_num of the Game_Object.

	location = p1; //sets the default location to (0,0)

	cout << "Game_Object default constructed." <<endl;
}

Game_Object::Game_Object(char in_code, int in_id, Cart_Point in_loc)
{
	
	display_code = in_code;

	id_num = in_id;

	location = in_loc;

	cout << "Game_Object constructed." << endl;
}

Cart_Point Game_Object::get_location()
{
	
	return location; //returns the location of the Game_Object
}

int Game_Object::get_id()
{
	return id_num; // returns the location of the Game_Object
}

void Game_Object::show_status()
{
	

	cout << display_code << " with ID " << get_id() << get_location() <<endl;

}

Game_Object::~Game_Object()
{
	cout << "Game_Object destructed." << endl; //message when the Game_Object is destroyed
}

bool Game_Object::update() // Doesnt really do anything
{
	return true;
}

void Game_Object::drawself(char* ptr) 
{
    ptr[0]= display_code; //stores the display code in the char array
  
    
    int a = get_id();
    
    
    ptr[1]= '0' + a; //stores id_num (ASCII) to array
    
}
bool Game_Object::is_alive()
{
    return true;
}
