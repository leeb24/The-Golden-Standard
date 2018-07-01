#ifndef PERSON_H
#define PERSON_H
#include "Cart_Point.h"
#include "Game_Object.h"
#include "Town_Hall.h"
#include "Gold_Mine.h"

class Person : public Game_Object
{
public:

	Person();

	Person(char);

	Person(char, int, Cart_Point);

	void start_moving(Cart_Point);
    
    virtual void start_mining(Gold_Mine*, Town_Hall*);

	void stop();

	void show_status();

	virtual ~Person();
	
	bool is_alive();

	void take_hit(int);

	virtual void start_attack(Person*);



protected:

	bool update_location();

	void setup_destination(Cart_Point);

private:

	double speed;

	Cart_Point destination;

	Cart_Vector delta;

	int health;
};

#endif
