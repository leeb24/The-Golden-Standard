#include <iostream>
#include <fstream>
#include <cmath>


using namespace std;

int main(){

	ifstream input("inputbye.txt");
	int temp;
	int i = 0;
	int inputarray [1003];
	double sum, daA, daB;
	int power, power1;
	int min;
	while(!input.eof()){
	
		input >> temp;

		if(!input.eof())
			break;
		inputarray[i]=temp;
		i++;

	}	

	for(double i = 0 ; i < 25 ; i = i + 0.1)
	{
		for( double j = 0 ; j < 25 ; j = j + 0.1)
		{	
			for( int num = 2 ; num < 1004 ; num++)
			{	
				
				power = pow(num, i);
				power1 = pow((inputarray[num]-j*power), 2);
				sum+= power1;

				if(num==2)
				{
					min = sum;
				}
			}
			
			if( sum < min )
			{	
				min = sum;
                daB = i;
                daA = j;
			}
		}
		


	}

	cout << daA << "  " << daB <<endl;


	return 0;
}
