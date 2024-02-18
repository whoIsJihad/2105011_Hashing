
#include <bits/stdc++.h>
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
    int deleteCount;
    int currMaxChainLen;
    int size_limit;

public:
    separateChaining(int size, int maxChainLen, int funcFlag)
    {
        int c = closestPrime(size);
        myVec.resize(c);
        this->size = c;
        this->size_limit = c;
        this->funcFlag = funcFlag;
        this->maxChainLen = maxChainLen;
        currMaxChainLen = 0;
        insertCount = 0;
        deleteCount = 0;
        totalProbe = 0;
        numCollision=0;
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
            // totalProbe++;
            if (myVec[index].size() > currMaxChainLen)
                currMaxChainLen = myVec[index].size();
        }
        else
        {
            // totalProbe += this->size + 1;
            numCollision++;
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

        int probe = 0;

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
                deleteCount++;
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

    vector<list<pair<string, int>>> getMyVec()
    {
        return myVec;
    }
    int getNumCollision()
    {
        return numCollision;
    }

    int getCurrMaxChainLen()
    {
        return currMaxChainLen;
    }
    int getDeletecount()
    {
        return deleteCount;
    }

    unsigned long getSize()
    {
        return size;
    }

    int getInsertCount()
    {
        return insertCount;
    }

    int getFuncFlag()
    {
        return funcFlag;
    }

    int getTotalProbe()
    {
        return totalProbe;
    }

    void rehashing_insert()
    {
        int c = closestPrime(2 * size);
        vector<list<pair<string, int>>> myVecNew(c);

        for (auto &lst : myVec)
        {
            for (auto it = lst.begin(); it != lst.end(); ++it)
            {
                unsigned long index;
                if (funcFlag == 1)
                {
                    index = djb2_hash(it->first) % c;
                }
                else if (funcFlag == 2)
                {
                    index = jenkins_hash(it->first) % c;
                }

                myVecNew[index].push_back(*it);
            }
        }

        myVec = myVecNew;
        size = c;

        // Update currMaxChainLen
        currMaxChainLen = 0;
        for (auto &lst : myVec)
        {
            if (lst.size() > currMaxChainLen)
                currMaxChainLen = lst.size();
        }
    }

    void rehashing_delete()
    {
        int c = closestPrime(size / 2);
        vector<list<pair<string, int>>> myVecNew(c);

        for (auto &lst : myVec)
        {
            for (auto it = lst.begin(); it != lst.end(); ++it)
            {
                unsigned long index;
                if (funcFlag == 1)
                {
                    index = djb2_hash(it->first) % c;
                }
                else if (funcFlag == 2)
                {
                    index = jenkins_hash(it->first) % c;
                }

                myVecNew[index].push_back(*it);
            }
        }

        myVec = myVecNew;
        size = c;

        // Update currMaxChainLen
        currMaxChainLen = 0;
        for (auto &lst : myVec)
        {
            if (lst.size() > currMaxChainLen)
                currMaxChainLen = lst.size();
        }
    }
    int getMaxChainLength()
    {
        return maxChainLen;
    }

    string generateRandomWord(int length)
    {
        const string charset = "abcdefghijklmnopqrstuvwxyz";
        const int charsetLength = charset.length();
        string word;

        // Generate random characters
        for (int i = 0; i < length; ++i)
        {
            word += charset[rand() % charsetLength];
        }

        return word;
    }

    unsigned long djb2_hash(const std::string &str)
    {
        unsigned long hash = 5381;
        for (char c : str)
        {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash;
    }

    unsigned long jenkins_hash(const std::string &key)
    {
        unsigned long hash = 0;
        for (char c : key)
        {
            hash += static_cast<unsigned long>(c);
            hash += hash << 10;
            hash ^= hash >> 6;
        }
        hash += hash << 3;
        hash ^= hash >> 11;
        hash += hash << 15;
        return hash;
    }

    unsigned long bernstein_hash(const std::string &str)
    {
        unsigned long hash = 5381;
        for (char c : str)
        {
            hash = 33 * hash + static_cast<unsigned long>(c);
        }
        return hash;
    }

    bool isPrime(int n)
    {
        if (n <= 1)
            return false;
        if (n <= 3)
            return true;

        if (n % 2 == 0 || n % 3 == 0)
            return false;

        for (int i = 5; i * i <= n; i += 6)
        {
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        }

        return true;
    }

    int closestPrime(int n)
    {
        // If n itself is prime, return n
        if (isPrime(n))
            return n;

        // Find closest larger prime
        int larger = n;
        while (!isPrime(larger))
        {
            larger++;
        }

        // Find closest smaller prime
        int smaller = n;
        while (!isPrime(smaller))
        {
            smaller--;
        }

        // Determine which one is closer
        if (abs(n - larger) < abs(n - smaller))
            return larger;
        else
            return smaller;
    }
};
