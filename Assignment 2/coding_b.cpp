#include <iostream>
using namespace std;
// i have used 2 arrays, one to store frequency and other to store and sort the colors//

// frequency array to store the frequency of color i at index i//
int freq[1005];
// index array to store index(color) values and sort them acc. to freq values from freq array//
int index[1005];

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
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
    { /* here i have compared the values in the freq array at corresponding indexes*/
        if (freq[L[i]] <= freq[R[j]])
        {
            arr[k] = L[i];/* storing the sorted indexes(colors) acc. to freq in the index array*/
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
void mergeSort(int arr[], int l, int r)
{     if (l < r){

        // Same as (l+r)/2, but avoids
        // overflow for large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main()
{
    int n;
    cin>>n;
    int e;// to store current input color//
    /* building the frequency array from inputs*/
    for(int i=1;i<=n;i++){cin>>e;++freq[e];}
    /* initializing the index array with colors from 1 to 1000 to sort afterwards*/
    for(int i=1;i<=1000;i++)index[i]=i;
    /* sort the index array acc. to freq of colors in freq array*/
    mergeSort(index,1,1000);
    /* printing the colors(from index array) in sorted order acc. to frequency and then keys*/
    for(int i=1;i<=1000;i++){while(freq[index[i]]--)cout<<index[i]<<" ";}
    //colors which have zero freq will not enter while loop and continue to next one//

    return 0;
}


