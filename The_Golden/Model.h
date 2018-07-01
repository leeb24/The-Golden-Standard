#ifndef MODEL_H
#define MODEL_H
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Person.h"
#include "Miner.h"
#include "View.h"
#include <list>

using namespace std;

class Model
{
public:
	
	Model();
	
	~Model();

	Person* get_Person_ptr(int);

	Gold_Mine* get_Gold_Mine_ptr(int);

	Town_Hall* get_Town_Hall_ptr(int);

	bool update();
	

	void display(View &);

	void show_status();
    
    void handle_new_command(Model* , char , int , int , int );

private:
	Model( const Model&);

	int time;

	
	list<Game_Object*> object_ptrslist;

	list<Game_Object*> active_ptrs;

	int num_objects;

	

	list<Person*> person_ptrs;

	int num_persons;

	

	int num_mines;

	list<Gold_Mine*> mine_ptrs;

	

	int num_halls;

	list<Town_Hall*> hall_ptrs;


	
};

#endif
