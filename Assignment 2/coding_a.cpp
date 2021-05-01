#include<bits/stdc++.h>
using namespace std;


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[],int arr2c[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
    int k = l;

    while (i < n1 && j < n2)
    {   //comparison is made based on arr2 values i.e movie end time values
        if (arr2c[L[i]] <= arr2c[R[j]])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int arr[],int arr2c[], int l, int r)
{
    if (l < r)
    {

        // Same as (l+r)/2, but avoids
        // overflow for large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr,arr2c, l, m);
        mergeSort(arr,arr2c, m + 1, r);

        merge(arr,arr2c, l, m, r);
    }
}



int main(){
    // for getting input from input.txt
    freopen("coding-question-a.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output-a.txt", "w", stdout);
    int test=6;
    while(test--)
    {
        int N;
    cin>>N;
    int arr1[N];// array for start times
    int arr2[N];// array for end times
    int arr3[N];// index array for sorting the movies according to end time
    for(int i=0;i<N;i++){
        int a,b;
        cin>>a>>b;//taking inputs of start and end time
        arr1[i]=a;
        arr2[i]=b;
    }
    for(int i=0;i<N;i++){
        arr3[i]=i;//initializing index array(indices of arr2) arr2 to sort afterwards
    }
    mergeSort(arr3,arr2,0,N-1);// mergesort to sort according to end time values and store indexes in arr3

    int cnt=1;// count initialized to 1 to always include first movie
    int pivot=arr2[arr3[0]];
    for(int i=1;i<N;i++){// //if starting time of current movie is greater than ending time of previous movie, we add 1 to the ans
        if(arr1[arr3[i]]>=pivot){
            cnt+=1;
            pivot=arr2[arr3[i]];


        }
    }
    cout<<cnt<<endl;
}
}
