#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
const ll Mod=998244353;
bool mem1;
int n,a[N];
ll ans;
void calc(int x) {
    // vector<int> p;
    // for(int i=1;i<=n;i++) if(a[i]&(1<<x)) p.push_back(i);
    ll cnt=0, c[2]={0,0}, l[2]={0,0};
    ll res=0;
    for(int i=n;i>=1;i--) {
        // if(a[i]&(1<<x)) cnt^=1;
        int cur=((a[i]&(1<<x))!=0);
        c[cnt]+=i, l[cnt]++;
        // cerr<<x<<" "<<i<<" "<<c[cnt^cur^1]-(i-1)*l[cnt^cur^1]<<endl;
        res=(res+c[cnt^cur^1]-(i-1)*l[cnt^cur^1]%Mod+Mod)%Mod;
        cnt^=cur;
    }
    ans=(ans+(1<<x)*res)%Mod;
}
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=0;i<=30;i++) calc(i);
    cout<<ans<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T=1;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}