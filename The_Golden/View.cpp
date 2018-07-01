#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "View.h"
#include <iostream>
#include <cmath>

using namespace std;

View::View()
{
	size = 11 ;

	scale = 2 ; 

	Cart_Point p1;

	origin = p1;
    
    
    
    for(int y = 0 ; y < 11 ;y = y+1)
    {
        for (int x = 0 ; x <11 ;x= x+1)
        {
            
            {
                grid[x][y][0] ='.';
                grid[x][y][1] =' ';
            }
            
        }
        
    }
    
    
}

void View::plot(Game_Object* ptr)
{	
	int ix;
	int iy;
	int y = 0;
	char gid[2];

    
	
    Cart_Point p1;
    
    

	
	p1 = ptr->get_location();

	get_subscripts (ix,iy,p1);

	
	
	ptr->drawself(gid);
    
    if ( grid[ix][iy][0] != '.')
    {
        grid[ix][iy][0] = '*';
        grid[ix][iy][1] = ' ';
    }

    else
    {
        grid[ix][iy][0] = gid[0];

        grid[ix][iy][1] = gid[1];
    }
    
    //cout<< grid[ix][iy][0] <<grid[ix][iy][1] <<endl;
    
    

	
	
}

bool View::get_subscripts(int &ix, int &iy, Cart_Point location)
{
	

	Cart_Vector v1;

	v1 = (location-origin)/scale;

	ix = v1.x;

	iy = v1.y;

	if (ix <= 11 && iy <= 11)
	{
		return true;
	}
	else 
	{
		cout << "Object outside display" <<endl;
		return false;
	}

}

void View::draw()
{
	for (int y = 10; y > -1; y--)
	{
        if(y%2 == 0)
        {
            if(y == 10)
                cout << "20";
            else if(y == 8)
                cout << "16";
            else if(y == 6)
                cout << "12";
            else if(y == 4)
                cout << "8 ";
            else if(y == 2)
                cout << "4 ";
            else if(y == 0)
                cout << "0 ";
        }
        else
            cout << "  " ;
        
		for (int x = 0; x < 11;x++)
		{
            
			cout << grid[x][y][0] << grid[x][y][1];
            
		}

		cout << endl;
        
	}
    
    cout << "  0   4   8   12  16  20" <<endl;


}

void View::clear()
{
    for(int y = 0 ; y < 11 ;y = y+1)
    {
        for (int x = 0 ; x <11 ;x= x+1)
        {
            
            {
                
                grid[x][y][0] ='.';
                grid[x][y][1] =' ';
            }
            
        }
        
    }
    
}
