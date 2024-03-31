#include <bits/stdc++.h>
#include <cmath>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e6+10;
const ll Mod=998244353;
bool mem1;
ll f[N],g[N];
int n,m,tr[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
void FFT(ll *f,int op) {
    for(int i=0;i<n;i++) 
        if(i<tr[i]) swap(f[i],f[tr[i]]);
    for(int l=2,nl=1;l<=n;l<<=1,nl<<=1) {
        ll t=Pow(3,(Mod-1)/l);
        if(op==-1) t=Pow(t,l-1);
        for(int j=0;j<n;j+=l) {
            ll d=1;
            for(int k=j;k<j+nl;k++) {
                ll a=f[k], b=d*f[k+nl]%Mod;
                f[k]=(a+b)%Mod, f[k+nl]=(a-b+Mod)%Mod;
                d=d*t%Mod;
            }
        }
    }
    if(op==-1) {
        ll inv=Pow(n,Mod-2);
        for(int i=0;i<n;i++) f[i]=f[i]*inv%Mod;
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=0;i<=n;i++) cin>>f[i];
    for(int i=0;i<=m;i++) cin>>g[i];
    m+=n, n=1;
    while(n<=m) n<<=1;
    for(int i=0;i<n;i++) tr[i]=(tr[i>>1]>>1)|((i&1)? (n>>1):0);
    FFT(f,1), FFT(g,1);
    for(int i=0;i<n;i++) f[i]=f[i]*g[i]%Mod;
    FFT(f,-1);
    for(int i=0;i<=m;i++) cout<<f[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}