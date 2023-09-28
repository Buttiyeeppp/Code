#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,m,deg[N],vis[N];
struct Edge { 
    int x,y;
}eg[N];
vector<int> g[N];
void solve() {
    cin>>n>>m;
    for(int i=1;i<=n;i++) deg[i]=0, g[i].clear();
    for(int i=1,x,y;i<=m;i++) {
        cin>>x>>y;
        deg[x]++, deg[y]++;
        eg[i]={x,y};
    }
    for(int i=1;i<=m;i++) {
        int x=eg[i].x, y=eg[i].y;
        if(deg[x]>deg[y]||(deg[x]==deg[y]&&x>y)) swap(x,y);
        g[x].push_back(y);
    }
    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,deg[i]);
    for(int i=1;i<=n;i++) {
        for(auto to:g[i]) vis[to]=1;
        for(auto to:g[i]) {
            for(auto u:g[to]) if(vis[u]) ans=max(ans,3);
        }
        for(auto to:g[i]) vis[to]=0;
    }
    cout<<ans<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}