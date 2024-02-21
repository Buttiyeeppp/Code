#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e3+10;
const ll Mod=998244353;
bool mem1;
int n,k,x[N],y[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
    ll ans=0;
    for(int i=1;i<=n;i++) {
        ll res=y[i];
        for(int j=1;j<=n;j++) if(i!=j) {
            res=res*(k-x[j]+Mod)%Mod;
            res=res*Pow((x[i]-x[j]+Mod)%Mod,Mod-2)%Mod;
        }
        ans=(ans+res)%Mod;
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}