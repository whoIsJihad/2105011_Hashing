#include <bits/stdc++.h>
#include "separateChainingHeader.cpp"
#include "doubleHashHeader.cpp"
#include "customProbingHeader.cpp"
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
int main()
{
    srand(time(0)); // Initialize random seed
    freopen("output.txt", "w", stdout);

    doubleHashing dh1(50, 1);
    doubleHashing dh2(50, 2);

    std::cout << "Testing Double Hashuing :" << std::endl;
    vector<string> allStrings(100);

    // inserting 10000 words
    for (int i = 0; i < 100; ++i)
    {
        string randomString = generateRandomWord(rand() % 6 + 5);

        // storing the random string
        allStrings[i] = randomString;

        // two Hashtable for two hash function
        dh1.insertVal(randomString);
        dh2.insertVal(randomString);
    }

    // searching for any 1000 of the word

    for (int i = 0; i < 10; i++)
    {
        int randomIndex = rand() % 100;
        string wordToSearch = allStrings[randomIndex];

        cout << wordToSearch << " " << dh1.findVal(wordToSearch) << " " << dh2.findVal(wordToSearch) << endl;
    }

    cout << "Avg probe for Hash function One : " << 1.0*dh1.getTotalProbes() / 10 << endl;
    cout << "Avg probe for Hash function Two : " << 1.0*dh2.getTotalProbes() / 10 << endl;
    // deleteing  1000 words

    for (int i = 0; i < 10; i++)
    {
        int randomIndex = rand() % 10000;
        string wordToDelete = allStrings[randomIndex];
        dh1.deleteVal(wordToDelete);
        dh2.deleteVal(wordToDelete);
    }

    return 0;
}
