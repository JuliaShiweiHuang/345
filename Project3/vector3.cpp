#include <iostream>
#include <vector>
#include <string> 

using namespace std;

struct job 
{
    char op; 
    int PID;
    int size;
};

int main()
{
    vector<job> x;
    job y;
    size_t vectorSize; 

    y.op = 'A';
    y.PID = 1;
    y.size = 20000;
    x.push_back(y);     


    cout << "my vector contains:" << endl;
    for (int i = 0, vectorSize = x.size(); i < vectorSize; ++i)
    {
        cout << "\tOP: " << x[i].op <<endl;
        cout << "\tPID: " << x[i].PID <<endl;
        cout << "\tSize: " << x[i].size << endl;

    }
    return 0;
}