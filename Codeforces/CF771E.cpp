#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,nt[4][N],f[N],g[N],h[N];
vector<PII> G[N],H[N];
map<ll,int> mp[4];
ll a[4][N];
void Max(int &x,int y) { if(y>x) x=y; }
void Min(int &x,int y) { if(y<x) x=y; }
void add(vector<PII> *vc,int i,int j,int v) {
    if(i>n||j>n) return;
    vc[i].emplace_back(j,v);
    Max(f[j],v);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1,x;i<=n;i++) cin>>x, a[1][i]=a[1][i-1]+x;
    for(int i=1,x;i<=n;i++) cin>>x, a[2][i]=a[2][i-1]+x;
    for(int i=1;i<=n;i++) a[3][i]=a[1][i]+a[2][i];
    for(int i=1;i<=3;i++) memset(nt[i],0x3f,sizeof(nt[i]));
    for(int i=n;i>=0;i--) {
        for(int j=1;j<=3;j++) {
            if(mp[j][a[j][i]]) nt[j][i]=mp[j][a[j][i]];
            mp[j][a[j][i]]=i;
        }
    }
    for(int i=n-1;i>=0;i--)
        for(int j=1;j<=3;j++) Min(nt[j][i],nt[j][i+1]);
    memset(g,0x3f,sizeof(g)), memset(h,0x3f,sizeof(h));
    for(int i=0;i<=n;i++) {
        add(G,i,nt[1][i],f[i]+1), add(H,i,nt[2][i],f[i]+1);
        if(nt[3][i]<=n) Max(f[nt[3][i]],f[i]+1);
        Max(f[i+1],f[i]);
        for(auto j:G[i]) {
            if(j.second>f[i]) Min(g[i],j.first);
        }
        for(auto j:H[i]) {
            if(j.second>f[i]) Min(h[i],j.first);
        }
        if(g[i]<=n) {
            if(nt[2][i]<=g[i]) add(G,nt[2][i],g[i],f[i]+2);
            else add(H,g[i],nt[2][i],f[i]+2);
        }
        if(h[i]<=n) {
            if(nt[1][i]<=h[i]) add(H,nt[1][i],h[i],f[i]+2);
            else add(G,h[i],nt[1][i],f[i]+2);
        }
    }
    cout<<f[n]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}