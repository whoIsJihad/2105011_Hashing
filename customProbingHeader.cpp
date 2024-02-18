
#include <bits/stdc++.h>

using namespace std;

class customProbing
{
    vector<pair<string, int>> myVec;
    int size;
    int currentSize;
    int numCollision;
    int totalProbe;
    int funcFlag;
    int C1, C2;

public:
    customProbing(int size, int funcFlag)
    {
        int c = closestPrime(size);
        myVec.resize(c, make_pair("", 0)); // Initialize all elements with empty key and zero value
        this->size = c;
        currentSize = 0;
        this->funcFlag = funcFlag;
        totalProbe = 0;
        numCollision = 0;
        C1 = 1;
        C2 = 1;
    }

    void insertVal(string key)
    {
       if(currentSize>=size) return;
       if(findVal(key)!=-1) return;

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
            if(i>size)
            {
                //cout << "Cant Find Slot .. Table Not Full" << endl;
                return;
            }
            index = (mainHash + C1 * i * auxHash + C2 * i * i) % size;
            numCollision++;
        }

        
        myVec[index] = make_pair(key, size + 1); // Mark the slot as occupied
        currentSize++;
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

        while (!myVec[index].first.empty())
        {
            if(i>size) return -1;                 
            if (myVec[index].first == key)
            {
                totalProbe += (i + 1);
                return myVec[index].second;
            }
            i++;
            index = (mainHash + C1 * i * auxHash + C2 * i * i) % size;
        }
        return -1;
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
    int getNumCollisions() const
    {
        return numCollision;
    }

    int getTotalProbes() const
    {
        return totalProbe;
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
