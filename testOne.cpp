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
pair<int, int> ReportFunction1(int funcFlag, int maxCL, int size);
pair<int, int> ReportFunction2(int funcFlag, int size);
pair<int, int> ReportFunction3(int funcFlag, int size);

void printReport(pair<int, int> &p, int size)
{
    cout << "Report for size " << size << endl;
    cout << "Average probe: " << p.first << endl;
    cout << "Number of collision: " << p.second << endl;
}
int main()
{
    srand(time(0)); // Initialize random seed
    freopen("output.txt", "w", stdout);

    cout << "Testing Seprate Chaining :" << endl;

    pair<int, int> report_s_5000 = ReportFunction1(1, 5, 5000);
    pair<int, int> report_s_10000 = ReportFunction1(1, 5, 5000);
    pair<int, int> report_s_20000 = ReportFunction1(1, 5, 5000);

    printReport(report_s_5000, 5000);
    printReport(report_s_10000, 10000);
    printReport(report_s_20000, 20000);

    pair<int, int> report_d_5000 = ReportFunction2(1, 5000);
    pair<int, int> report_d_10000 = ReportFunction2(1, 10000);
    pair<int, int> report_d_20000 = ReportFunction2(1, 20000);

    cout << "\n\nTesting Double Hashing :" << endl;
    printReport(report_d_5000, 5000);
    printReport(report_d_10000, 10000);
    printReport(report_d_20000, 20000);
    cout << "*********************\n";

    cout << "\n\nTesting Custom Probing :" << endl;
    pair<int, int> report_c_5000 = ReportFunction3(1, 5000);
    pair<int, int> report_c_10000 = ReportFunction3(1, 10000);
    pair<int, int> report_c_20000 = ReportFunction3(1, 20000);

    printReport(report_c_5000, 5000);
    printReport(report_c_10000, 10000);
    printReport(report_c_20000, 20000);
    return 0;
}

pair<int, int> ReportFunction1(int funcFlag, int maxCL, int size)
{
    vector<string> allStrings(10000);
    separateChaining ht(size, maxCL, funcFlag);

    for (int i = 0; i < 10000; ++i)
    {
        string randomString = generateRandomWord(rand() % 6 + 5);

        // storing the random string
        allStrings[i] = randomString;

        // two Hashtable for two hash function
        ht.insertVal(randomString);

        bool conditionOne = ht.getInsertCount() != 0 && ht.getInsertCount() % 100 == 0;
        bool conditionTwo = ht.getCurrMaxChainLen() > ht.getMaxChainLength();
        if (conditionOne && conditionTwo)
        {
            ht.rehashing_insert();
        }
    }

    for (int i = 0; i < 1000; i++)
    {
        int randomIndex = rand() % 10000;
        string wordToSearch = allStrings[randomIndex];
        int ind = ht.findVal(wordToSearch);
    }
    // deleteing  1000 words
    for (int i = 0; i < 1000; i++)
    {
        int randomIndex = rand() % 10000;
        string wordToDelete = allStrings[randomIndex];
        ht.deleteVal(wordToDelete);

        bool condOne = ht.getDeletecount() != 0 && ht.getDeletecount() % 100 == 0;
        bool condTwo = ht.getCurrMaxChainLen() < ht.getMaxChainLength() * 0.8;

        if (condOne && condTwo)
        {
            ht.rehashing_delete();
        }
    }

    return make_pair(1.0 * ht.getTotalProbe() / 1000, 1.0 * ht.getNumCollision());
}

pair<int, int> ReportFunction2(int funcFlag, int size)

{
    vector<string> allStrings(10000);

    doubleHashing dh(size, funcFlag);
    for (int i = 0; i < 10000; ++i)
    {
        string randomString = generateRandomWord(rand() % 6 + 5);

        // storing the random string
        allStrings[i] = randomString;
        // two Hashtable for two hash function
        dh.insertVal(randomString);
    }
    // finding 1000 words
    for (int i = 0; i < 1000; i++)
    {
        int randomIndex = rand() % 10000;
        string wordToSearch = allStrings[randomIndex];
        int ind = dh.findVal(wordToSearch);
    }
    // deleteing  1000 words
    for (int i = 0; i < 1000; i++)
    {
        int randomIndex = rand() % 10000;
        string wordToDelete = allStrings[randomIndex];
        dh.deleteVal(wordToDelete);
    }
    return make_pair(1.0 * dh.getTotalProbes() / 1000, dh.getNumCollisions());
}

pair<int, int> ReportFunction3(int funcFlag, int size)

{
    vector<string> allStrings(10000);

    customProbing cp(size, funcFlag);
    for (int i = 0; i < 10000; ++i)
    {
        string randomString = generateRandomWord(rand() % 6 + 5);

        // storing the random string
        allStrings[i] = randomString;
        // Hashtable for custom probing
        cp.insertVal(randomString);
    }
    // finding 1000 words
    for (int i = 0; i < 1000; i++)
    {
        int randomIndex = rand() % 10000;
        string wordToSearch = allStrings[randomIndex];
        int ind = cp.findVal(wordToSearch);
    }
    // deleting 1000 words
    for (int i = 0; i < 1000; i++)
    {
        int randomIndex = rand() % 10000;
        string wordToDelete = allStrings[randomIndex];
        cp.deleteVal(wordToDelete);
    }
    return make_pair(1.0 * cp.getTotalProbes() / 1000, cp.getNumCollisions());
}