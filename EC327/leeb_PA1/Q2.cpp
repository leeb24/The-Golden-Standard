#include <iostream>
#include <math.h>       /* ceil */
#include <iomanip>      // Setprecision (prints to two decimals in this file)

//Included library for the round up and two decimal places in the output

using namespace std;

int main(){
    
    float OBill;
    float TaxR;
    int TL;
    int PT;
    float Totaltip;
    float TotalpostT;
    
    
    // intput Original Bill and  Tax Rate
    
    
    cout << " Enter the original bill amount: " ;
    
    cin >> OBill;
    
    cout << " Enter the tax Rate %: " ;

    cin >> TaxR;
    
    double TotalPretip = (OBill + ( (OBill/100) * TaxR )) ;
    
    cout << " Enter tip level (1= 15%, 2= 20%, 3= 25%): " ;
    
    cin >> TL;

    
    // While (if its not 1 or 2 or 3 , go back to typing Tip level)
    
    while (TL != 1 && TL !=2 && TL !=3 ) // if the input is invalid input again
    {
        
        cout << "Enter Valid Tip Level: ";
        
        cin >> TL;
        
    }
    
    int Tiprate ;
    
    // start if statements with TL= 1,2,3
    
    if (TL == 1) {
        
        
        Tiprate = 15 ;
        
        
    }
    
    else if (TL == 2) {
        
        
        Tiprate = 20 ;
        
        
    }
    
    else if (TL == 3) {
        
        
        Tiprate = 25 ;
        
        
    }
    
    // Ask Post TAX
    
    cout << " Tip on post-tax amount? (1= yes, 2= No): " ;
    
    cin >> PT;
    
    // Process inputs of post-tax
    
    while (PT != 1 && PT !=2 ) // if the input is invalid input again
    {
        
        cout << "Enter Valid number: ";
        
        cin >> PT;
        
    }
    
    if ( PT == 1 ){
        
        Totaltip =  ((TotalPretip/100)* Tiprate);
        
        TotalpostT = (TotalPretip + Totaltip);
    }
    
    else if ( PT == 2 ){
        
        Totaltip = ( (OBill/100) * Tiprate );
        
        
        TotalpostT = ( TotalPretip + Totaltip );
    }
    
    
    cout << " The total bill pre-tip is:$" << fixed << setprecision(2) << ceil(TotalPretip*100)/100 << endl; // round up and two decimals
    
    cout << " The total tip is:$"<< fixed << setprecision(2) << ceil(Totaltip*100)/100 << endl;
    
    cout << " The total bill post-tip is:$"<< fixed << setprecision(2) << ceil(TotalpostT*100)/100 << endl;
    
    
    
    
   
    
        
        
        
        return 0;
    
}
