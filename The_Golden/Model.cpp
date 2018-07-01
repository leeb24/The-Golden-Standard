#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Person.h"
#include "Miner.h"
#include "Model.h"
#include "View.h"
#include "Soldier.h"
#include <iostream>
#include <list>


using namespace std;

Model::Model()
{
    
    time = 0;
    
    Cart_Point p1(5, 1); //initial position for Miner1
    
    Miner* miner1pointer;
    
    miner1pointer = new Miner(1, p1); //creates Miner1 in the heap at certain position.
    
    object_ptrslist.insert(object_ptrslist.begin(), miner1pointer);
    active_ptrs.insert(active_ptrs.begin(), miner1pointer);
    person_ptrs.insert(person_ptrs.begin(), miner1pointer);
    
    
    //
    Cart_Point p2(10, 1);
    
    Miner* miner2pointer;
    
    miner2pointer = new Miner(2, p2);
    
    object_ptrslist.insert(object_ptrslist.begin(), miner2pointer);
    person_ptrs.insert(person_ptrs.begin(), miner2pointer);
    active_ptrs.insert(active_ptrs.begin(), miner2pointer);
    
    
    
    //
    Cart_Point p3(1, 20);
    
    Gold_Mine* goldmine1ptr;
    
    goldmine1ptr = new Gold_Mine(1, p3);
    
    object_ptrslist.insert(object_ptrslist.begin(), goldmine1ptr);
    active_ptrs.insert(active_ptrs.begin(), goldmine1ptr);
    mine_ptrs.insert(mine_ptrs.begin(), goldmine1ptr);
    
    
    //
    Cart_Point p4(10, 20);
    
    Gold_Mine* goldmine2ptr;
    
    goldmine2ptr = new Gold_Mine(2, p4);
    
    
    object_ptrslist.insert(object_ptrslist.begin(), goldmine2ptr);
    active_ptrs.insert(active_ptrs.begin(), goldmine2ptr);
    mine_ptrs.insert(mine_ptrs.begin(), goldmine2ptr);
    
    
    //
    Town_Hall* townhptr;
    
    Cart_Point p5(0,0);
    
    townhptr = new Town_Hall(1,p5);
    
    object_ptrslist.insert(object_ptrslist.begin(), townhptr);
    active_ptrs.insert(active_ptrs.begin(), townhptr);
    hall_ptrs.insert(hall_ptrs.begin(), townhptr);
    
    
    //
    Soldier* Soldier3 = new Soldier(3,Cart_Point(5,15));
    
    object_ptrslist.insert(object_ptrslist.begin(), Soldier3);
    active_ptrs.insert(active_ptrs.begin(), Soldier3);
    person_ptrs.insert(person_ptrs.begin(), Soldier3);
    
    
    //
    Soldier* Soldier4 = new Soldier(4,Cart_Point(10,15));
    
    
    object_ptrslist.insert(object_ptrslist.begin(), Soldier4);
    active_ptrs.insert(active_ptrs.begin(), Soldier4);
    person_ptrs.insert(person_ptrs.begin(), Soldier4);
    
    
    
    
    
    //
    cout << "Model constructed." << endl;
    
}

Model::~Model()
{
    for(
        list<Game_Object*>::iterator obj_iterator = object_ptrslist.begin();
        obj_iterator != object_ptrslist.end();
        obj_iterator++)
    {
        delete *obj_iterator;
        
        
    }
    cout << "Model destructed." << endl;
}

Person* Model::get_Person_ptr(int id)
{
    
    for( list<Person*>::iterator person_iterator = person_ptrs.begin(); person_iterator != person_ptrs.end();person_iterator++)
    {
        int idcheck;
        
        idcheck = (*person_iterator)->get_id();
        
        if (idcheck == id)
        {
            
            return (*person_iterator); //if the pointer was found return that pointer
        }
        
        
    }
    
    return NULL;
    
    
}

Gold_Mine* Model::get_Gold_Mine_ptr(int id)
{
    for( list<Gold_Mine*>::iterator mine_iterator = mine_ptrs.begin(); mine_iterator != mine_ptrs.end(); mine_iterator++){
        
        int idcheck;
        
        idcheck = (*mine_iterator)->get_id();
        
        if (idcheck == id)
        {
            
            return (*mine_iterator); //if the pointer was found return that pointer
        }
        
    }
    
    
    return NULL;
}

Town_Hall* Model::get_Town_Hall_ptr(int id)
{
    for( list<Town_Hall*>::iterator hall_iterator = hall_ptrs.begin(); hall_iterator != hall_ptrs.end(); hall_iterator++) {
        int idcheck;
        
        idcheck = (*hall_iterator)->get_id();
        
        if (idcheck == id)
        {
            
            return (*hall_iterator); //if the pointer was found return that pointer
        }
        
        
    }
    
    return NULL;
    
}

