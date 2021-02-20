//new linked list class
//Joseph Sembower

#include <iostream>

struct Node
{
    int key;
    Node *next;
};

class LinkedList
{
   Node *head;

   int testData[40000];
   float insertTimes[400];
   float searchTimes[400];

   public:
   LinkedList();
   void insert(int n);
   int search(int n);
   void display();
   void readFile(std::string fileName);

   int getTestData(int n);

    void timeInsertAndSearch();
    void timeInsert();
    void doSearch();
    void printInsertTimes();
    void printSearchTimes();

    float getInsertTimes(int p);
    float getSearchTimes(int p);

    void writeFile(std::string fileName);

};