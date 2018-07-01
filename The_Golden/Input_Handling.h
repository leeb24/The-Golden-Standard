//
//  Input_Handling.h
//  PA4
//
//  Created by ByoungSul lee on 2016. 12. 9..
//  Copyright © 2016년 ByoungSul lee. All rights reserved.
//

#ifndef Input_Handling_h
#define Input_Handling_h
#include <iostream>
using namespace std;

class Invalid_Input
{
    public :
    
        Invalid_Input(char* in_ptr) : msg_ptr(in_ptr)
        {
        
        }
    
        const char* const msg_ptr;
    
    private :
    
    Invalid_Input();
    
    
};


#endif /* Input_Handling_h */
