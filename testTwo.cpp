#include <bits/stdc++.h>

using namespace std;

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

int main()
{
    // Initialize random seed
    srand(time(0));

    int len = 10;
    int uniqueDjb2Count = 0;
    int uniqueJenkinsCount = 0;

    // Set to store unique hash values
    unordered_set<unsigned long> djb2Hashes;
    unordered_set<unsigned long> jenkinsHashes;

    for (int i = 0; i < 100; i++)
    {
        string randomString = generateRandomWord(len);
        unsigned long djb2HashValue = djb2_hash(randomString) % 199;
        unsigned long jenkinsHashValue = jenkins_hash(randomString) % 199;

        // Check uniqueness and update counts
        if (djb2Hashes.find(djb2HashValue) == djb2Hashes.end())
        {
            djb2Hashes.insert(djb2HashValue);
            uniqueDjb2Count++;
        }

        if (jenkinsHashes.find(jenkinsHashValue) == jenkinsHashes.end())
        {
            jenkinsHashes.insert(jenkinsHashValue);
            uniqueJenkinsCount++;       
        }

        cout << randomString << "\t" << djb2HashValue << "\t" << jenkinsHashValue << "\n";
    }

    cout << "Number of unique DJB2 hash values: " << uniqueDjb2Count << endl;
    cout << "Number of unique Jenkins hash values: " << uniqueJenkinsCount << endl;

    return 0;
}
