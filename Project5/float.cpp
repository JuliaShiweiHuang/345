#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <iomanip>
#include <set>


using namespace std;


int main() {

    double num;
    
    printf("Enter double: ");
    cout << "this is for scanf line: "; scanf("%lf", &num);
    cout << "this is for printf line: "; printf("%.3lf", num);
    
    // getch();
    return 0;
}
