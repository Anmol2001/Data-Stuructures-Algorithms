#include <bits/stdc++.h>
using namespace std;
#define MAX 400005
// max size of segment tree is 4*N as N is 100000

// initializing segment tree
int seg_T[MAX] = { 0 };
// lazy array to store pending updates
int lazy_prop[MAX] = { 0 };

// curr is index of current node in segment tree
// seg_start and seg_end are Starting and ending indexes of
// elements for which current nodes stores minimum value
// dec_start and dec_end are starting and ending indexes of decrease query
void decrease_Range(int curr, int seg_start, int seg_end, int dec_start,
					int dec_end, int change)
{
	// doing lazy update
	if (lazy_prop[curr] != 0) {
		// Make pending updates using value stored in lazy
		// nodes
		seg_T[curr] += lazy_prop[curr];

		// Checking if it is not leaf node
		if (seg_start != seg_end) {
			// descending the lazy values to children
			lazy_prop[curr * 2 + 1] += lazy_prop[curr];
			lazy_prop[curr * 2 + 2] += lazy_prop[curr];
		}

		// set the lazy value for updated node to be zero
		lazy_prop[curr] = 0;
	}

	// Out of range
	if (seg_start > seg_end || seg_start > dec_end || seg_end < dec_start)
		return;

	// Current segment is fully in range
	if (seg_start >= dec_start && seg_end <= dec_end) {
		// Add the difference to current node
		seg_T[curr] += change;

		// Same logic for checking leaf node or not
		if (seg_start != seg_end) {
			// postponing the updates
			lazy_prop[curr * 2 + 1] += change;
			lazy_prop[curr * 2 + 2] += change;
		}
		return;
	}

	// If not completely in range, but overlaps
	// recur for children
	int mid = (seg_start + seg_end) / 2;
	decrease_Range(curr * 2 + 1, seg_start, mid, dec_start, dec_end, change);
	decrease_Range(curr * 2 + 2, mid + 1, seg_end, dec_start, dec_end, change);

	// And use the result of children calls
	// to update this node
	seg_T[curr] = min(seg_T[curr * 2 + 1], seg_T[curr * 2 + 2]);
}


// constructing segment tree by recursion
void construct_seg_T(int arr[], int seg_start, int seg_end, int curr)
{
	// out of range
	if (seg_start > seg_end)
		return;

	// storing array elements in the leaves whose segment size is 1
	// therefor seg_start and seg_end are same
	if (seg_start == seg_end) {
		seg_T[curr] = arr[seg_start];
		return;
	}

	// recursion in left and right segments
	int mid = (seg_start + seg_end) / 2;
	construct_seg_T(arr, seg_start, mid, curr * 2 + 1);
	construct_seg_T(arr, mid + 1, seg_end, curr * 2 + 2);

	seg_T[curr] = min(seg_T[curr * 2 + 1], seg_T[curr * 2 + 2]);
}

// this function is for getting leftmost smaller element
// by searching in min segment tree
int leftmost_smaller(int v, int lv, int rv, int x) {
    seg_T[v]+=lazy_prop[v];
    //doing lazy update
    if (lv!=rv){
    // descending lazy updates
    lazy_prop[2*v+1]+=lazy_prop[v];
    lazy_prop[2*v+2]+=lazy_prop[v];
    lazy_prop[v]=0;}
        if(seg_T[v] >= x) return -1;
        while(lv != rv) {
            int mid = lv + (rv-lv)/2;//breaking into segments
            // checking for smaller element on left child first
            // to get leftmost smaller element than v
            if(seg_T[2*v+1]+lazy_prop[2*v+1] < x) {
                v = 2*v+1;//left child
                //doing lazy updates
                seg_T[v]+=lazy_prop[v];
                lazy_prop[2*v+1]+=lazy_prop[v];
                lazy_prop[2*v+2]+=lazy_prop[v];
                lazy_prop[v]=0;
                rv = mid;
            }else {
                v = 2*v+2;//right child
                seg_T[v]+=lazy_prop[v];
                lazy_prop[2*v+1]+=lazy_prop[v];
                lazy_prop[2*v+2]+=lazy_prop[v];
                lazy_prop[v]=0;
                lv = mid+1;
            }
        }
        return lv;// returning the index
}

int main()
{
    int n,Q;
    cin>>n>>Q;
    int arr[n];
    for(int i=0;i<n;i++)cin>>arr[i];

	// Build segment tree from given array
	construct_seg_T(arr, 0,n-1,0);
	int t,l,r,v;
	while(Q--){
	    cin>>t;
        if (t==1){cin>>l>>r>>v;
           decrease_Range(0,0,n-1, l, r, -v);
        }
        else{ cin>>v;
	int index=leftmost_smaller(0,0,n-1,v);
	cout<<index<<"\n";}}
	return 0;
}
