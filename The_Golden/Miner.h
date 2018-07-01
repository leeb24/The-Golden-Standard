#ifndef MINER_H
#define MINER_H
#include "Cart_Point.h"
#include "Game_Object.h"
#include "Town_Hall.h"
#include "Gold_Mine.h"

class Miner : public Person
{
public:
	
	Miner();

	Miner(int, Cart_Point);

	bool update();

	void start_mining(Gold_Mine*, Town_Hall*);

	Cart_Point get_location();

	void show_status();

	~Miner();

private:

	double amount;

	Gold_Mine* mine;

	Town_Hall* home;


};

#endif