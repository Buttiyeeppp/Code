#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PLI=pair<ll,int>;
const int N=5e5+10;
bool mem1;
int n,m,k,c[N],vis[N];
ll dis[N];
vector<int> g[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1,x,y;i<=m;i++) {
        cin>>x>>y;
        g[x].push_back(y), g[y].push_back(x);
    }
    memset(dis,0x3f,sizeof(dis)); dis[1]=0;
    priority_queue<PLI,vector<PLI>,greater<PLI>> q; q.emplace(0,1);
    while(q.size()) {
        int x=q.top().second; q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(auto y:g[x]) if(!vis[y]) {
            int v=INT_MAX;
            v=min(((c[y]-1-c[x])%k+k)%k,(c[y]+1-c[x]+k)%k);
            if(dis[y]>v+dis[x]) dis[y]=v+dis[x], q.emplace(dis[y],y);
        }
    }
    ll mx=0;
    for(int i=1;i<=n;i++) mx=max(mx,dis[i]);
    for(int i=1;i<=n;i++) cout<<(c[i]+mx-dis[i]+k)%k<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}