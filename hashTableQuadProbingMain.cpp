//JOSEPH SEMBOWER
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <fstream>
using namespace std;
/*
 * Node Type Declaration
 */
enum EntryType {Legitimate, Empty, Deleted};
/*
 * Node Declaration
 */
struct HashNode
{
    int element;
    enum EntryType info;
};
/*
 * Table Declaration
 */
struct HashTable
{
    int size;
    HashNode *table;
    int Collisions = 0;
    public:
    float insertTimes[400];
    float searchTimes[400];
    int testData[40000];
};
/*
 * Returns whether n is prime or not
 */
   bool isPrime(int number){
        if (number == 2 || number == 3)
            return true;

        if (number % 2 == 0 || number % 3 == 0)
            return false;

        int divisor = 6;
        while (divisor * divisor - 2 * divisor + 1 <= number)
        {

            if (number % (divisor - 1) == 0)
                return false;

            if (number % (divisor + 1) == 0)
                return false;

            divisor += 6;

        }

        return true;

    }
/*
 * Finding next prime size of the table
 */
    int nextPrime(int a){
        while (!isPrime(++a)){ }
        return a;
    }
/*
 * Function To Generate Hash
 */
int HashFunc(int key, int size)
{
    return key % size;
}
/*
 * Function to Initialize Table
 */
HashTable *initializeTable(int size)
{
    HashTable *htable;
    htable = new HashTable;
    if (htable == NULL)
    {
        cout<<"Out of Space"<<endl;
        return NULL;
    }
    htable->size = nextPrime(size);
    htable->table = new HashNode [htable->size];
    if (htable->table == NULL)
    {
        cout<<"Table Size Too Small"<<endl;
        return NULL;
    }
    for (int i = 0; i < htable->size; i++)
    {
        htable->table[i].info = Empty;
        htable->table[i].element = NULL;
    }
    return htable;
}
/*
 * Function to Find Element at a key
 */
int Find(int key, HashTable *htable)
{
    int pos = HashFunc(key, htable->size);
    int collisions = 0;
    while (htable->table[pos].info != Empty &&      //This goes on to check if the nodes are empty, used for rehasing the table
           htable->table[pos].element != key)
           
    {
        htable->Collisions++;
        pos = pos + 2 * ++collisions -1;
        if (pos >= htable->size)
            pos = pos - htable->size;
    }
    return pos;
}
/*
 * Function to Insert Element into a key
 */
void Insert(int key, HashTable *htable)
{
    int pos = Find(key, htable);
    if (htable->table[pos].info != Legitimate)  //if the node is legitimate, it means its already in the table, just needs to be rehashed
    {
        htable->table[pos].info = Legitimate;
        htable->table[pos].element = key;
    }
}
/*
 * Function to Rehash the Table
 */
HashTable *Rehash(HashTable *htable) //rehasing the table to increase the size for quadratic probing
{
    int size = htable->size;
    HashNode *table = htable->table;
    htable = initializeTable(2 * size);
    for (int i = 0; i < size; i++)
    {
        if (table[i].info == Legitimate)
            Insert(table[i].element, htable);
    }
    free(table);
    return htable;
}
/*
 * Function to Retrieve Hash Table
 */
void Retrieve(HashTable *htable)
{
    for (int i = 0; i < htable->size; i++)
    {
        int value = htable->table[i].element;
        if (!value)
            cout<<"Position: "<<i + 1<<" Element: Null"<<endl;
        else
            cout<<"Position: "<<i + 1<<" Element: "<<value<<endl;
    }
 
}

	void readFile(string fileName, HashTable *htable){
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
			htable->testData[counter] = stoi(line); //add everything into the int array for all the values to time how long it takes to insert them into the data structure
			counter++;
		}
        myFile.close();
	}

    void printTestData(HashTable *ht)
    {
        for (int i = 0; i < 40000; i++)
        {
            cout << ht->testData[i] << endl;
        }
    }

int main()
{
    int value, size, pos, i = 1;
    int choice;
    HashTable *htable;

    htable = initializeTable(40009);
    cout<<"Size of Hash Table: "<<nextPrime(size);

    //arrays for inserting, searching, and getting test data
        int testData[40009];
        float InsertTimesA[400];
        float SearchTimesA[400];


        //reading in the first file
		ifstream myFile;
		myFile.open("dataSetA.csv");
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
        myFile.close();

    for (int j = 0; j < 4000; j++)
    {
        Insert(testData[j], htable);

    }

   Retrieve(htable);









            //need to insert elements into the hash table

            /*
            if (i > htable->size)
            {
                cout<<"Table is Full, Rehash the table"<<endl;
            }
            */
            //Insert(value, htable);
            //Retrieve(htable);

            //htable = Rehash(htable);

           // exit(1);

       
    
    return 0;
}