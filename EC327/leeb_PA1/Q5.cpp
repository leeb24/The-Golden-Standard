#include <iostream>
#include <stdio.h>  //  For isalpha functionality
#include <ctype.h>  //  For isalpha functionality

using namespace std;




int main() {
    
    char letter;
    char Upper;
    
    cout << "Enter a letter: ";
    
    cin >> letter ; //INPUT
    
    if (isalpha(letter)) // IF LETTER
    {
        letter = toupper(letter); //CHANGE TO UPPERCASE
        
        if (letter == 'Z') //IF UPPERCASED LETTER IS Z OUTPUT A
        {
            letter = 'A';
            
            cout << "CRYPTO: "<< letter << endl;
            return 0;
        }
        
        Upper = letter + 1;// RAISE ASCII VALUE OF UPPERCASE LETTER+1
        
        
        cout << "CRYPTO: "<< Upper << endl;
        
        return 0;
        
    }
    
   
    
    else // IF OTHER INPUT OTHER THAN LETTER
    {
        cout << "YOU DID NOT ENTER A LETTER"<< endl;
        return 0;
    }
    
    
    
    
    
    return 0;
}
