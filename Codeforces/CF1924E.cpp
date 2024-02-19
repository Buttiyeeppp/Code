#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e9+7;
bool mem1;
ll n,m,k;
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
void Add(ll &x,ll y) {
    return x=(x+y>=Mod)? x+y-Mod:x+y, void();
}
void solve() {
    cin>>n>>m>>k;
    if(n*m<k) return cout<<0<<endl, void();
    ll ans=1;
    for(int i=1;i<=n-1;i++) if((k+i-1)/i<=m)
        Add(ans,Pow(i+(k+i-1)/i-1,Mod-2));
    for(int i=1;i<=m-1;i++) if((k+i-1)/i<=n)
        Add(ans,Pow(i+(k+i-1)/i-1,Mod-2));
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