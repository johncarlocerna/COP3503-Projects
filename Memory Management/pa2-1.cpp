#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <cstdio>
#include <string>
#include <cstring>
#include "pa2.h"

using namespace std;

int main(int gitpumped, char * chooseAlgorithm[] ){
    bool bestOrWorst = true;   //If it is true, it runs best fit, false is worst fit. Runs best by default.
    string algDetermine = "";
    List list; //generic list declaration
    
    if (chooseAlgorithm[1] != 0) {     //
        algDetermine = chooseAlgorithm[1];        //
    }
	if (algDetermine == "best") {
        printf("Using best fit algorithm\n");
    }
    else if (algDetermine == "worst") {
        bestOrWorst = false;
        printf("Using worst fit algorithm\n");
    }

    else { 
        printf("Defaulting to the best fit algorithm\n\n");
    }
    int selection; //picks the option for the menu    
    printf("   1. Add Program\n");  /*Console menu*/
    printf("   2. Kill Program\n");
    printf("   3. Fragmentation\n");
    printf("   4. Print Memory\n");
    printf("   5. Exit\n");

  int pages;
  int maximumSize =0;
   while(selection!=5){  //exit if selection is 5, otherwise loop
	   printf("\nchoice - ");
	   cin >> selection; 
		if(selection == 1){ //if 1, add a program into memory
			string name;
			double size;
			cout << "Program name - ";
                cin >> name;      
                cout << "Program size (KB) - ";
                cin >> size;                
                pages = ceil(size/4.0); //divides by 4 for each page and rounds up  
                if(pages > 32 - maximumSize){ //if the available memory is smaller than the attempted amount of pages, display error
					cout << "Error, not enough memory for Program " << name << " .\n";
				}	
                else if (bestOrWorst) { //if bestOrWorst is true, use best algorithm. Otherwise, use worst.     
                    if (list.bestAlgorithm(name, pages)) {      
                        for (int i = list.goodIndex; i < pages + list.goodIndex; i++) { //while the bestAlgorithm runs...    
                            list.pageReplacer(name, i); //replace the pages.    
                        }
                        cout << "Program " << name << " added successfully: " << pages << " page(s) added.\n"; 
                        maximumSize = maximumSize + pages;
                    } 
                    else { 
                    }
                } else {    
                    if ( list.worstAlgorithm(name, pages)) {
                        for (int i = list.badIndex; i < pages + list.badIndex; i++) {//works the same as the best algorithm, but with the worstAlgorithm function
                            list.pageReplacer(name, i);
                        }
                        cout << "Program " << name << " successfully added, " << pages << " pages used.\n";
                        maximumSize = maximumSize + pages;
                    } 
                    else {
                    }
				  }
                }
		else if(selection ==2){ //if 2, attempt to delete a program
			string name;
                cout << "Program name to delete: ";
                cin >> name;
                
                if (list.killProgram(name, pages)) //run killprogram function
                {    
                    cout << "\nProgram " << name << " deleted," << pages -1 << " page(s) reclaimed.\n"; //if successful, kill the program
                maximumSize = maximumSize - pages;
                } 

                else 
                {
                    cout << "\n" << name << " was not found in memory. \n"; //if not found, fail.
                }
		}
		else if(selection==3){ //if 3, get the number of fragments.
			printf("\n");
            list.getFragments();
		}
		else if(selection==4){ //if 4, display the list of nodes
			printf("\n");
            list.displayList();
		}
		else if(selection==5){ //if 5, exit the program and pat yourself on the back.
            return 0;
		}
		else{ //if the selection was not 1,2,3,4, or 5, display invalid input and make the user try again.
			cout << selection << " Invalid input\n";  
		}
	}
}
