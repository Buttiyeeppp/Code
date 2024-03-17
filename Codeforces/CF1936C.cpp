#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
using PLI=pair<ll,int>;
const int N=1e6+10;
bool mem1;
int n,m,c[N],p[N],b[N];
vector<int> a[N];
vector<PII> eg[N];
ll dis[N];
int id(int x,int y) { return y*n+x; }
void solve() {
    cin>>n>>m;
    for(int i=0;i<=(m+1)*n;i++) eg[i].clear(), dis[i]=1e17;
    for(int i=1;i<=n;i++) cin>>c[i], p[i]=i;
    for(int i=1;i<=n;i++) {
        a[i].resize(m+1);
        for(int j=1;j<=m;j++) cin>>a[i][j];
    }
    for(int j=1;j<=m;j++) {
        for(int i=1;i<=n;i++) 
            b[i]=a[i][j], eg[id(i,0)].emplace_back(id(i,j),0), eg[id(i,j)].emplace_back(id(i,0),c[i]);
        sort(p+1,p+n+1,[](const int &x,const int &y){ return b[x]<b[y]; });
        for(int i=2;i<=n;i++) {
            eg[id(p[i],j)].emplace_back(id(p[i-1],j),b[p[i]]-b[p[i-1]]);
            eg[id(p[i-1],j)].emplace_back(id(p[i],j),0);
        }
    }
    priority_queue<PLI,vector<PLI>,greater<PLI>> q;
    q.emplace(0,1), dis[1]=0;
    while(q.size()) {
        auto pi=q.top(); q.pop();
        int x=pi.second;
        if(pi.first>dis[x]) continue;
        for(auto y:eg[x]) {
            if(dis[y.first]>dis[x]+y.second) {
                dis[y.first]=dis[x]+y.second;
                q.emplace(dis[y.first],y.first);
            }
        }
    }
    cout<<dis[n]<<endl;
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