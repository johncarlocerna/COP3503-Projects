#ifndef pa1
#define pa1
#include <iostream>
using namespace std;
int checkEntry(int numInput){

    int invalidNum; //in case the value is not valid
    
    int validNumber = numInput; //in case the value is valid

    if (numInput < 3 || numInput % 2 == 0 || numInput > 15){ //if number is less than 3, greater than 15, or even, then display error
        cout << "Please Enter a Valid Number: ";
        cin >> invalidNum;
        validNumber = checkEntry(invalidNum); //go through the function again
    }

    //In the event of a valid number, return the number
    return validNumber;

}

void matrixSums(int matrixSize, int magicSquare[][15]){

    int rowSum = 0; //initializing and declaring the sum variables for the rows, columns, and diagonals.
    int colSum = 0; 
    int fdiagSum = 0; 
    int bdiagSum = 0; 

    cout << "Checking the sums of every row: ";

    // calculates the sum of the rows
    for (int rows = 0; rows < matrixSize; rows++){
        for (int cols = 0; cols < matrixSize; cols++){
            rowSum += magicSquare[rows][cols];
        }

        cout << " " << rowSum;
        rowSum = 0;
    }

    cout << endl;

    cout << "Checking the sums of every column: ";

    // calculates the sum of the columns
    for (int cols = 0; cols < matrixSize; cols++){
        for (int rows = 0; rows < matrixSize; rows++){
            colSum += magicSquare[rows][cols];
        }

        cout << " " << colSum;
        colSum = 0;
    }

    cout << endl;
    cout << "Checking the sums of every diagonal: ";
    // sums the forward diagonal (fdiag) and displays the output.
    for (int fdiag = 0; fdiag < matrixSize; fdiag++){
        fdiagSum += magicSquare[fdiag][fdiag];
    }
    cout << fdiagSum << " ";
    // sums the backward diagonal (bdiag) and displays the output.
    for (int bdiag = matrixSize - 1; bdiag >= 0; bdiag--){
        bdiagSum += magicSquare[bdiag][bdiag];
    }
    cout << bdiagSum;
} //end program

#endif // pa1
