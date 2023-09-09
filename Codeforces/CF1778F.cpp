#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const int INF=0x3f3f3f3f;
bool mem1;
int n,k,a[N],f[N][110],g[110],p[N];
vector<int> v,eg[N];
void dfs(int x,int from) {
    for(int i=0;i<(int)v.size();i++) f[x][i]=((a[x]%v[i]!=0)? INF:0);
    for(auto y:eg[x]) if(y!=from) {
        dfs(y,x);
        for(int i=0;i<(int)v.size();i++) f[x][i]=min(INF,f[x][i]+f[y][i]);
    }
    if(x==1) return;
    for(int i=0;i<(int)v.size();i++) g[i]=f[x][i];
    for(int i=0;i<(int)v.size();i++)
        for(int j=0;v[i]*v[j]<=a[1]&&j<=i;j++) if((~p[v[i]*v[j]])&&v[i]%v[j]==0) g[p[v[i]*v[j]]]=min(g[p[v[i]*v[j]]],f[x][i]+1);
    for(int i=0;i<(int)v.size();i++) f[x][i]=g[i];
}
void solve() {
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i], eg[i].clear();
    for(int i=1,x,y;i<n;i++) {
        cin>>x>>y, eg[x].push_back(y), eg[y].push_back(x);
    }
    v.clear();
    for(int i=1;i<=a[1];i++) {
        p[i]=-1;
        if(a[1]%i==0) v.push_back(i), p[i]=v.size()-1;
    }
    dfs(1,0);
    int ans=a[1];
    for(int i=0;i<(int)v.size();i++) if(f[1][i]<k) ans=a[1]*v[i];
    cout<<ans<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
 
    int T; cin>>T;
    while(T--) solve();
 
    #ifdef xxzx
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    cerr<<"Time "<<clo<<"MS"<<endl;
    #endif
    return 0;
}