#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int M=130;
const ll Mod=998244353;
bool mem1;
ll n,m,f[65][M],g[65][M];
int dep(ll x) { return ((x<<1)<=n)? dep(x<<1)+1:0; }
int dep2(ll x) { return ((x<<1|1)<=n)? dep2(x<<1|1)+1:0; }
bool full(ll x) { return (dep(x)==dep2(x)); }
ll f1[M],g1[M],dpf[M],dpg[M];
// f为所有方案,g为钦定选根的方案
ll Add(ll x,ll y) { return (x+y>=Mod)? x+y-Mod:x+y; }
void dfs(ll x) {
    for(int i=1;i<M;i++) dpf[i]=dpg[i]=0;
    if((x<<1|1)>n) {
        if((x<<1)<=n) {
            dfs(x<<1);
            for(int j=1;j<M;j++) dpg[j]=g1[j-1], dpf[j]=Add(f1[j],dpg[j]);
        }
        dpf[1]=Add(dpf[1],1), dpg[1]=Add(dpg[1],1);
        for(int j=1;j<M;j++) f1[j]=dpf[j], g1[j]=dpg[j];
        return;
    }
    int d;
    if(!full(x<<1)) dfs(x<<1), d=dep(x<<1|1);
    else dfs(x<<1|1), d=dep(x<<1);
    for(int j=1;j<M;j++) {
        dpg[j]=dpf[j]=Add(g1[j-1],g[d][j-1]);
        for(int k=1;k+1<j;k++) dpf[j]=Add(dpf[j],g1[k]*g[d][j-k-1]%Mod);
        dpf[j]=Add(dpf[j],Add(f1[j],f[d][j]));
    }
    dpf[1]=Add(dpf[1],1), dpg[1]=Add(dpg[1],1);
    for(int j=1;j<M;j++) f1[j]=dpf[j], g1[j]=dpg[j];
}
ll POW(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
ll Pow[100010][M];
void solve() {
    cin>>n>>m;
    dfs(1);
    ll ans=0,p;
    for(int i=min((ll)M-1,n);i>=0;i--) {
        if(i==min((ll)M-1,n)) p=POW(m,n-i);
        else p=p*m%Mod;
        for(int v=1;v<=m;v++) ans=(ans+f1[i]*(Pow[v][i]-Pow[v-1][i]+Mod)%Mod*p%Mod*v)%Mod;
    }
    cout<<ans<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    f[0][1]=g[0][1]=1;
    for(int i=1;i<65;i++) {
        for(int j=1;j<=i*2+1;j++) {
            g[i][j]=f[i][j]=2*g[i-1][j-1]%Mod;
            for(int k=1;k+1<j;k++) f[i][j]=(f[i][j]+g[i-1][k]*g[i-1][j-k-1])%Mod;
            f[i][j]=(f[i][j]+2*f[i-1][j])%Mod;
        }
        f[i][1]=(f[i][1]+1)%Mod, g[i][1]=(g[i][1]+1)%Mod;
    }
    for(int i=1;i<100010;i++) {
        Pow[i][0]=1;
        for(int j=1;j<M;j++) Pow[i][j]=Pow[i][j-1]*i%Mod;
    }
    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}