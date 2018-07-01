#include <iostream>
#include <math.h> // for power function

using namespace std;

int main()
{

  int a;
  int b;
  int basea;
  int baseb;
  int i;
  int HD=0;// Hamming distace count
  int saveinput1;
  int saveinput2;

  cout << "Enter two numbers between 0~100: ";

  cin >> a;
  cin >> b;
  
  saveinput1= a; //saves initial input
  saveinput2= b;

  for(i=4;i>=0;i--) //for loop for converting to base-3 and compare
  { 
    int power = pow(3,i);
    
    basea = a / power;
    a = a % power;

    baseb = b /power;
    b = b % power;

    if ( basea != baseb ) // adds 1 to HD variable and collects during loop 
      {
	HD=HD+1;

      }
    
    
    
  }


  cout << "Hamming distance between " << saveinput1 << " and " << saveinput2 << " when numbers are in ternary format is: " << HD << endl;


  return 0;

}
