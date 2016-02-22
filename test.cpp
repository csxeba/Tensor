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
    int error = 0;
    
    cout << "--- TESTING VECTOR INITIALIZATION METHODS ---" << endl;
    cout << "1) Init_list and array initializations!" << endl;
    dvec v1({0.0, 1.0, 2.0, 3.0, 4.0, 5.0});
    double ar[6] = {5.0, 4.0, 3.0, 2.0, 1.0, 0.0};
    dvec v2(6, ar);
    cout << "Range 5-0: ";
    v2.print();
    daxpy(v1, v2, 1.0);
    cout << "   Six fives: ";
    v2.print();
    for (int i = 0; i < 6; i++) {
        if(v2[i] != 5.0) error++;
    }
    
    cout << "2) vector from vector initializations!" << endl;
    dvec v3(6, 0.2);
    dvec v4(v3);
    cout << "   This should come out as 6: " << ddot(v2, v4) << endl;
    if(ddot(v2, v4) != 6.0) error++;
    
    if (not error)
    {
        cout << "Test passed!" << endl << endl;
    }
    else
    {
        cout << "Test failed with errorcode: " << error << endl;
        throw error;
    }
}

void test_matrix_initializations()
{
    int error = 0;
    cout << "--- TESTING MATRIX INITIALIZATION METHODS ---" << endl;
    cout << "1) Default value vs vector folding!" << endl;
    dmatrix2 m1(3, 5, 1.0);
    dvec initvector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    dmatrix2 m2(5, 2, initvector);
    dmatrix2 res(3, 2, 0.0);
    
    dgemm(m1, m2, res);
    
    cout << "   This should come out as 25, 30 / 25, 30, / 25, 30" << endl;
    res.print();
    for (int i = 0; i < res.Vector::size(); i++) {
        if (i % 2 == 0){
            if (res.Vector<double>::at(i) != 25) error ++;}
        else {
            if (res.Vector<double>::at(i) != 30) error ++;}
    }
    
    cout << "2) Testing the copy constructor!" << endl;
    
    dmatrix2 m3(m1);
    
    cout << "   Should be 15 -> " << dasum(m1) << endl;
    if (dasum(m1) != 15.0) error++;
    
    if (error)
    {
        cout << "Test failed with errorcode: " << error << endl;
        throw error;
    }
    else
    {
        cout << "Test passed!" << endl << endl;
    }
}

int main()
{
    //test_vector_initializations();
    test_matrix_initializations();
    
    
    return 0;
}