#include<bits/stdc++.h>
#include "neededFunc.cpp"
using namespace std;

class customProbing
{
    vector<pair<string, int>> myVec;
    int size;
    int numCollision;
    int totalProbe;
    int funcFlag;
    int C1, C2;

public:
    customProbing(int size,int funcFlag)
    {
        int c = closestPrime(size);
        myVec.resize(c, make_pair("", 0)); // Initialize all elements with empty key and zero value
        this->size = c;
        this->funcFlag = funcFlag;
        totalProbe = 0;
        numCollision = 0;
        C1 = 1;
        C2 = 1;
    }

    void insertVal(string key)
    {
        unsigned long index;
        int i = 0;
        unsigned long mainHash;
        if (funcFlag == 1)
        {
            mainHash = djb2_hash(key);
        }
        else if (funcFlag == 2)
        {
            mainHash = jenkins_hash(key);
        }
        unsigned long auxHash = bernstein_hash(key);

        index = (mainHash + C1 * i * auxHash + C2 * i * i) % size;

        while (!myVec[index].first.empty()) // Check for an empty key
        {
            i++;
            index = (mainHash + C1 * i * auxHash + C2 * i * i) % size;
           // numCollision++;
        }

        myVec[index] = make_pair(key, size + 1); // Mark the slot as occupied
        totalProbe += (i + 1);
    }

    int findVal(string key)
    {
        unsigned long index;
        int i = 0;
        unsigned long mainHash;
        if (funcFlag == 1)
        {
            mainHash = djb2_hash(key);
        }
        else if (funcFlag == 2)
        {
            mainHash = jenkins_hash(key);
        }
        unsigned long auxHash = bernstein_hash(key);

        index = (mainHash + C1 * i * auxHash + C2 * i * i) % size;

        while (!myVec[index].first.empty()) // Check for an empty key
        {
            if (myVec[index].first == key)
            {
                totalProbe += (i + 1);
                return myVec[index].second;
            }
            i++;
            index = (mainHash + C1 * i * auxHash + C2 * i * i) % size;
        }
        return -1; // Key not found
    }

    void deleteVal(string key)
    {
        unsigned long index;
        int i = 0;
        unsigned long mainHash;
        if (funcFlag == 1)
        {
            mainHash = djb2_hash(key);
        }
        else if (funcFlag == 2)
        {
            mainHash = jenkins_hash(key);
        }
        unsigned long auxHash = bernstein_hash(key);

        index = (mainHash + C1 * i * auxHash + C2 * i * i) % size;

        while (!myVec[index].first.empty()) // Check for an empty key
        {
            if (myVec[index].first == key)
            {
                myVec[index] = make_pair("", 0); // Mark the slot as empty
                return;
            }
            i++;
            index = (mainHash + C1 * i * auxHash + C2 * i * i) % size;
        }
    }

    int getMaxChainLength() const
    {
        return 0; // No chaining in custom probing
    }

    int getNumCollisions() const
    {
        return numCollision;
    }

    int getTotalProbes() const
    {
        return totalProbe;
    }
};
