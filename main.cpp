/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>

#include "generic.h"
#include "blasing.h"

using namespace std;

int test_vector_initializations()
{
    int out = 0;
    
    cout << "1) Init_list and array initializations!" << endl;
    dvec v1({0.0, 1.0, 2.0, 3.0, 4.0, 5.0});
    double ar[] = {5.0, 4.0, 3.0, 2.0, 1.0, 0.0};
    dvec v2(6, ar);
    daxpy(v1, v2);
    cout << "   Six fives: ";
    v1.print();
    for (int i = 0; i < 6; i++) {
        if(v2[i] != 5.0) out++;
    }
    
    cout << "2) vector from vector initializations!" << endl;
    dvec v3(6, 0.2);
    dvec v4(v3);
    cout << "   This should come out as 6.0: " << ddot(v2, v4) << endl;
    if(ddot(v2, v4) != 6.0) out++;
    
    if (not out)
    {
        cout << "Test passed!" << endl;
    }
    else
    {
        cout << "Errorcode: " << out << endl;
        throw out;
    }
}

int main()
{
    test_vector_initializations();
    
    
    return 0;
}