#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,vis[N],ins[N],ind[N];
vector<int> eg[N],g[N];
void dfs(int x) {
    vis[x]=ins[x]=1;
    for(auto y:eg[x]) {
        if(!ins[y]) ind[y]++, g[x].push_back(y);
        if(!vis[y]) dfs(y);
    }
    ins[x]=0;
}
bool ask(int x,int y) {
    cout<<"? "<<x<<" "<<y<<endl;
    int res;
    cin>>res;
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++) {
        cin>>x>>y;
        eg[x].push_back(y);
    }
    for(int i=1;i<=n;i++) if(!vis[i]) dfs(i);
    queue<int> q;
    for(int i=1;i<=n;i++) if(!ind[i]) q.push(i);
    while(q.size()>1) {
        int x=q.front(); q.pop();
        int y=q.front(); q.pop();
        if(!ask(x,y)) swap(x,y);
        for(auto to:g[y]) {
            ind[to]--;
            if(!ind[to]) q.push(to);
        }
        q.push(x);
    }
    cout<<"! "<<q.front()<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}