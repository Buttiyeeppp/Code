#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
const ll Mod=998244353;
bool mem1;
int n,m,t1[N],t2[N];
ll f[N],fac[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
void init() {
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1,x;i<=m;i++) cin>>x, t1[1<<(x-1)]++;
    for(int i=1,x;i<=m;i++) cin>>x, t2[1<<(x-1)]++;
    for(int i=0;i<n;i++)
        for(int s=0;s<(1<<n);s++)
            if(s&(1<<i)) t1[s]+=t1[s^(1<<i)], t2[s]+=t2[s^(1<<i)];
    init();
    ll ans=0;
    for(int s=1;s<(1<<n);s++) {
        if(t1[s]!=t2[s]) continue;
        f[s]=fac[t1[s]];
        for(int i=(s-1)&s;i;i=(i-1)&s) if(i&(s&(-s))){
            f[s]=(f[s]-f[i]*fac[t1[s]-t1[i]]%Mod+Mod)%Mod;
        }
        // cerr<<"FF "<<s<<" "<<f[s]<<" "<<m-t1[s]<<endl;
        ans=(ans+f[s]*fac[m-t1[s]])%Mod;
    }
    // cerr<<ans<<endl;
    cout<<ans*Pow(fac[m],Mod-2)%Mod<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}