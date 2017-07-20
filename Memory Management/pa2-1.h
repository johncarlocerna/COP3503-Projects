//Johncarlo Cerna
//1897-1649
//Project 2
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

struct Node {
    
    Node(string d) : nodeList(d), next(NULL) {}     //constructs node
    string nodeList;
    Node *next;
    
};

struct List {

    int goodIndex;       //index for bestAlgorithm
    int badIndex;        //index for worstAlgorithm
    int max;			 //max memory used for worstAlg
    int min;			 //min memory used for bestAlg
    int count;			 //size of memory when tracking the max or min
    int first;			 //variable used to keep track of pointer
    int second;          //variable used to keep track of first and pointer
    Node *head;			 //beginning of list
    Node *tail;          //end of list
    
    List(string nodeList) {
        head = NULL; //head and tail start off with nothing
        tail = NULL;
        head = new Node(nodeList);
        tail = head;
    }

    List() {
        head = NULL;
        tail = NULL;
        for(int i = 0; i < 32; i++){ //32 'free' pages       
            push("Free");
        }
        
    };


    int listSize() {    //returns list size
        
        int count = 0;
        Node * current = head;
        while(current != NULL){   //increases until the next node is null, then returns the size
            current = current->next;
            ++count;
        }
        return count;   //return list size
    }
    
    bool emptyList() {   
        
        return listSize() == 0;
    }
    
    void push(string nodeList) {    //function used for pushing values to the list.   
        
        if(head == NULL) {
            head = new Node(nodeList);
            tail = head;
        }
        else{
            tail -> next = new Node(nodeList);
            tail = tail->next;
        }
    }

    bool killProgram(string nodeList, int pages) {  
        Node * current = head;
        bool programFound = false; //inherently false
        for(int i = 0; i < 32; i++) {
            
            if(current -> nodeList == nodeList) { //if program is found in memory, change to free node and turn bool programFound into true
                current -> nodeList = "Free";
                programFound = true;
            }
            if(current->next != NULL) { //keep going until the next node is null.
                current = current->next;
            }
        }
        return programFound; //return t or f.
    }
    
   void getFragments(){     //method to find the fragments of the code
        
        Node * current = head;
        string name;    
        int count = 0; //start count from 0
        
        for(int i = 0; i < 32; i++) { //traverse the list
            
            if(current -> nodeList == "Free" && name != "Free") {  //if the node is free and the name isn't 'free', change name to free and add to counter
                name = "Free";
                count++;
            }
            else if(current->nodeList != name) {     //if the node does not equal the name, make name equal the node
                name = current -> nodeList;   
            }
            else if(current->next != NULL) {     //if it is not null, set current to current ->next.
                current = current->next;   
            }
        }
        
        cout << "There are " << count << " fragments." << endl;   //print out fragments
    }
    
        
    void displayList() {  //prints the list
        
        if(head == NULL) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node * current = head;{    
        }
        while(current != NULL) { //while not null, keep going
            
            for(int i = 0; i < 8; i++) {
                
                if(current != NULL) { //if not null and the node isn't free, go on
                    
                    if(current->nodeList != "Free") {
                        cout << current -> nodeList << "   ";
                    }
                    else {
                        cout << current -> nodeList << " ";
                    }
                    current = current->next;
                }
                
            }
            cout << "\n \n";   
        }     
    }
    void pageReplacer(string nodeList, int place) {  //replaces pages      
        Node * current = head;     
        for(int i = 0; i < place; i++) {
            current = current -> next; //
        }       
        current -> nodeList = nodeList;
    }    

    bool bestAlgorithm(string name, int size) {      
        Node * current = head;
        goodIndex = 0;
        min = 0;
        count = 0; 
        first=0;
        second=0;  
        bool firstTime=true;  //when this function runs the first time, min should equal count and the goodIndex should equal first.   
        for(int i = 0; current-> next!=NULL; i++) {          
            if(current -> nodeList == name) {    
                cout <<"Error, Program " << name << " is already running.";
                return false;
            }           
            if(current->nodeList == "Free") { //if the next available node is free, start running/
                first=second;    
                    if(current->next != NULL) {
                        count++;
                        current = current -> next;
                        second++;
                    }
                    while(current->nodeList=="Free"){ //traverses the list to find the smallest memory place.
						if(current->next != NULL) {
                        count++;
                        current = current -> next;
                        second++;
                    }
                    else{
						break; //when encountering a node that is not free, break.
					}
						}
                if(firstTime){ //if this is the first time running the best algorithm, automatically use the first available spot as the min.
					min=count;
					goodIndex=first;
					firstTime=false;
				
			    }
			else{
                if(count < min) {       //when the current size is below the previous minimum size, overwrite the min. 
                    min = count;
                    goodIndex=first;  
                }
			}               
                count = 0;
            }           
            else{
                current = current->next;
                second++;
            }
        }
				first=0;
               return true;
    }
     bool worstAlgorithm(string name, int size) { 
        Node * current = head;
        badIndex = 0;
        max = 0;
        count = 0; 
        first=0;
        second=0;       
        for(int i = 0; current-> next!=NULL; i++) {          
            if(current -> nodeList == name) {    //if the program name entered is already in memory, display error.
                cout <<"Error, Program " << name << " is already running.";
                return false;
            }           
            if(current->nodeList == "Free") { //if the node is free, start running algorithm
                first=second;
                    
                    if(current->next != NULL) {//this code tries to find the memory gap that is the largest.
                        count++;
                        current = current -> next;
                        second++;
                    }
                    while(current->nodeList=="Free"){ //while loop of the above
						if(current->next != NULL) {
                        count++;
                        current = current -> next;
                        second++;
                    }
                    else{
						break;
					}
						}
                if(count > max) {       //when the current size exceeds the previous max size, overwrite the max size.
                    max = count;
                    badIndex=first;  
                }               
                count = 0;
            }           
            else{
                current = current->next;
                second++;
            }
        }
               first=0;
               return true;
    }
   
};
