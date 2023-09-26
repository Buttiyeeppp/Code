#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,fa[N];
vector<int> g[N];
ll ans[N],a[N],sz[N];
void dfs(int x,int from) {
    sz[x]=1, fa[x]=from;
    for(auto y:g[x]) if(y!=from) {
        dfs(y,x);
        sz[x]+=sz[y];
    }
}
void dfs1(int x,int from) {
    for(auto y:g[x]) if(y!=from) {
        ans[y]=ans[x]+(a[y]^a[x])*(sz[x]-sz[y]-sz[y]);
        int mem;
        sz[x]=sz[x]-sz[y], mem=sz[y], sz[y]=n;
        dfs1(y,x);
        sz[x]=n, sz[y]=mem;
    }
}
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) g[i].clear();
    for(int i=1,x,y;i<n;i++) {
        cin>>x>>y;
        g[x].push_back(y), g[y].push_back(x);
    }
    dfs(1,0);
    memset(ans,0,sizeof(ans));
    for(int i=2;i<=n;i++) ans[1]+=(a[i]^a[fa[i]])*sz[i];
    dfs1(1,0);
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    cout<<endl;
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