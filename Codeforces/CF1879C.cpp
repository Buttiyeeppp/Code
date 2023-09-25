#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=998244353;
const int N=2e5+10;
bool mem1;
string s;
ll fac[N];
void init() {
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
}
void solve() {
    cin>>s;
    int n=s.size(),cnt=0;
    ll ans=0, res=1;
    for(int i=0;i<n;i++) {
        if(i==0||s[i]!=s[i-1]) {
            if(cnt) ans+=cnt-1, res=res*cnt%Mod;
            cnt=1;
        }
        else cnt++;
    }
    if(cnt) ans+=cnt-1, res=res*cnt%Mod;
    cout<<ans<<" "<<res*fac[ans]%Mod<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}