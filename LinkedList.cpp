//Linked List cpp file Joseph Sembower
//4/20/20

#include "LinkedList.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
using namespace std;


LinkedList :: LinkedList()
{
    head = NULL;
}

void LinkedList::insert(int addData)
{
    Node* n = new Node;
    n->next = NULL;
    n->key = addData;

    //if there already is things in the list
    if (head!=NULL)                         //if head is pointing to an object, something is in the list
    {
        Node *curr = head;    //points to what head is pointing to
        while(curr->next != NULL)   //while not at the end of the list
        {
            curr = curr->next; // advances the curr pointer until last node in the list, last node is set to null
        }
        curr->next = n; //points to null
    }
    else    
    {
        head = n; //placing it at the front of the list
    }
    //cout << "Node added to the linked list: "  << n->key << endl;
}

Node* LinkedList :: search(int value)
{
    Node *temp = head;
    Node *returnNode = nullptr;
    bool found = false;

    while(!found && temp != nullptr)
    {
        if (temp->key == value)
        {
            found = true;
            returnNode = temp;
        }
        else
        {
            temp = temp->next;
        }
    }
    if (returnNode)
    {
        //cout << "Found the node" << endl;     //dont need to print out that we found the node
        return returnNode;
    }
    return NULL; 
}

//search b for other file
Node* LinkedList :: searchB(int value)
{
    Node *temp = head;
    Node *returnNode = nullptr;
    bool found = false;

    while(!found && temp != nullptr)
    {
        if (temp->key == value)
        {
            found = true;
            returnNode = temp;
        }
        else
        {
            temp = temp->next;
        }
    }
    if (returnNode)
    {
        //cout << "Found the node" << endl;
    }
    return returnNode;
}


void LinkedList :: display()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->key << endl;
        temp = temp->next;
    }
}



//NEW READ FILE ONLY USE THIS ONE!!!!
void LinkedList :: readFile(string fileName)
{
    ifstream inFile;
    clock_t timer;
    inFile.open(fileName);
    if (inFile.fail()){
        cout << "could not open the file\n";
    }

    string line;
    int counter = 0;
    int otherCounter = 0;
    int otherCounter2 = 0;
    while(getline(inFile,line,',')){
        auto start = std::chrono::high_resolution_clock::now();
        if (counter % 100 == 0)
        {
            auto finish = std::chrono::high_resolution_clock::now();
            InsertA[otherCounter] = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
            otherCounter++;
        }  
        if (counter % 100 == 0){
            auto newTimer = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 100; i++){
            search(rand() % 99);
            }
            auto endTimer = std::chrono::high_resolution_clock::now();
            SearchA[otherCounter2] = std::chrono::duration_cast<std::chrono::milliseconds>(endTimer-newTimer).count();
            otherCounter2++;
        }

        
        this->insert(stoi(line));
        counter++;
    }
    

    inFile.close();
}

//USE THIS READ FILE ONLY^^^^^


void LinkedList :: printInsertAResults()
{
    for (int i = 0; i < 400; i++){
        cout << "Time at indice: " << i<<"  "<< (float)InsertA[i] << endl;
    }
}

//print b results insert
void LinkedList :: printInsertBResults()
{
    for (int i = 0; i < 400; i++){
        cout << "Time at indice: " << i<<"  "<< (float)InsertB[i] << endl;
    }
}

//print time results
void LinkedList :: printSearchResultsA(){

    for (int i = 0; i < 400; i++){
        cout << "Time at indice: " << i<<"  "<< (float)SearchA[i] << endl;
    }
}

//write to the files



void LinkedList :: printSearchResultsB(){

    for (int i = 0; i < 400; i++){
        cout << "Time at indice: " << i<<"  "<< (float)SearchB[i] << endl;
    }
}

//write functions for inserting values

void LinkedList :: writeSearch(string fileName)
{
    ofstream outFile;

    outFile.open(fileName);

    for (int i = 0; i < 400; i++)
    {
        outFile << SearchA[i] << endl;
    }
    outFile.close();
}

void LinkedList :: writeInsert(string fileName)
{
    ofstream outFile;

    outFile.open(fileName);

    for (int i = 0; i < 400; i++)
    {
        outFile << InsertA[i] << endl;
    }
    outFile.close();
}














/*
void LinkedList :: readFileA(string fileName)
{
    ifstream inFile;
    clock_t timer;
    inFile.open(fileName);
    if (inFile.fail()){
        cout << "could not open the file\n";
    }

    string line;
    int counter = 0;
    int otherCounter = 0;
    while(getline(inFile,line,',')){
        auto start = std::chrono::high_resolution_clock::now();
        if (counter % 100 == 0)
        {
            auto finish = std::chrono::high_resolution_clock::now();
            InsertA[otherCounter] = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();

            //create a second clock to get how long the searching take
            auto start2 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 100; i++){
                searchA(rand() % 99+(otherCounter*100));
            }
            auto finish2 = std::chrono::high_resolution_clock::now();
            SearchA[otherCounter] = std::chrono::duration_cast<std::chrono::microseconds>(finish2-start2).count();
            otherCounter++;
        }

        
        this->insert(stoi(line));
        counter++;
        //
    }
    

    inFile.close();
}
*/

//read file B
/*
void LinkedList :: readFileB(string fileName)
{
    ifstream inFile;
    inFile.open(fileName);
    if (inFile.fail()){
        cout << "could not open the file\n";
    }

    string line;
    int counter = 0;
    int otherCounter = 0;
    for (int x = 0; x < 40000; x++){
        getline(inFile, line, ',');
        auto start = std::chrono::high_resolution_clock::now();
        if (x % 100 == 0)
        {
            auto finish = std::chrono::high_resolution_clock::now();
            //cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
            InsertB[otherCounter] = std::chrono::duration_cast<std::chrono::seconds>(finish-start).count();
            

            //create a second clock to get how long the searching take
            auto start2 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 100; i++){
                searchB(rand() % 99+(otherCounter*100));
            }
            auto finish2 = std::chrono::high_resolution_clock::now();
            SearchB[otherCounter] = std::chrono::duration_cast<std::chrono::seconds>(finish2-start2).count();
            otherCounter++;
        }

        
        this->insert(stoi(line));
        //
    }
    

    inFile.close();
} 

*/