bool Model::update()
{
    time = time + 1;
    
    int a = 0;
    
    
    
    
    
    
    int* check1 = new int [active_ptrs.size()];
    
    for(
        list<Game_Object*>::iterator active_iterator = active_ptrs.begin();
        active_iterator != active_ptrs.end();
        active_iterator++)
    {
        
        
        
        check1[a] = (*active_iterator)->update();
        
        a++;
        
       
    }
    
    for( list<Game_Object*>::iterator person_iterator = active_ptrs.begin(); person_iterator != active_ptrs.end();person_iterator++)
    {
        if((*person_iterator)->is_alive() == false)
        {
            cout << "Dead Object removed" << endl;
            
            person_iterator = active_ptrs.erase(person_iterator);
            
            
        }
        
    }
    
    
    
    
    for (int i = 0; i < active_ptrs.size(); i++)
    {
        if (check1[i] == 1) //if any one of the objects returned true, return true
        {
            return true;
        }
        
    }
    
    
    
    return false;
}

void Model::show_status()
{	
    cout << "Time: " << time <<endl;
    for(
        list<Game_Object*>::iterator obj_iterator = object_ptrslist.begin();
        obj_iterator != object_ptrslist.end();
        obj_iterator++)
    {
        (*obj_iterator)->show_status();
        
        
    }
    
    
    
}

void Model::display(View &view)
{	
    
    
    
    for(
        list<Game_Object*>::iterator active_iterator = active_ptrs.begin();
        active_iterator != active_ptrs.end();
        active_iterator++)
    {
        view.plot(*active_iterator);
    }
    
    view.draw();
}

void Model::handle_new_command(Model* model, char type, int id, int x, int y)
{
    if ( id > 9 )
    {
        cout << "Invalid ID - ID number is invalid." <<endl;
        return;
    }
    
    if( type == 'g')
    {
        for( list<Gold_Mine*>::iterator mine_iterator = mine_ptrs.begin(); mine_iterator != mine_ptrs.end(); mine_iterator++){
            
            int idcheck;
            
            idcheck = (*mine_iterator)->get_id();
            
            if (idcheck == id)
            {
                cout << "ID number already exists!" << endl;
                return;
            }
            
        }
        
        
        
        Gold_Mine* newgoldmineptr = new Gold_Mine(id, Cart_Point(x,y));
        
        
        object_ptrslist.push_back(newgoldmineptr);
        active_ptrs.push_back(newgoldmineptr);
        mine_ptrs.push_back(newgoldmineptr);

        
        
        
        
    }
    
    else if ( type == 't')
    {
        for( list<Town_Hall*>::iterator hall_iterator = hall_ptrs.begin(); hall_iterator != hall_ptrs.end(); hall_iterator++) {
            int idcheck;
            
            idcheck = (*hall_iterator)->get_id();
            
            if (idcheck == id)
            {
                cout << "ID number already exists!" << endl;
                return;
            }
        }
        
        
        Town_Hall* newhallptr = new Town_Hall(id, Cart_Point(x,y));
            
            
        object_ptrslist.push_back(newhallptr);
        active_ptrs.push_back(newhallptr);
        hall_ptrs.push_back(newhallptr);

        
    }
    
    else if ( type == 'm')
    {
        for( list<Person*>::iterator person_iterator = person_ptrs.begin(); person_iterator != person_ptrs.end();person_iterator++)
        {
            int idcheck;
            
            idcheck = (*person_iterator)->get_id();
            
            if (idcheck == id)
            {
                cout << "ID number already exists!" << endl;
                return;
            }
        }
        
        Miner* newminerptr = new Miner(id,Cart_Point(x,y));
        
        object_ptrslist.push_back(newminerptr);
        active_ptrs.push_back(newminerptr);
        person_ptrs.push_back(newminerptr);
        
        
    }
    
    else if ( type == 's')
    {
        for( list<Person*>::iterator person_iterator = person_ptrs.begin(); person_iterator != person_ptrs.end();person_iterator++)
        {
            int idcheck;
            
            idcheck = (*person_iterator)->get_id();
            
            if (idcheck == id)
            {
                cout << "ID number already exists!" << endl;
                return;
            }
        }
        
        Soldier* newsoldierptr = new Soldier(id,Cart_Point(x,y));
        
        object_ptrslist.push_back(newsoldierptr);
        active_ptrs.push_back(newsoldierptr);
        person_ptrs.push_back(newsoldierptr);
        
    }
}

