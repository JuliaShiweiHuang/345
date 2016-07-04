#include <iostream>
#include <string>
#include <fstream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int* TemporaryArray;

void MakeMerge(int* MakeMergeArray, int Left, int Middle, int Right){
    int i = Left, j = Middle + 1;

  for (int step = 0; step < Right - Left + 1; ++step){
        if ((j > Right || (i <= Middle && MakeMergeArray[i] < MakeMergeArray[j])))
        {
            TemporaryArray[step] = MakeMergeArray[i];
            ++i;
        }
        else
        {
            TemporaryArray[step] = MakeMergeArray[j];
            ++j;
        }
  }

  for (int step = 0; step < Right - Left + 1; ++step)
  {
        MakeMergeArray[Left + step] = TemporaryArray[step];
  }

}


int main () {
  cout << "this is main" << endl;
  int *myArray = new int[4]; 
  myArray[] = {2,9,4,2};
  MakeMerge(myArray, 1, 2, 3);

  return 0;
}