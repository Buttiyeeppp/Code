#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,k,dis[2][N],ind[N],vis[N];
vector<int> zg[N];
vector<PII> g[N],ng[N];
void dij(int st,int op,vector<PII> g[]) {
    memset(dis[op],0x3f,sizeof(dis[op]));
    memset(vis,0,sizeof(vis));
    priority_queue<PII,vector<PII>,greater<PII>> q;
    dis[op][st]=0, q.emplace(0,st);
    while(q.size()) {
        int x=q.top().second; q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(auto to:g[x]) {
            int y=to.first;
            if(dis[op][y]>dis[op][x]+to.second)
                dis[op][y]=dis[op][x]+to.second, q.emplace(dis[op][y],y);
        }
    }
}
int tp[N];
ll Mod,f[N][55];
void Add(ll &x,ll y) { return x=(x+y>=Mod)? x+y-Mod:x+y, void(); }
void solve() {
    cin>>n>>m>>k>>Mod;
    for(int i=1;i<=n;i++) zg[i].clear(), g[i].clear(), ng[i].clear(), ind[i]=0;
    for(int i=1,x,y,z;i<=m;i++) {
        cin>>x>>y>>z;
        g[x].emplace_back(y,z), ng[y].emplace_back(x,z);
    }
    dij(1,0,g), dij(n,1,ng);
    for(int i=1;i<=n;i++) {
        if(dis[0][i]+dis[1][i]>dis[0][n]+k) continue;
        for(auto to:g[i]) if(!to.second) {
            int j=to.first;
            if(dis[0][j]+dis[1][j]>dis[0][n]+k) continue;
            zg[i].push_back(j), ind[j]++;
        }
    }
    queue<int> q;
    for(int i=1;i<=n;i++) 
        if(!ind[i]) q.push(i);
    int tim=0;
    memset(tp,0,sizeof(tp));
    while(q.size()) {
        int x=q.front(); q.pop();
        tp[x]=++tim;
        for(auto y:zg[x]) {
            ind[y]--;
            if(!ind[y]) q.push(y);
        }
    }
    for(int i=1;i<=n;i++) if(ind[i]) {
        return cout<<-1<<endl, void();
    }
    vector<int> nd;
    for(int i=1;i<=n;i++) if(!ind[i]) nd.push_back(i);
    sort(nd.begin(),nd.end(),[](const int &x,const int &y) 
        { return (dis[0][x]==dis[0][y])? (tp[x]<tp[y]):(dis[0][x]<dis[0][y]); });
    ll ans=0;
    memset(f,0,sizeof(f));
    f[1][0]=1;
    for(int c=0;c<=k;c++) {
        for(int i=0;i<(int)nd.size();i++) {
            int x=nd[i];
            for(auto to:g[x]) {
                int y=to.first;
                if(c+dis[0][x]+to.second-dis[0][y]<=k)
                    Add(f[y][c+dis[0][x]+to.second-dis[0][y]],f[x][c]);
            }
        }
        Add(ans,f[n][c]);
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
/*
d[x]  the shortest path
Edge (x,y,w)
f(x,c) --> f(y,c+d[x]+w-d[y])
c<=c+d[x]+w-d[y]

Case : < 
round of 0: cut it/'-1'
'-1' --> index x(in round),dis(1-->x)+dis(x-->n)<=d+k
*/
