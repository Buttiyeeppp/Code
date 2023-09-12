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
int n,fa[N][20],dep[N],v[N];
pair<ll,ll> vf[N];
struct edge {
    ll to,p1,p2;
};
vector<edge> eg[N];
void dfs(int x,int from) {
    for(auto y:eg[x]) if(y.to!=from) {
        vf[y.to]={y.p1,y.p2}, fa[y.to][0]=x, dep[y.to]=dep[x]+1;
        dfs(y.to,x);
    }
}
int lca(int x,int y) {
    if(dep[x]<dep[y]) swap(x,y);
    for(int h=dep[x]-dep[y],i=0;h;h>>=1,i++) {
        if(h&1) x=fa[x][i];
    }
    if(x==y) return x;
    for(int i=19;i>=0;i--) 
        if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
    return fa[x][0];
}
ll ans;
void dfs1(int x,int from) {
    for(auto y:eg[x]) if(y.to!=from) {
        dfs1(y.to,x);
        v[x]+=v[y.to];
    }
    if(from) ans+=min(vf[x].first*v[x],vf[x].second);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1,x,y,a,b;i<n;i++) {
        cin>>x>>y>>a>>b;
        eg[x].push_back({y,a,b}), eg[y].push_back({x,a,b});
    }
    dfs(1,0);
    for(int j=1;j<20;j++)
        for(int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
    for(int i=1;i<n;i++) v[i]++, v[i+1]++, v[lca(i,i+1)]-=2;
    dfs1(1,0);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}