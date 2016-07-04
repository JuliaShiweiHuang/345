#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h> /* printf */
#include <math.h>
#include <vector>

using namespace std;


class job{
private:
    int PID, size;

public:
    job(int inPID, int inSize) { PID = inPID; size = inSize; };

};


// std::vector<char> path;
// // ...
// for (std::vector<char>::const_iterator i = path.begin(); i != path.end(); ++i)
//     std::cout << *i << ' ';


int main()
{  
    std::vector <job> path;
    int PID, size;
    cin >> PID >> size;
    v.push_back(job(PID, size));
    for(int i=0; i<path.size(); ++i)
  		std::cout << path[i] << ' ';

    return 0;
   
}


// class treeNode {
// public:
// 	int value;
// 	treeNode(int integer){ value = integer; left = NULL; right = NULL; };
// 	friend class BinarySearchTree;
// protected:
// 	treeNode *left, *right, *parent;
// 	//other stuff
// };
