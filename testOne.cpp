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


class myHashtable{
    vector<list<string,int>> myVec;

    public:

    myHashtable(int n){
        
    } 
};

int main()
{
    // Initialize random seed
    srand(time(0));

    int len = 10;
    for (int i = 0; i < 100; i++)
    {
        string randomString = generateRandomWord(len);
        cout << randomString << "\t" << djb2_hash(randomString) % 37 << "\t" << jenkins_hash(randomString) % 37 << "\n";
    }


    
}