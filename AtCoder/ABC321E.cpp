#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
ll n,x,k;
ll calc(ll x,ll k) {
    ll l=1;
    while(k) {
        if(x>n/2) return 0;
        x*=2;
        if(l>n/2) l=n;
        else l<<=1;
        k--;
    }
    return min(n-x+1,l);
}
void solve() {
    cin>>n>>x>>k;
    ll ans=calc(x,k);
    while(x>1&&k) {
        int v=x&1;
        x>>=1, k--;
        if(!k) ans++;
        else ans+=calc((x<<1)|(v^1),k-1);
    }
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