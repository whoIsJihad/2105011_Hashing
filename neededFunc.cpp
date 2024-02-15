#include<bits/stdc++.h>
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
