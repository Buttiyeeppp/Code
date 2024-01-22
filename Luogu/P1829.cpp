#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=20101009;
const int N=1e7+10;
bool mem1;
ll pri[N],mu[N],s[N];
vector<int> P;
void init() {
    mu[1]=1;
    for(int i=2;i<N;i++) {
        if(!pri[i]) mu[i]=-1, P.push_back(i);
        for(auto now:P) {
            if(1ll*now*i>=N) break;
            pri[now*i]=1;
            if(i%now==0) { mu[now*i]=0; break; }
            mu[now*i]=mu[i]*-1;
        }
    }
    for(ll i=1;i<N;i++) {
        s[i]=((s[i-1]+mu[i]*i*i)%Mod+Mod)%Mod;
    }
}
void Add(ll &x,ll y) { return x=(x+y>=Mod)? x+y-Mod:x+y, void(); }
ll f(ll n,ll m) {
    ll res=0;
    for(ll l=1,r;l<=min(n,m);l=r+1) {
        r=min(n/(n/l),m/(m/l));
        Add(res,(s[r]-s[l-1]+Mod)%Mod*((1+(n/l))*(n/l)/2%Mod)%Mod*((1+(m/l))*(m/l)/2%Mod)%Mod);
    }
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    ll n,m; cin>>n>>m;
    ll ans=0;
    for(ll l=1,r;l<=min(n,m);l=r+1) {
        r=min(n/(n/l),m/(m/l));
        Add(ans,(l+r)*(r-l+1)/2%Mod*f(n/l,m/l)%Mod);
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}