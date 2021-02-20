#include "hashTableQuadraticProbing.hpp"
#include <chrono>
#include<cstdlib>
using namespace std;

HashTable :: HashTable(int s){
    size = s;
    
}

int HashTable :: hashFunc(int n){
    return n % size;
}

//PRIME NUMBER FUNCTIONS
bool HashTable :: isPrime(int n){
    if (n == 2 || n == 3)
        return true;
    if (n == 1 || n % 2 == 0)
        return false;
    for (int i = 3; i * i <= n; i +=2)
        if (n % i == 0)
            return false;
    return true;
}

int HashTable :: nextPrime(int n){
    if (n <= 0)
        n == 3;
    if (n % 2 == 0)
        n++;
    for (;!isPrime( n ); n +=2);
        return n;
}





