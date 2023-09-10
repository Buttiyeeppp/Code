#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
ll n,m,l[N];
bool check(ll x) {
    ll res=l[1], h=1;
    for(int i=2;i<=n;i++) {
        if(res+1+l[i]>x) res=l[i], h++;
        else res+=1+l[i];
    }
    return (h<=m);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    ll mx=0;
    for(int i=1;i<=n;i++) cin>>l[i], mx=max(mx,l[i]);
    ll l=mx-1, r=1e17;
    while(l+1<r) {
        ll mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid;
    }
    cout<<r<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}