#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
const ll Mod=1e9+7;
bool mem1;
ll n,k,x[N],y[N],pre[N],suf[N];
ll zpre[N],zsuf[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k;
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
    cout<<v<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}