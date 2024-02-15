#include<bits/stdc++.h>
#include "neededFunc.cpp"
using namespace std;

class doubleHashing
{
    vector<pair<string, int>> myVec;
    int size;
    int numCollision;
    int totalProbe;
    int funcFlag;

public:
    doubleHashing(int size, int funcFlag)
    {
        int c = closestPrime(size);
        myVec.resize(c, make_pair("", 0)); // Initialize all elements with empty key and zero value
        this->size = c;
        this->funcFlag = funcFlag;
        totalProbe = 0;
        numCollision = 0;
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

        index = (mainHash + i * auxHash) % size;

        while (!myVec[index].first.empty()) // Check for an empty key
        {
            i++;
            index = (mainHash + i * auxHash) % size;
            numCollision++;
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

        index = (mainHash + i * auxHash) % size;

        while (!myVec[index].first.empty()) // Check for an empty key
        {
            if (myVec[index].first == key)
            {
                totalProbe += (i + 1);
                return myVec[index].second;
            }
            i++;
            index = (mainHash + i * auxHash) % size;
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

        index = (mainHash + i * auxHash) % size;

        while (!myVec[index].first.empty()) // Check for an empty key
        {
            if (myVec[index].first == key)
            {
                myVec[index] = make_pair("", 0); // Mark the slot as empty
                return;
            }
            i++;
            index = (mainHash + i * auxHash) % size;
        }
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

