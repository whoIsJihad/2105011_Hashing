#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

bool isPrime(int n);
int closestPrime(int n);

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

class separateChaining
{
    vector<list<pair<string, int>>> myVec;
    int size;
    int maxChainLen;
    int numCollision;
    int totalProbe;
    int funcFlag;
    int currMaxChainLen;

public:
    separateChaining(int size, int maxChainLen, int funcFlag)
    {
        myVec.resize(size);
        this->size = size;
        this->funcFlag = funcFlag;
        this->maxChainLen = maxChainLen;
        currMaxChainLen = 0;
    }

    void insertVal(string key)
    {
        unsigned long index;
        if (findVal(key) != -1)
            return;
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

        for (auto it = myList.begin(); it != myList.end(); ++it)
        {
            if (it->first == key)
            {
                return it->second;
            }
        }

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
                if (myList.size() == currMaxChainLen + 1) {
                    for (auto& lst : myVec) {
                        if (lst.size() > currMaxChainLen)
                            currMaxChainLen = lst.size();
                    }
                }

                return;
            }
        }
    }

    int getMaxChainLength() const {
        return currMaxChainLen;
    }
};

int main()
{
    // Initialize random seed
    srand(time(0));

    separateChaining myHashTable_djb2(100, 5, 1);

    // Test insertion and track maximum chain length
    int len = 10;
    for (int i = 0; i < 100; i++)
    {
        string randomString = generateRandomWord(len);
        myHashTable_djb2.insertVal(randomString);
        cout << "Current Max Chain Length: " << myHashTable_djb2.getMaxChainLength() << endl;
    }

    return 0;
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
