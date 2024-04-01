#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e5+10;
const ll Mod=998244353;
bool mem1;
ll n,m,g[N],t[N],f[N],ans[N],tr[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
void NTT(ll *f,ll n,ll op) {
    for(int i=0;i<n;i++) tr[i]=(tr[i>>1]>>1)|((i&1)? n>>1:0);
    for(int i=0;i<n;i++)
        if(i<tr[i]) swap(f[i],f[tr[i]]);
    for(int l=2,nl=1;l<=n;l<<=1,nl<<=1) {
        for(int i=0;i<n;i+=l) {
            ll t=Pow(3,(Mod-1)/l), d=1;
            if(op==-1) t=Pow(t,l-1);
            for(int j=i;j<i+nl;j++) {
                ll a=f[j], b=d*f[j+nl]%Mod;
                f[j]=(a+b)%Mod, f[j+nl]=(a-b+Mod)%Mod;
                d=d*t%Mod;
            }
        }
    }
    if(op==-1) {
        ll inv=Pow(n,Mod-2);
        for(int i=0;i<n;i++) f[i]=f[i]*inv%Mod;
    }
}
void sol(int l,int r) {
    // cerr<<l<<" "<<r<<endl;
    if(l>=r) return;
    int mid=(l+r)>>1;
    sol(l,mid);
    int len=r-l+1;
    for(int i=0;i<len;i++) t[i]=g[i];
    for(int i=l;i<=r;i++) f[i-l]=(i<=mid? ans[i]:0);
    NTT(t,len,1), NTT(f,len,1);
    for(int i=0;i<len;i++) f[i]=f[i]*t[i]%Mod;
    NTT(f,len,-1);
    for(int i=mid+1;i<=r;i++) ans[i]=(ans[i]+f[i-l])%Mod;
    sol(mid+1,r);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>m;
    for(int i=1;i<m;i++) cin>>g[i];
    n=ans[0]=1;
    while(n<m) n<<=1;
    sol(0,n-1);
    for(int i=0;i<m;i++) cout<<ans[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}