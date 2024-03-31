#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
const ll Mod=1e9+7;
bool mem1;
int n,m,k,u[N],r[N];
ll c[N][N],h[N],pre[N],suf[N],zpre[N],zsuf[N];
void init() {
    for(int i=0;i<N;i++) c[i][0]=1;
    for(int i=1;i<N;i++)
        for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%Mod;
}
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
ll x[N],y[N];
ll Lag(ll n,ll k) {
    for(int i=1;i<=k+2;i++) y[i]=(y[i-1]+Pow(i,k))%Mod, x[i]=i;
    pre[0]=suf[k+3]=1;
    for(int i=1;i<=k+2;i++) pre[i]=pre[i-1]*(n-x[i]+Mod)%Mod;
    for(int i=k+2;i>=1;i--) suf[i]=suf[i+1]*(n-x[i]+Mod)%Mod;
    zpre[0]=zsuf[0]=1;
    for(int i=1;i<=k+2;i++) zpre[i]=zpre[i-1]*i%Mod, zsuf[i]=zsuf[i-1]*(-i+Mod)%Mod;
    ll v=0;
    for(int i=1;i<=k+2;i++) {
        v=(v+
            pre[i-1]*suf[i+1]%Mod*Pow(zpre[i-1]*zsuf[k+2-i]%Mod,Mod-2)%Mod*y[i]%Mod
            )%Mod;
    }
    return v;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++) cin>>u[i];
    for(int i=1;i<=m;i++) cin>>r[i];
    for(int i=1;i<=m;i++) {
        ll v=1;
        for(int k=0;k<=r[i]-1;k++) {
            ll res=c[r[i]-1][k]*v%Mod;
            if((r[i]-1-k)&1) res=(Mod-res)%Mod;
            res=res*Lag(u[i],n-k-1)%Mod;
            h[i]=(h[i]+res)%Mod;
            v=v*u[i]%Mod;
        }
    }
    int lim=INT_MAX;
    for(int i=1;i<=m;i++) lim=min(lim,n-r[i]);
    ll ans=0;
    for(int p=k;p<=lim;p++) {
        ll res=c[n-1][p]*c[p][k]%Mod;
        if((p-k)&1) res=(Mod-res)%Mod;
        for(int i=1;i<=m;i++) res=res*c[n-p-1][r[i]-1]%Mod*h[i]%Mod;
        ans=(ans+res)%Mod;
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}