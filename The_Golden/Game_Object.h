#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "Cart_Point.h"

class Game_Object
{
private:

	int id_num;

protected:

	Cart_Point location;
	
	char display_code;

	char state;

public:

	Game_Object();

	Game_Object(char,int);

	Game_Object(char,int,Cart_Point);

	//virtual void start_mining(Gold_Mine*, Town_Hall*);

	Cart_Point get_location();

	int get_id();

	virtual void show_status();

	virtual bool update();

	virtual ~Game_Object();
    
    void drawself(char*);
    
    virtual bool is_alive();

};

#endif
