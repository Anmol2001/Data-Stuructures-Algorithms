#include<bits/stdc++.h>
using namespace std;
//Kruskal implementation to obtain MST
//structure for graph
int S,D;// source and destination
struct Graph{
   int V, E;
   vector< pair<int,pair<int,int> >> edges;// edges list for construction MST from original graph
   vector <vector<pair<int,int>>> adj_list;// adjacency list to use in MST (vertex,cost)
   Graph(int V, int E){
      this->V = V;
      this->E = E;
      this->adj_list.resize(V+1);
   }
   void addEdge(int u, int v, int w){
      edges.push_back({w, {u, v}});
   }
   void kruskalMST(Graph*);// pointer of MST passed into original graph function
   void DFS(int,int,int);
};
// disjoint set implementation
struct DisjointSets{
   int *parent, *rnk;
   int n;
   // initially assigning each one as its parent as all are different sets
   DisjointSets(int n){
      this->n = n;
      parent = new int[n+1];
      rnk = new int[n+1];
   for (int i = 0; i <= n; i++){
      rnk[i] = 0;
      parent[i] = i;
   }
}
// finding parent in log(n) time
int find(int u){
   if (u != parent[u])
   parent[u] = find(parent[u]);
   return parent[u];
}
// merging small set with bigger set so that time complexity of find is always (O)log(n)
void merge(int x, int y){
   x = find(x), y = find(y);
   if (rnk[x] > rnk[y])
      parent[y] = x;
   else
      parent[x] = y;
   if (rnk[x] == rnk[y])
      rnk[y]++;
   }
};
void Graph::kruskalMST( Graph* po){
   sort(edges.begin(), edges.end());
   DisjointSets ds(V);
   vector< pair<int,pair<int,int>> >::iterator it;
   // iterating on sorted edges
   for (it=edges.begin(); it!=edges.end(); it++){
      int u = it->second.first;
      int v = it->second.second;
      int set_u = ds.find(u);
      int set_v = ds.find(v);
      if (set_u != set_v){
         //storing MST in adjacency list
         po->adj_list[u].push_back(make_pair(v,it->first));
         po->adj_list[v].push_back(make_pair(u,it->first));
         ds.merge(set_u, set_v);
      }
   }
   return ;
}
stack<pair<int,int>> path; // weight,vertex for storing path of DFS traversal
bool vis[5005]={0};// visited array for DFS
bool f=0;// flag variable for indicating destination found
void calculate_ans(int max_allowed){
    stack<int> ans;// stack for storing path from reverse order and outputting in correct order
    int max_cost_road=0;
    while(path.empty()!=true){
        max_cost_road=max(path.top().first,max_cost_road);
        ans.push(path.top().second);
        path.pop();
    }
    ans.push(S);
    if (max_cost_road<=max_allowed)
    {cout<<"POSSIBLE\n";while(ans.empty()!=true){cout<<ans.top()<<" ";ans.pop();}}
    else cout<<"NOT POSSIBLE\n";
}
// using DFS to find unique path in MST from source to destination
void Graph::DFS(int source,int dest,int max_cost){
    if (f==1)return;
    if (vis[source]==1){path.pop();return;}
    vis[source]=1;
    vector< pair<int,int> >::iterator it;
    for (it=this->adj_list[source].begin(); it!=this->adj_list[source].end(); it++){
            if(f==1)return;
            int ns=it->first;// new successor
            if (ns==dest){f=1;path.push(make_pair(it->second,ns));calculate_ans(max_cost);return;}
            path.push(make_pair(it->second,ns));
            DFS(ns,dest,max_cost);}
       if(f!=1)path.pop();
       return;
}

int main(){
   int V , E ;
   cin>>V>>E;
   Graph g(V, E);// creating an object graph for original graph
   Graph mst(V,E);// creating an object graph for MST
   int a,b,c;
   for(int i=0;i<E;i++){cin>>a>>b>>c;g.addEdge(a,b,c);}
    Graph* pt= &mst;// pointer to MST
   g.kruskalMST(pt);// function for constructing and storing MST in adjacency list through pointer of MST graph object
   int cost;
   cin>>S>>D>>cost;
   mst.DFS(S,D,cost);// doing DFS on MST from source to destination and to trace path
   return 0;
}
