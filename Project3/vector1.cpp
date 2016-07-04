#include <iostream>
#include <vector>
#include <string> // string would be welcome here!

using namespace std;

struct student // the typedef thing is not necessary in C++
{
    string            name; // i find this "using namespace ..." thing a bad habit, it can make code harder to read
    int                            age;
    vector<std::string>       subject;
};

int main()
{
    vector<student>    x;
    student                 y;
    size_t                  size; // calling vector.size() every iterations is a bad idea, performance-wise
    size_t                  size_subj; // same

    y.name = "John";
    y.age = 9;
    y.subject.push_back("biology");
    y.subject.push_back("math");
    y.subject.push_back("art");
    x.push_back(y);     

    // y.name = "Bon";
    // y.age = 12;
    // y.subject.clear(); // clear subjects of the other student
    // y.subject.push_back("history");
    // y.subject.push_back("physics");
    // x.push_back(y);     

    cout << "my vector contains:";
    for (int i = 0, size = x.size(); i < size; ++i)
    {
        size_subj = x[i].subject.size();
        // I prefer using operator[] when I'm sure nothing can go wrong
        cout << "Student # " << i + 1 <<endl;
        cout << "\tname: " << x[i].name <<endl;
        cout << "\tage: " << x[i].age <<endl;
        cout << "\tSubjects: ";
        for (int j = 0; j < size_subj; ++j) {   
            cout << x[i].subject[j];
            cout << endl;
        }

    }
    return 0;
}