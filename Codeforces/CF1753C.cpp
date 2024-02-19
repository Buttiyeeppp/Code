#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const ll Mod=998244353;
bool mem1;
int n,a[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
void solve() {
    cin>>n;
    int ze=0, k=0;
    for(int i=1;i<=n;i++) cin>>a[i], ze+=(a[i]==0);
    for(int i=1;i<=ze;i++) k+=a[i];
    ll ans=0, c=(1ll*n*(n-1)/2)%Mod;
    for(int i=1;i<=k;i++) ans=(ans+c*Pow(1ll*i*i%Mod,Mod-2)%Mod)%Mod;
    cout<<ans<<endl;
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