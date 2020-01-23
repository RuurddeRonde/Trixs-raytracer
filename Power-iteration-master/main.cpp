//
//  main.cpp
//
//  Created by Furkanicus on 10/04/15.
//  Copyright (c) 2015 M.Furkan Akyurek. All rights reserved.
//  Learnrope.com
// First Argument for file name
// Second argument for the tolerance
// Third argument for the name of the output file


#include <fstream> // for file access
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cmath> // For Absolute function
#include "matrix.h" // Matrix Class


using namespace std;

int main(int argc, char * argv[]) {
    
    //                        //
    /* Start of Opening Files */
    //                        //
    {
    if (argc > 1)
    {
        cout << "argv[1] = " << argv[1] << endl;
        cout << "argv[2] = " << argv[2] << endl;
        cout << "argv[3] = " << argv[3] << endl;
    }
    else
    {
        cout << "No file name entered. Abort! Abort!";
        return -1;
    }
    
    //----------------------------------//
    
    // String to Double Conversion
    string::size_type indexer;
    double tolerance = std::stod(argv[2],&indexer);

    // Initialization of A matrix
    Matrix A(argv[1]);
    int row = A.getRows();
    
    // Pick an X vector
    // 1,2,3,4........
    Matrix X(row,1,1.0);
    for (unsigned i = 1; i <= row; i++)
    {
        X(i-1,0) = i;
    }
    
    // Error code defined to quit program when complex eigenvalues
    int errorCode;
    double eigenvalue = 0.0;
    
    // Power Iteration to find an eigenvalue
    tie(X, eigenvalue, errorCode) = A.powerIter(row, tolerance);
    
    // Quit if flag raised
    if (errorCode == -1)
    {
        return -1;
    }
    cout << "First Eigenvalue: " << eigenvalue << endl;
        // Outputting X Vector
        ofstream myfile_x (argv[3]);
        myfile_x << "Eigenvalue#1:" << eigenvalue << endl;
        myfile_x << endl;
        for (unsigned i = 0; i < row; i++)
        {
            myfile_x << "X" << i << " = " << X(i,0) << endl;
            myfile_x << endl;
        }
        X.print();
    
    // Beginning to execute deflation
    double eigenvalue2;
    Matrix X1(row,1,1.0); // Another X Vector for Power Iteration
    Matrix A2 = A.deflation(X, eigenvalue); // Deflation Applied
    // Power Iteration for Second one
    tie(X1, eigenvalue2, errorCode) = A2.powerIter(row, tolerance);
    if (errorCode == -1)
    {
        return -1;
    }
    //                           //
    /* Start of Output Functions */
    //                           //
    

    myfile_x << "Eigenvalue#2:" << eigenvalue2 << endl;
    cout << "Second Eigenvalue: " << eigenvalue2 << endl;
    myfile_x.close();
    
    }
    return 0;
}
