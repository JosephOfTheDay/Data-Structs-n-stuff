//hash table with quadratic probing

#include <iostream>
#include <chrono>
#include<cstdlib>
using namespace std;


struct Node{
    int key;
    Node *next;

    public:
        Node(int n){
            this->key = n;
            this->next = nullptr;
        }

        int getKey(){
            return key;
        }

        Node *getNext(){
            return next;
        }

        void setNode(Node *next){
            this->next = next;
        }
};

class HashTable
{
    Node* *table;
    int size;
    int elementCount;
    int collisions;

    //search insert and testData arrays
    int testData[40009];
    float searchTimes[400];
    float insertTimes[400];

    public:
        HashTable(int s);
        int hashFunc(int n);
        bool isPrime(int n);
        int nextPrime(int n);
        void insert(int n);
        bool isFull();

};

