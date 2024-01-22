#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=998244353;
const int N=30;
bool mem1;
ll n,fac[N],inv[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
void init() {
    fac[0]=inv[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Pow(fac[N-1],Mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll ans;
int a[N],cnt[N];
void Add(ll &x,ll y) { return x=(x+y>=Mod)? x+y-Mod:x+y, void(); } 
ll c(ll x) { return inv[x]*fac[x-1]%Mod; }
void dfs(int x,int step) {
    if(!x) {
        ll res=fac[n];
        memset(cnt,0,sizeof(cnt));
        for(int i=step-1;i>=1;i--)
            for(int j=1;j<=a[i];j++) {
                res=res*c((++cnt[j])+a[i]-j)%Mod;
            }
        Add(ans,res*res%Mod*a[1]%Mod);
        return;
    }
    int lim=x;
    if(step!=1) lim=min(lim,a[step-1]);
    for(int i=1;i<=lim;i++) {
        a[step]=i;
        dfs(x-i,step+1);
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    cin>>n;
    dfs(n,1);
    cout<<ans*inv[n]%Mod<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}