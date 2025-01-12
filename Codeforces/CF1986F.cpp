#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool memory1;
int n,m,head[N],tot=1;
vector<int> g[N];
struct Edge {
    int x,to,nxt;
}eg[N<<1];
void Addedge(int x,int y) {
    eg[++tot]={x,y,head[x]};
    head[x]=tot;
}
int dfn[N],low[N],tim,bri[N<<1];
void tarjan(int x,int from) {
    dfn[x]=low[x]=++tim;
    for(int i=head[x];i;i=eg[i].nxt) if((i^1)!=from) {
        int y=eg[i].to;
        if(!dfn[y]) tarjan(y,i),low[x]=min(low[x],low[y]);
        else low[x]=min(low[x],dfn[y]);
        if(low[y]>dfn[x]) bri[i]=bri[i^1]=1;
    }
}
int col[N],cnt;
void dfs(int x) {
    col[x]=cnt;
    for(int i=head[x];i;i=eg[i].nxt) if(!bri[i]) {
        int y=eg[i].to;
        if(!col[y]) dfs(y);
    }
}
int sz[N];
ll z,mx;
void dfs1(int x,int from) {
    // cerr<<"dfs1"<<endl;
    for(auto y:g[x]) if(y!=from) {
        dfs1(y,x);
        sz[x]+=sz[y];
        mx=max(mx,1ll*sz[y]*(n-sz[y]));
    }
}
void solve() {
    cin>>n>>m;

    tot=1,cnt=tim=mx=0,z=1ll*n*(n-1)/2;
    for(int i=1;i<=n;i++) head[i]=dfn[i]=low[i]=col[i]=sz[i]=0,g[i].clear();
    for(int i=0;i<=(m<<1);i++) bri[i]=0;

    for(int i=1,x,y;i<=m;i++) {
        cin>>x>>y;
        Addedge(x,y),Addedge(y,x);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,0);
    for(int i=1;i<=n;i++) if(!col[i]) cnt++,dfs(i);
    for(int i=1;i<=n;i++) sz[col[i]]++;
    // cerr<<"Col ";
    // for(int i=1;i<=n;i++) cerr<<col[i]<<" ";
    // cerr<<endl;
    for(int i=2;i<=tot;i++) if(col[eg[i].x]!=col[eg[i].to]) {
        g[col[eg[i].x]].push_back(col[eg[i].to]);
    }
    dfs1(1,0);
    cout<<z-mx<<endl;
}
bool memory2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&memory1-&memory2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}