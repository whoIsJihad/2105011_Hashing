#include <bits/stdc++.h>
#include "neededFunc.cpp"
using namespace std;

class separateChaining
{
    vector<list<pair<string, int>>> myVec;
    int size;
    int maxChainLen;
    int numCollision;
    int totalProbe;
    int funcFlag;
    int insertCount;
    int currMaxChainLen;

public:
    separateChaining(int size, int maxChainLen, int funcFlag)
    {
        int c = closestPrime(size);
        myVec.resize(c);
        this->size = c;
        this->funcFlag = funcFlag;
        this->maxChainLen = maxChainLen;
        currMaxChainLen = 0;
        insertCount = 0;
    }

    void insertVal(string key)
    {
        unsigned long index;
        if (findVal(key) != -1)
            return;
        insertCount++;
        if (funcFlag == 1)
        {
            index = djb2_hash(key) % size;
        }
        if (funcFlag == 2)
        {
            index = jenkins_hash(key) % size;
        }

        if (myVec[index].empty())
        {
            myVec[index].push_back({key, size + 1});
            totalProbe++;
            if (myVec[index].size() > currMaxChainLen)
                currMaxChainLen = myVec[index].size();
        }
        else
        {
            totalProbe += this->size + 1;
            myVec[index].push_back({key, size + 1});

            // Update currMaxChainLen if necessary
            if (myVec[index].size() > currMaxChainLen)
                currMaxChainLen = myVec[index].size();
        }
    }

    int findVal(string key)
    {
        unsigned long index;

        if (funcFlag == 1)
        {
            index = djb2_hash(key) % size;
        }
        else if (funcFlag == 2)
        {
            index = jenkins_hash(key) % size;
        }

        list<pair<string, int>> &myList = myVec[index];

        int probe = 1;

        for (auto it = myList.begin(); it != myList.end(); ++it)
        {
            probe++;

            if (it->first == key)
            {
                totalProbe += probe;
                return it->second;
            }
        }
        totalProbe += probe;
        return -1; // Key not found
    }

    void deleteVal(string key)
    {

        unsigned long index;
        if (funcFlag == 1)
        {
            index = djb2_hash(key) % size;
        }
        else if (funcFlag == 2)
        {
            index = jenkins_hash(key) % size;
        }

        list<pair<string, int>> &myList = myVec[index];

        for (auto it = myList.begin(); it != myList.end(); ++it)
        {
            if (it->first == key)
            {
                myList.erase(it);
                size--;

                // Update currMaxChainLen if necessary
                if (myList.size() == currMaxChainLen + 1)
                {
                    for (auto &lst : myVec)
                    {
                        if (lst.size() > currMaxChainLen)
                            currMaxChainLen = lst.size();
                    }
                }

                return;
            }
        }
    }

    int getMaxChainLength() const
    {
        return currMaxChainLen;
    }

    void rehashing()
    {
        if (currMaxChainLen <= maxChainLen)
        {
            return;
        }

        int c = closestPrime(2 * size);
        vector<list<pair<string, int>>> myVecNew(c);


        for(auto x:myVec){
            
        }

    }
};
