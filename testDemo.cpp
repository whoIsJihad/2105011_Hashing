#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    vector<pair<string,int>>myVector;
    
    // Add elements to the vector
    myVector.push_back({"",0});
    if(myVector[0].first.empty()) cout<<"yes.empty\n";

    
    // Access and print the elements
    for (const auto& pair : myVector) {
        cout << "String: " << pair.first << ", Integer: " << pair.second << endl;
    }
    
    return 0;
}
