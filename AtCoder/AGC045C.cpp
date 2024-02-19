#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e9+7;
const int N=5e3+10;
bool mem1;
int n,a,b;
ll f[N],g[N][2];
void Add(ll &x,ll y) { x=(x+y>=Mod)? x+y-Mod:x+y; }
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>a>>b;
    if(a>b) swap(a,b);
    f[1]=1;
    for(int i=2;i<b;i++) {
        f[i]=f[i-1];
        for(int j=a;j<=i-1;j++) Add(f[i],f[i-j-1]);
    }
    ll ans=1;
    g[0][0]=g[0][1]=1;
    for(int i=a;i<=n;i++) {
        for(int j=1;j+i<b;j++) Add(g[i+j][1],f[j]);
    }
    for(int i=1;i<=n;i++) {
        ans=2*ans%Mod;
        for(int j=1;j<=min(b-1,i);j++) {
            Add(g[i][1],g[i-j][0]*f[j]%Mod);
            if(j+(n-i)<b&&n-i>=a) Add(g[n][0],g[i-j][0]*f[j]%Mod);
        }
        for(int j=1;j<=min(a-1,i);j++) Add(g[i][0],g[i-j][1]);
    }
    Add(g[n][0],g[n][1]);
    cout<<(ans-g[n][0]+Mod)%Mod<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}