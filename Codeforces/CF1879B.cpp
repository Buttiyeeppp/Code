#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int n;
void solve() {
    cin>>n;
    ll s1=0, s2=0, mn1=1e17, mn2=1e17;
    for(int i=1,x;i<=n;i++) cin>>x, s1+=x, mn1=min(mn1,(ll)x);
    for(int i=1,x;i<=n;i++) cin>>x, s2+=x, mn2=min(mn2,(ll)x);
    cout<<min(s1+mn2*n,s2+mn1*n)<<endl;
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