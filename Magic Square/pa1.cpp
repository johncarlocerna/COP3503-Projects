//Name: Johncarlo Cerna
//UFID: 1897-1649
//Assignment 1: Magic Squares
#include <iostream>
#include <iomanip>
#include "pa1.h"

using namespace std;

int checkEntry(int numInput);
//function to check the entry for a valid number of rows/columns


void matrixSums(int matrixSize, int magicSquare[][15]);
//function to display the sums of rows, columns, and diagonals to prove indenticality
int main(){
    
    int numInput; //number that is entered; possibly valid or invalid

    int validNumber = 0; //number that fits the constraints of the program
    
    int magicArray[15][15] = {0}; //array must be initialized empty first
    
    cout << "Enter the size of a magic square: ";
    
    cin >> numInput;  //takes in input
    
    cout << endl;

    validNumber = checkEntry(numInput); //runs the checkEntry function and checks to see if the number fits the constraints

    //I used the Siamese method Algorithm to calculate the magic square, since this program only needs to work for odd-numbered squares.
	int rows;
    int cols;
    int row_x = 0;
    int col_y = (validNumber - 1) / 2;
    magicArray[row_x][col_y] = 1;

    for (rows = 2; rows <= validNumber * validNumber; rows++){  //siamese algorithm
        row_x--;
        col_y++;
        if (row_x < 0 && col_y == validNumber){
           row_x = row_x + 2;
           col_y--;
        }
        if (row_x < 0){
           row_x = validNumber - 1;
        }
        if (col_y >= validNumber){
           col_y = 0;
        }
        if (magicArray[row_x][col_y] != 0){
           row_x = row_x + 2;
           col_y = col_y - 1;
        }
        magicArray[row_x][col_y] = rows;
    }
    
    cout << endl;
	for(int iteration = 1; iteration <=4; iteration++){ //iterates 4 times for 4 different magic squares
		cout << "Magic Square #" << iteration << " is: " << endl;		
		//prints the matrix
		for(rows = 0;rows < validNumber;rows++){
			for(cols = 0; cols < validNumber; cols++){
				cout << setw(5) << magicArray[rows][cols];
			}
			cout << endl;
		}
		cout << endl;
		// function call to check if all rows, columns,and diagonals add to the same number
		matrixSums(validNumber, magicArray);
		cout << endl;
			if(iteration != 4){ //if the iteration is 4, no need to run this part of the code.
		int temp;
		for (int rows = 0; rows<validNumber/2; rows++){ //runs until the iterations reach the half of the size of the matrix
        for (int cols = rows; cols<validNumber-rows-1; cols++){
                temp=magicArray[rows][cols]; //saves first array place into a temporary integer
                magicArray[rows][cols] = magicArray[cols][validNumber-rows-1];  //original array index overwritten to horizontally opposite index
                magicArray[cols][validNumber-rows-1] = magicArray[validNumber-rows-1][validNumber-cols-1]; // horizontally opposite index overwritten to its vertically opposite index
                magicArray[validNumber-rows-1][validNumber-cols-1] = magicArray[validNumber-cols-1][rows]; // vertically opposite index overwritten to its horizontally opposite index
                magicArray[validNumber-cols-1][rows] = temp; //the previous index is overwritten to the first index.
                //This code turns the matrix 90 degrees, creating a new magic square. Repeats 3 times.
			}
        }
}
	}
}


