#ifndef SOLDIER_H
#define SOLDIER_H

#include "Person.h"
#include "Cart_Point.h"

class Soldier : public Person
{
public:
	
	void start_attack(Person*);

	bool update();

	void show_status();

	Soldier();

	Soldier(int , Cart_Point);

	~Soldier();

private:

	int attack_strength;

	double range;

	Person* target;

};

#endif