#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=998244353;
const int N=1e6+10;
bool mem1;
ll n,m,fac[N],inv[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
void init() {
    fac[0]=inv[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Pow(fac[N-1],Mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll C(ll x,ll y) {
    if(x<0||y<0||x<y) return 0;
    return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    cin>>n>>m;
    if(n<m) swap(n,m);
    ll res=0;
    for(int i=1;i<=m;i++) res=(res+C(n+m-2*i,n-i)*C(2*i,i)%Mod)%Mod;
    res=res*Pow(2*C(n+m,n)%Mod,Mod-2)%Mod;
    cout<<(res+n)%Mod<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}