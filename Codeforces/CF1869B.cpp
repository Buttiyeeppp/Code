#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
ll n,k,a,b,x[N],y[N];
void solve() {
    cin>>n>>k>>a>>b;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
    ll ans=abs(x[a]-x[b])+abs(y[a]-y[b]);
    ll mn1=1e15, mn2=1e15;
    for(int i=1;i<=k;i++) mn1=min(mn1,abs(x[i]-x[a])+abs(y[i]-y[a]));
    for(int i=1;i<=k;i++) mn2=min(mn2,abs(x[i]-x[b])+abs(y[i]-y[b]));
    ans=min(ans,mn1+mn2);
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