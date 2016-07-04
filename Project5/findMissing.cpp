#include<stdio.h>

int findFirstMissing(int array[], int start , int end){
    
    if(end<=start+1){
        return start+1;//return the missing number
    }
    else{
        
        int mid = start + (end-start)/2;
        
        if((array[mid] - array[start]) != (mid-start))
            return findFirstMissing(array, start, mid);
        else
            return findFirstMissing(array, mid+1, end);
        
    }
}

// driver program to test above function
int main()
{
  int arr[] = {1, 2, 3, 4, 6, 7, 8, 9};
  int n = sizeof(arr)/sizeof(arr[0]);
  printf(" First missing element is %d",
           findFirstMissing(arr, 0, n-1));
  getchar();
  return 0;
}
