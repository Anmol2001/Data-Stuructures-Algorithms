#include <bits/stdc++.h>
using namespace std;

// Two Dequeue (Double ended queue) based
// method for getting difference of
// all subarrays of size k
void print_difference(int arr[], int n, int k)
{

    // Creating two Double Ended Queues,
    // Qi and Qi2 that will store indexes
    // of array elements
    // The queues will store indexes
    // of useful elements in every
    // window and Qi will
    // maintain decreasing order of
    // values from front to rear in Qi, i.e.,
    // arr[Qi.front[]] to arr[Qi.rear()]
    // are sorted in decreasing order
    // Similarly Qi2 will store in increasing order
    // from front to rear of Qi2
    deque<int> Qi(k);// decreasing order deque for maximum element
    deque<int> Qi2(k);//increasing order deque for minimum element

    /* Processing first k (or first sliding window)
     elements of the given array */
    int i;
    for (i = 0; i < k; ++i)
    {

        // For every element in Qi, the previous
        // smaller elements are useless so
        // remove them from Qi
        //Similarly For every element in Qi2, the previous
        // larger elements are useless so
        // remove them from Qi
        while ((!Qi.empty()) && arr[i] >=arr[Qi.back()])
             // Remove from rear of Qi to maintain descending order
            Qi.pop_back();
        while ((!Qi2.empty()) && arr[i] <=arr[Qi2.back()])
             // Remove from rear of Qi2 to maintain ascending order
            Qi2.pop_back();

        // Add new element at rear of queues Qi and Qi2
        Qi.push_back(i);
        Qi2.push_back(i);
    }

    // Process rest of the elements,
    // i.e., from arr[k] to arr[n-1]
    for (; i < n; ++i)
    {
        // The elements at the front of
        // the queues are the maximum and minimum elements of
        // previous window, so we  print the difference
        cout << arr[Qi.front()]-arr[Qi2.front()] << " ";

        // Remove the elements from both queues which
        // are out of this window
        while ((!Qi.empty()) && Qi.front() <=i - k)
            // Remove from front of queue Qi
            Qi.pop_front();
        while ((!Qi2.empty()) && Qi2.front() <=i - k)

            // Remove from front of queue Qi2
            Qi2.pop_front();

        // Remove all elements from both queues
        // smaller than the currently
        // being added element (remove
        // useless elements)
        while ((!Qi.empty()) && arr[i] >=arr[Qi.back()])
            Qi.pop_back();
        while ((!Qi2.empty()) && arr[i] <=arr[Qi2.back()])
            Qi2.pop_back();

        // Add current element at the rear of Qi and Qi2
        Qi.push_back(i);
        Qi2.push_back(i);
    }

    // Print the difference (maximum-minimum)
    // of last window
    cout << arr[Qi.front()]-arr[Qi2.front()];
}

int main()
{
    int n,k;
    cin>>n>>k;
    int arr[n];//declaring an array of size n
    for(int i=0;i<n;i++)cin>>arr[i];
    //calling the function to print difference if sliding windows
    print_difference(arr, n, k);
    return 0;
}
