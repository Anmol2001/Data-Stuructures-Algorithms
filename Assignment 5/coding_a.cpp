#include <bits/stdc++.h>
using namespace std;
int maze[12][12];
// initializing maze with zeros and one extra row column at each side for accessibility
// because zeros are robots and are of no use so initially  before input all are robots

// i have assumed to start from t=1 for ease of implementation
int main(){
    int n,m;
    cin>>m>>n;
    int hc=0;// for counting number of humans
    int input;
    // queue for storing active zombies which are recently transformed from humans
    // because zombies which have used their power are of no use
    // queue is storing address and active time of zombies
    queue<pair<pair<int,int>,int>> qu;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
                cin>>input;
            maze[i][j]=input;
            if (input==1)hc+=1;
            else if (input==2) qu.push(make_pair(make_pair(i,j),2));// pushing initial zombies into queue and their active time is 2
        }
    }
    int t=1; // assuming to start from t=1 for ease of implementation  later on we will shift
    int mod_t=1;// modifications done at time t or humans destroyed at time t
    // initialized modifications with 1 so that while loop can start

    // at every t the newly(at t-1) made zombies are spreading the virus 1 unit in each direction
    while(hc!=0 && mod_t!=0){t+=1;mod_t=0;
     while (qu.front().second==t){
             int i=qu.front().first.first;
             int j=qu.front().first.second;
             qu.pop();// as zombie has used its power so removing it from queue

            if (maze[i+1][j]==1){maze[i+1][j]=t+1;hc-=1;mod_t+=1;qu.push(make_pair(make_pair(i+1,j),t+1));}
            if (maze[i-1][j]==1){maze[i-1][j]=t+1;hc-=1;mod_t+=1;qu.push(make_pair(make_pair(i-1,j),t+1));}
            if (maze[i][j+1]==1){maze[i][j+1]=t+1;hc-=1;mod_t+=1;qu.push(make_pair(make_pair(i,j+1),t+1));}
            if (maze[i][j-1]==1){maze[i][j-1]=t+1;hc-=1;mod_t+=1;qu.push(make_pair(make_pair(i,j-1),t+1));}  }

        }
    // if new modifications are zero or all humans are destroyed the loop will terminate

    if (hc==0)cout<<t-1;// doing time shift of one unit as discussed above
    else cout<<-1;

return 0;}
