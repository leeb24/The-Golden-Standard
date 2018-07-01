#include <iostream>
#include <cmath>
#include <stdlib.h>

// includede libraries for abs & power functionality

using namespace std;

int main(){
    // Coordinate inputs
    float X1;
    float Y1;
    float X2;
    float Y2;
    float X3;
    float Y3;
    
    cout << " Enter Three Coordinates " << endl;
    
    // Slope
    
    cin >> X1 >> Y1 >> X2 >> Y2 >> X3 >> Y3 ;

    
    float slope = (Y2-Y1)/(X2-X1);
    
    
    
    // Line EQ Constants
    
    double A = - slope;
    int B = 1;
    double C = -Y1 - (slope*X1);
    
    
    
    
    
    // Shortest Distance from X3,Y3
    
    
    float R = ( (A * X3 ) + ( B * Y3 ) + C );
    float D = ( pow( ( ( A*A ) + ( B*B ) ), (double) 0.5) );
    float Result = abs( R / D );
    
    cout << " The shortest distance for (" << X3 << "," << Y3 << ")" << " to the line composed of (" << X1 << "," << Y1 << ")" << " and (" << X2 << "," << Y2 << ") is " << Result << endl;
    
    
    return 0;
    
    
    
}
