//JOSEPH SEMBOWER

#include <iostream>
#include <fstream>
#include <chrono>
#include<cstdlib>
using namespace std;



struct Node {
	int key;
	Node *next;


public:
	//Node functions essentially helper functions
	Node(int n)
	{
		this->key = n;
		this->next = nullptr;
	}

	int getKey(){
		return key;
	}

	Node *getNext(){
		return next;
	}

	void setNext(Node *next){
		this->next = next;
	}
};

//Hash table class

class HashTable{

	Node* *table;
	int size;
	int collisions;
	int searchCollisions;
	int testData[400009];
	float searchTimes[400];
	float insertTimes[400];
	int Collisions1[400];
	int Collisions2[400];
public:
	HashTable(int s){
		size = s;
		table = new Node*[size];
		for (int i = 0; i < size; i++){
			table[i] = nullptr;
		}
	}

	int hashFunc(int n){
		return (n % size);
	}


	//search function
	int search(int key){
		int index = hashFunc(key);

		if (table[index] == NULL){
			return -1;
		}
		else{
			searchCollisions++;
			Node *n = table[index];
			while(n != NULL and n->getKey() != key){

				n = n->getNext();
			}
			if (n == NULL){
				return -1;
			}
			else{
				return n->key;
			}
		}
	}
	//insert function
	void insert(int key){
		int index = hashFunc(key);

		if (table[index] == NULL){
			table[index] = new Node(key);
		}
		else{
			Node *n = table[index];
			while (n->getNext() != NULL){
				n = n->getNext();
			}
			Node *m = new Node(key);
			n->setNext(m);
			collisions++;
		}

	}

	//read the file
	void readFile(string fileName){
		ifstream myFile;
		myFile.open(fileName);
		//to see if the file magically cannot open
		if (myFile.fail())
		{
			cout << "could not open the file.";
		}

		string line;
		int counter = 0;

		while(getline(myFile, line, ',')){
			testData[counter] = stoi(line); //add everything into the int array for all the values to time how long it takes to insert them into the data structure
			counter++;
		}
	}

	//helper functions for the hashtable class
	int getTestData(int index)
	{
		return testData[index];
	}

	void timeInsertAndSearch()
	{
		auto start = std::chrono::high_resolution_clock::now();
		int insertIndex = 0;
		int searchIndex = 0;
		for (int i = 0; i < 40000; i++){
			if (i % 100 == 0){
				auto end = std::chrono::high_resolution_clock::now();
				insertTimes[insertIndex] = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
				insertIndex++;
				auto start = std::chrono::high_resolution_clock::now();
				Collisions1[searchIndex] = collisions;
				collisions = 0;
			}

			if (i % 100 == 0){
				auto startSearchTimer = std::chrono::high_resolution_clock::now();
				for (int j = 0; j < 99 + (searchIndex*100); j++){
					this->search(testData[rand() % 99 + (searchIndex*100)]);
				}
				auto endSearchTimer = std::chrono::high_resolution_clock::now();
				searchTimes[searchIndex] = std::chrono::duration_cast<std::chrono::microseconds>(endSearchTimer-startSearchTimer).count();
				searchIndex++;
				Collisions2[searchIndex] = searchCollisions;
				searchCollisions = 0;
			}
		this->insert(this->getTestData(i));
		}
	}

	void printInsertTimes()
	{
		for (int i = 0; i < 400; i++){
			cout << insertTimes[i] << endl;
		}
	}
	
	void printSearchTimes()
	{
		for (int i = 0; i < 400; i++){
			cout << searchTimes[i] << endl;
		}
	}

	float getSearchTimes(int index)
	{
		return searchTimes[index];
	}

	float getInsertTimes(int index)
	{
		return insertTimes[index];
	}

	//writes to a text file, spaced out by sections

	void writeFile(string fileName)
	{
		ofstream outFile;
		outFile.open(fileName);

		for (int x = 0; x < 400; x++){
			outFile << getInsertTimes(x) << endl;
		}
		outFile << endl;
		for (int y = 0; y < 400; y++){
			outFile << getSearchTimes(y) << endl;
		}
		outFile << endl;
		//inserting insertion collisions here
		for (int j = 0; j < 400; j++)
		{
			outFile << Collisions1[j] << endl;
		}

		outFile << endl;
		//inserting search collisions here
		for (int c = 0; c < 400; c++)
		{
			outFile << Collisions2[c] << endl;
		}


		outFile.close();
	}

	int getCollisions()
	{
		return collisions;
	}

	void printTable()
	{
		for (int i = 0; i < size; i++){
			cout << "index " << i << ": " << search(testData[i]) <<  endl;
		}
	}

	void printInsertCollisions()
	{
		for (int i= 0; i < 400; i++){
			cout << Collisions1[i] << endl;
		}
	}	

	void printSearchCollisions()
	{
		for (int i= 0; i < 400; i++){
			cout << Collisions2[i] << endl;
		}
	}

};

	
//MAIN FUNCTION


int main()
{
	HashTable SetA(40000);

	SetA.readFile("dataSetA.csv");
	SetA.timeInsertAndSearch();

	SetA.writeFile("insert_search_performance_HashTable_chaining_dataSetA.txt");

	

	HashTable SetB(40000);

	SetB.readFile("dataSetB.csv");
	SetB.timeInsertAndSearch();
	SetB.writeFile("insert_search_performance_HashTable_chaining_dataSetB.txt");


	SetB.printTable();

			
	
	return 0;
}



