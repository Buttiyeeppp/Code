#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
using PLL=pair<ll,ll>;
const int N=3e2+10;
const int V=1e6;
bool mem1;
ll n,m,b[N][N],a[N][N],vis[N<<1],dis[N<<1],len[N<<1];
vector<PLL> g[N<<1];
void solve() {
    cin>>n>>m;
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++) cin>>b[i][j];
    for(int i=1;i<=n;i++) a[i][1]=0;
    for(int i=1;i<=m;i++) a[1][i]=0;
    for(int i=2;i<=n;i++)
        for(int j=2;j<=m;j++) {
            a[i][j]=b[i-1][j-1]-a[i-1][j-1]-a[i-1][j]-a[i][j-1];
        }
    for(int i=1;i<=n+m;i++) g[i].clear();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            int x=i, y=j+n;
            if((i&1)!=(j&1)) swap(x,y);
            g[x].emplace_back(y,a[i][j]);
            g[y].emplace_back(x,V-a[i][j]);
        }
    queue<int> q;
    for(int i=1;i<=n+m;i++) dis[i]=len[i]=0, vis[i]=1, q.push(i);
    while(q.size()) {
        int x=q.front(); q.pop();
        vis[x]=0;
        for(auto to:g[x]) {
            int y=to.first;
            if(dis[y]>dis[x]+to.second) {
                dis[y]=dis[x]+to.second, len[y]=len[x]+1;
                if(len[y]>=n+m) return cout<<"NO"<<endl, void();
                if(!vis[y]) vis[y]=1, q.push(y);
            }
        }
    }
    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            int op=((i&1)==(j&1))? 1:-1;
            a[i][j]+=op*(dis[i]-dis[j+n]);
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
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