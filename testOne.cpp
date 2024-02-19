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
pair<float, int> ReportFunction1(int funcFlag, int maxCL, int size);
pair<float, int> ReportFunction2(int funcFlag, int size);
pair<float, int> ReportFunction3(int funcFlag, int size);

void printReport(pair<float, int> &p, int size)
{
    cout << "Report for size " << size << endl;
    cout << "Average probe: " << p.first << endl;
    cout << "Number of collision: " << p.second << endl;
}

int main()
{
    srand(time(0)); // Initialize random seed
    freopen("output.txt", "w", stdout);

    // Print table header
    std::cout << std::left << std::setw(10) << "| Size" << std::setw(20) << "| Collision Method"
              << std::setw(25) << "| Collision (Hash1)" << std::setw(25)
              << "| Probe (Hash1)" << std::setw(25) << "| Collision (Hash2)"
              << std::setw(25) << "| Probe (Hash2) |" << std::endl;
    std::cout << std::setw(140) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;

    // Generate and print reports for different sizes
    int sizes[] = {5000, 10000, 20000};
    for (int size : sizes)
    {
        // Reports for Separate Chaining
        std::pair<float, int> report_s1 = ReportFunction1(1, 5, size);
        std::pair<float, int> report_s2 = ReportFunction1(2, 5, size);

        // Reports for Double Hashing
        std::pair<float, int> report_d1 = ReportFunction2(1, size);
        std::pair<float, int> report_d2 = ReportFunction2(2, size);

        // Reports for Custom Probing
        std::pair<float, int> report_c1 = ReportFunction3(1, size);
        std::pair<float, int> report_c2 = ReportFunction3(2, size);

        // Print reports for each size
        std::cout << "| " << std::setw(8) << size << " | Separate Chaining"
                  << std::setw(15) << " | " << report_s1.second << std::setw(20) << " \t| "
                  << report_s1.first << std::setw(15) << " | " << report_s2.second
                  << std::setw(20) << "\t | " << report_s2.first << " |" << std::endl;
        std::cout << "| " << std::setw(8) << ""
                  << " | Double Hashing"
                  << std::setw(17) << "    | " << report_d1.second << std::setw(20) << "\t| "
                  << report_d1.first << std::setw(15) << " | " << report_d2.second
                  << std::setw(20) << "\t | " << report_d2.first << " |" << std::endl;
        std::cout << "| " << std::setw(8) << ""
                  << " | Custom Probing"
                  << std::setw(17) << "    | " << report_c1.second << std::setw(20) << " \t| "
                  << report_c1.first << std::setw(15) << " | " << report_c2.second
                  << std::setw(20) << " \t| " << report_c2.first << " |" << std::endl;

        // Print horizontal line
        std::cout << std::setw(140) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;
    }

    return 0;
}

pair<float, int> ReportFunction1(int funcFlag, int maxCL, int size)
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

    return make_pair(1.0 * ht.getTotalProbe() / 1000.0, 1.0 * ht.getNumCollision());
}

pair<float, int> ReportFunction2(int funcFlag, int size)

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
    return make_pair(1.0 * dh.getTotalProbes() / 1000.0, dh.getNumCollisions());
}

pair<float, int> ReportFunction3(int funcFlag, int size)

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
    return make_pair(1.0 * cp.getTotalProbes() / 1000.0, cp.getNumCollisions());
}