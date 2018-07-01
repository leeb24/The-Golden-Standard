#include <iostream>
#include <cmath>
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Person.h"
#include "Miner.h"
#include "Model.h"
#include "View.h"
#include "Game_Command.h"
#include "Input_Handling.h"
#include <string>
#include <sstream>
using namespace std;


int main()
{	
	char command; // variables for storing user inputs

	int first;

	int second;

	int last;
    
    
    
    char type;
	
	cout << "EC327: Introduction to Software Engineering" <<endl;
	cout << "Fall 2016" <<endl;
	cout << "Programming Assignment 3" <<endl;

	Model* model = new Model(); //Make a pointer to the default Model on the heap
    
	View look;// Make a default View class

	model->show_status(); // show the initial status of the objects
    
    model->display(look); //show the initial view of the objects
    look.clear(); //reset the grid

	do
	{
		cout << "Enter command: " ;
        
        
            
        
		cin >> command ;  
    	cin.ignore(); 

    	if(command == 'm' || command =='w' || command == 's' || command == 'a') //sort out if the function will be needing additional parameters
    	{
		
		string input; 

        getline(cin,input);
        
            stringstream (input) >> first >> second >> last;
		
		}
        
        if(command == 'n')
        {
            string input2;
            
            getline(cin,input2);
            
            stringstream (input2) >> type >> first >> second >> last;
  
        }
		
		switch(command) //switch statements for each command, leading to Game_Command
		{
			case 'm':
				cout << "Moving " << first << " to (" << second << "," << last << ")"<<endl; //echo the input
				do_move_command(model,first,second,last); //invokes do_move_command
				break;

			case 'w':
				do_work_command(model,first,second,last); //invokes the do_work_command
				break;

			case 's':
				do_stop_command(model,first); //invokes the do_stop_command
				break;

			case 'g':
				do_go_command(model); //invokes the go command
				break;

			case 'r':
				do_run_command(model); //invokes the run command
				break;

			case 'q':
				do_quit_command(model); //terminates program
				break;

			case 'a':
                cout << "S" << first <<": Attacking." << endl;
				do_attack_command(model,first,second);
            
            case 'n':
                do_make_command(model, type, first, second, last);


		}
        
		if (command != 'q') // show the view of the objects if the command is not q
		{
			model->display(look);
            look.clear();

		}
        
    
	}while(command != 'q' ); //loop untill user input q as command

	

	return 0;
}
