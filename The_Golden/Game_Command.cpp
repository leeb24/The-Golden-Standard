#include "Model.h"
#include "Game_Command.h"
#include "Cart_Point.h"
#include "Person.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Soldier.h"
#include <iostream>

using namespace std;


void do_move_command(Model* model,int id,int x,int y) // command 'm'
{
	Cart_Point p1(x,y); //Initilize a Cart_Point to input (x,y)

	Person* personptr = model->get_Person_ptr(id); //Get a person ptr with a variable id(input)

	personptr->start_moving(p1); //Calls start_moving function in class Person

}

void do_work_command(Model* model, int id1, int id2, int id3)
{
    Person* personptr = model->get_Person_ptr(id1); //Get a person ptr with a variable id(input)

	Gold_Mine* mineptr = model->get_Gold_Mine_ptr(id2); //Get a Gold_Mine ptr with  id2(input)

	Town_Hall* hallptr = model->get_Town_Hall_ptr(id3); //Get a Town_Hall ptr with id3(input)

	personptr->start_mining(mineptr,hallptr); //invokes the start mining function of specified class (Miner)
}

void do_stop_command(Model* model, int id)
{
	Person* personptr = model->get_Person_ptr(id); //Get ptr of a Person with user input (id)

	personptr->stop(); //invokes function stop
}

void do_go_command(Model* model)
{
	cout << "Advancing one tick." <<endl;
	model->update(); //  Runs 1 iteration of update() of all objs
	model->show_status(); //show status of objects after update
}

void do_run_command(Model* model)
{
	int check;

	cout << "Advancing to next event." <<endl;

	for (int i = 0; i < 5 ; i++) //runs 5 iteration of update unless true is returned
	{
		check = model->update();

		if(check == 1) //if true was returned, break from the loop
		{
			model->show_status();
			break;
		}

		if(i == 4)
		{
			model->show_status();//if true was not returned, show_status
			break;
		}

	}


}

void do_quit_command(Model* model)
{
	cout << "Terminating program." << endl;
	delete model;
}

void do_attack_command(Model* model, int id1 , int id2)
{
	Person* soldierptr = model->get_Person_ptr(id1);

	soldierptr->start_attack(model->get_Person_ptr(id2));

}

void do_make_command(Model* model, char type, int id, int x, int y)
{
    
    model->handle_new_command(model, type, id, x, y);
    
}
