#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int n,k,x;
void solve() {
    cin>>n>>k>>x;
    if(n<k||x<k-1) return cout<<-1<<endl, void();
    // if(n>k&&x==k) return cout<<-1<<endl, void();
    ll ans=k*(k-1)/2+(x==k? k-1:x)*(n-k);
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