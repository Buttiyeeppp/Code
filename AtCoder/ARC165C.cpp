#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PLL=pair<ll,ll>;
const int N=2e5+10;
bool mem1;
int n,m,mn[2][N],col[N],pd;
struct Edge {
    int x,y,c;
}eg[N];
vector<PLL> g[N];
void dfs(int x,ll v) {
    for(auto y:g[x]) if(y.second<v) {
        if(col[y.first]==col[x]) pd=1;
        if(!col[y.first]) {
            col[y.first]=((col[x]==1)? 2:1);
            dfs(y.first,v);
        }
    }
}
bool check(ll v) {
    for(int i=1;i<=n;i++) col[i]=0;
    pd=0;
    for(int i=1;i<=n;i++) if(!col[i]) col[i]=1, dfs(i,v);
    return (pd==0);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    memset(mn,0x3f,sizeof(mn));
    for(int i=1,x,y,c;i<=m;i++) {
        cin>>x>>y>>c;
        eg[i]={x,y,c};
        g[x].emplace_back(y,c), g[y].emplace_back(x,c);
        if(c<mn[0][x]) mn[1][x]=mn[0][x], mn[0][x]=c;
        else if(c<mn[1][x]) mn[1][x]=c;
        swap(x,y);
        if(c<mn[0][x]) mn[1][x]=mn[0][x], mn[0][x]=c;
        else if(c<mn[1][x]) mn[1][x]=c;
    }
    ll l=0, r=1e17;
    for(int i=1;i<=n;i++) r=min(r,(ll)mn[0][i]+mn[1][i]+1);
    while(l+1<r) {
        ll mid=(l+r)>>1;
        if(check(mid)) l=mid;
        else r=mid;
    }
    cout<<l<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}