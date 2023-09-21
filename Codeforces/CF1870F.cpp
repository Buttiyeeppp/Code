#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
ll n,k;
ll dfs(ll l,ll r) {
    ll res=0,ml=l,mr=r;
    while(l) {
        res+=r-l+1;
        l/=k, r/=k;
    }
    l=ml, r=mr;
    while(l<=n/k) {
        l*=k;
        if(r<=n/k) r*=k;
        else r=n+1;
        // r=min(r*k,n+1);
        res+=r-l;
    }
    // cerr<<ml<<" "<<mr<<" "<<res<<endl;
    return res;
}
ll find(ll op,ll i,ll j) {
    ll l=i-1,r=j+1;
    while(l+1<r) {
        ll mid=(l+r)>>1;
        if(dfs(i,mid)<=mid-op) l=mid;
        else r=mid;
    }
    return l;
}
void solve() {
    cin>>n>>k;
    ll ans=0;
    ll i=1, j=min(k-1,n), l=k;
    while(1) {
        // cerr<<i<<" "<<j<<endl;
        ans+=find(0,i,j)-find(1,i,j);
        if(i>n/k) break;
        i*=k;
        if(l<=(n+1)/k) l*=k, j=l-1;
        else j=n;
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