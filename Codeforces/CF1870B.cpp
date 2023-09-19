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
int n,m,a[N],b[N];
void solve() {
    cin>>n>>m;
    int ans1=0,ans2=0;
    for(int i=1;i<=n;i++) cin>>a[i], ans1^=a[i];
    int x=0;
    for(int i=1;i<=m;i++) cin>>b[i], x|=b[i];
    for(int i=1;i<=n;i++) a[i]|=x;
    for(int i=1;i<=n;i++) ans2^=a[i];
    if(n&1) swap(ans1,ans2);
    cout<<ans2<<" "<<ans1<<endl;
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