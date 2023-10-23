#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const ll Mod=1e9+7;
bool mem1;
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
ll fac[N],inv[N];
void init() {
    fac[0]=inv[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Pow(fac[N-1],Mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll C(ll x,ll y) {
    if(x<y) return 0;
    return fac[x]*inv[y]%Mod*inv[x-y];
}
void solve() {
    ll n,k;
    cin>>n>>k;
    ll ans=1;
    for(int i=1;i<n;i++) {
        ll v=C(n-(k-1)*(i-1),i);
        v=v*Pow(C(n,i),Mod-2)%Mod;
        ans=(ans+v)%Mod;
    }
    cout<<ans<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}