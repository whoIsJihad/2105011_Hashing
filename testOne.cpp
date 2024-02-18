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

    int size;
    int funcFlag;
    int maxChainLen;

    cin >> size >> maxChainLen;

    // Test separateChaining
    separateChaining HT_separateChainingOne(size, maxChainLen, 1);
    separateChaining HT_separateChainingTwo(size, maxChainLen, 2);

    std::cout << "Testing separateChaining:" << std::endl;

    vector<string> allStrings(10000);

    // inserting 10000 words
    for (int i = 0; i < 10000; ++i)
    {
        string randomString = generateRandomWord(rand() % 6 + 5);

        // storing the random string
        allStrings[i] = randomString;

        // two Hashtable for two hash function
        HT_separateChainingOne.insertVal(randomString);
        HT_separateChainingTwo.insertVal(randomString);

        bool conditionOne = HT_separateChainingOne.getInsertCount() != 0 && HT_separateChainingOne.getInsertCount() % 100 == 0;
        bool conditionTwo = HT_separateChainingOne.getCurrMaxChainLen() > HT_separateChainingOne.getMaxChainLength();
        if (conditionOne && conditionTwo)
        {
            HT_separateChainingOne.rehashing_insert();
        }

        bool _conditionOne = HT_separateChainingTwo.getInsertCount() != 0 && HT_separateChainingTwo.getInsertCount() % 100 == 0;
        bool _conditionTwo = HT_separateChainingTwo.getCurrMaxChainLen() > HT_separateChainingTwo.getMaxChainLength();
        if (_conditionOne && _conditionTwo)
        {
            HT_separateChainingTwo.rehashing_insert();
        }
    }

    // searching for any 1000 of the word

    for (int i = 0; i < 1000; i++)
    {
        int randomIndex = rand() % 10000;
        string wordToSearch = allStrings[randomIndex];

        cout << wordToSearch << " " << HT_separateChainingOne.findVal(wordToSearch) << " " << HT_separateChainingTwo.findVal(wordToSearch) << endl;

        // Perform search operation here
    }

    cout << "Avg probe for Hash function One : " << HT_separateChainingOne.getTotalProbe() / 1000 << endl;
    cout << "Current Max chain Length : " << HT_separateChainingOne.getCurrMaxChainLen() << endl;

    cout << "Avg probe for Hash function Two : " << HT_separateChainingTwo.getTotalProbe() / 1000 << endl;

    cout << "Current Max chain Length : " << HT_separateChainingTwo.getCurrMaxChainLen() << endl;
    // deleteing  1000 words

    for (int i = 0; i < 1000; i++)
    {
        int randomIndex = rand() % 10000;
        string wordToDelete = allStrings[randomIndex];
        HT_separateChainingOne.deleteVal(wordToDelete);
        HT_separateChainingTwo.deleteVal(wordToDelete);

        bool condOne = HT_separateChainingOne.getDeletecount() != 0 && HT_separateChainingTwo.getDeletecount() % 100 == 0;
        bool condTwo = HT_separateChainingOne.getCurrMaxChainLen() < HT_separateChainingTwo.getMaxChainLength() * 0.8;

        if (condOne && condTwo)
        {
            HT_separateChainingOne.rehashing_delete();
        }
        bool _condOne = HT_separateChainingTwo.getDeletecount() != 0 && HT_separateChainingTwo.getDeletecount() % 100 == 0;
        bool _condTwo = HT_separateChainingTwo.getCurrMaxChainLen() < HT_separateChainingTwo.getMaxChainLength() * 0.8;

        if (_condOne && _condTwo)
        {
            HT_separateChainingTwo.rehashing_delete();
        }
    }
    return 0;
}
