#include <bits/stdc++.h>
#include "neededFunc.cpp"
#include "separateChainingHeader.cpp"
#include "doubleHashHeader.cpp"
#include "customProbingHeader.cpp"
using namespace std;


int main()
{
    srand(time(0)); // Initialize random seed

    int size = 100;
    int funcFlag = 1; // Use djb2_hash for Hash function
    int maxChainLen = 5;

    // Test separateChaining
    separateChaining myHashTable_separateChaining(size, maxChainLen, funcFlag);
    cout << "Testing separateChaining:" << endl;
    for (int i = 0; i < 100; ++i)
    {
        string randomString = generateRandomWord(10);
        myHashTable_separateChaining.insertVal(randomString);
    }
    cout << "Max Chain Length: " << myHashTable_separateChaining.getMaxChainLength() << endl;

    // Test doubleHashing
    funcFlag = 1; // Use djb2_hash for Hash function
    doubleHashing myHashTable_doubleHashing(size, funcFlag);
    cout << "\nTesting doubleHashing:" << endl;
    for (int i = 0; i < 100; ++i)
    {
        string randomString = generateRandomWord(10);
        myHashTable_doubleHashing.insertVal(randomString);
    }
    cout << "Number of Collisions: " << myHashTable_doubleHashing.getNumCollisions() << endl;
    cout << "Total Probes: " << myHashTable_doubleHashing.getTotalProbes() << endl;

    // Test customProbing
    funcFlag = 2; // Use jenkins_hash for Hash function
    customProbing myHashTable_customProbing(size,funcFlag);
    cout << "\nTesting customProbing:" << endl;
    for (int i = 0; i < 100; ++i)
    {
        string randomString = generateRandomWord(10);
        myHashTable_customProbing.insertVal(randomString);
    }
    cout << "Max Chain Length: " << myHashTable_customProbing.getMaxChainLength() << endl;

    return 0;
}
