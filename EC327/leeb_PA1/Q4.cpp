#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;

int Cardone;
int Cardtwo;
char Royals1;
char Royals2;

// Overloaded fuctions
int BlackJack ( int Cardone , int Cardtwo ) // int + int combo
{
    
        int total = 0;
    
        total = Cardone + Cardtwo;
    
        return total;

}

int BlackJack ( int Cardone , char Royals2 ) // int  + char combo
{
    
    int total = 0;
    int x = 0;
    int y =0;
    
    if (Royals2 == 'j' || Royals2 == 'q' || Royals2 == 'k') {
        
        y = 10;
        
    }
    if ( Royals2 == 'A' )
    {
        
        y = 11;
        
    }
  
    total = y + Cardone;
    
    
    
        return total ;
        
}
    
int BlackJack ( char Royals1 , int Cardtwo ) // char + int combo
{
    
    int total = 0 ;
    int x = 0;
    
    if (Royals1 == 'j' || Royals1 == 'q' || Royals1 == 'k')
    {
        
        x = 10;
        
    }
    if ( Royals1 == 'A' )
    {
        
        x = 11;
    
    }

    total = x + Cardtwo;
        return total;
        
}
    
int BlackJack ( char Royals1, char Royals2 )// char + char combo
{
    
    int total = 0;
    int x = 0,y = 0;
    if ( Royals1 == 'j' || Royals1  == 'q' || Royals1 == 'k') {
        
        x = 10;
        
    }
    
    else if ( Royals1 == 'A' ){
        
        x = 11;
    
    }
    
    if ( Royals2 == 'j' || Royals2 == 'q' || Royals2 == 'k'){
        
        y = 10;
        
    }
    
    else if ( Royals2  == 'A') {
        
        y = 11;
        
    }
    
    total = x + y;
    
        return total;
}
    



int main ()
{
    int Cardone;
    int Cardtwo;
    int Cardthree;
    int total;
    char Royals1;
    char Royals2;
    char Ask;
    
    
    
    
    // Seed Time
    srand (time(NULL));
    
    // Rand (Draw two cards)
    Cardone = rand() % 13 + 2;

    Cardtwo = rand() % 13 + 2;

    
    cout << "Welcome to EC327 Black Jack" << endl;
    
    // 11-14 into J,Q,K,A for each overloaded function
    
    if(Cardone > 10 && Cardtwo > 10)
    {
        if(Cardone == 11)
        {
            Royals1 = 'j';
        }
        if(Cardone == 12)
        {
            Royals1 ='q';
        }
        if(Cardone == 13)
        {
            Royals1 ='k';
        }
        if(Cardone == 14)
        {
            Royals1 ='A';
        }

        if(Cardtwo == 11)
        {
            Royals2 = 'j';
        }
        if(Cardtwo == 12)
        {
            Royals2 ='q';
        }
        if(Cardtwo == 13)
        {
            Royals2 ='k';
        }
        if(Cardtwo == 14)
        {
            Royals2 ='A';
        }

        total = BlackJack (Royals1,Royals2); //invoke fuction


    }

    if((Cardone > 10) && (Cardtwo <= 10))
    {
        if(Cardone == 11)
        {
            Royals1 = 'j';
        }
        if(Cardone == 12)
        {
            Royals1 ='q';
        }
        if(Cardone == 13)
        {
            Royals1 ='k';
        }
        if(Cardone == 14)
        {
            Royals1 ='A';
        }

        total = BlackJack (Royals1, Cardtwo); //invoke fuction

    }

    if((Cardone <= 10) && (Cardtwo > 10))
    {
        if(Cardtwo == 11)
        {
            Royals2 = 'j';
        }
        if(Cardtwo == 12)
        {
            Royals2 ='q';
        }
        if(Cardtwo == 13)
        {
            Royals2 ='k';
        }
        if(Cardtwo == 14)
        {
            Royals2 ='A';
        }
        
        total = BlackJack (Cardone, Royals2); //invoke fuction
        
    }
    
    
    if ( (Cardone <= 10) && (Cardtwo <= 10))
    {
        total = BlackJack( Cardone , Cardtwo ); //invoke fuction
    }
    
    
   
    
    cout << "Total: " << total << endl;
    
    // Draw again process & pick one more card from 2-14 & check if total becomes 21
    
    if (total < 21)
    {
        
        do
        {
            cout << "Draw again? (y,n) " ;
        
            cin >> Ask ;
            if ( Ask == 'n' ) {
                
                cout << "TOTAL: " << total << endl;
                cout << "YOU QUIT WITH "<< total << endl;
                break;
                
            }
            
            if ( Ask != 'y' ) {
                
                cout << "ERROR OCCURED " << endl;
                break;
                
            }
           
                
                Cardthree = rand() % 13 + 2;
                
                if ( Cardthree == 14 )
                {
                    
                    total = total + 11 ;
                    
                }
                
                else if ( Cardthree == 13 || Cardthree == 12 || Cardthree == 11)
                {
                    
                    total = total + 10 ;
                    
                }
                
                else if ( Cardthree <= 10 )
                {
                    
                    total = total + Cardthree ;
                    
                }
                
                if (total == 21)
                {
                    
                    cout << "Total: " << total <<endl;
                    cout << "WON BLACKJACK" << endl;
                    return 0;
                    
                }
                
                if (total > 21)
                {
                    
                    cout << "TOTAL : " << total << endl;
                    
                    cout << "FAILED BLACKJACK" << endl;
                    break;
                    
                }
                
                
            
            cout << "TOTAL " << total << endl;
          
        
        }while(Ask == 'y');
        
        
        
            
            
    }
    

    if ( total == 21 )
    {
        cout << "Total: " << total <<endl;
        cout << "WON BLACKJACK" << endl;
        
    }
    
    
    return 0;
    }













    

    

