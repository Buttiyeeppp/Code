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
ll m,n=1,f[N],g[N],h[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
int tr[N];
void NTT(ll *f,int n,int op) {
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
void inv(ll *h,int n) {
    if(n==1) return h[0]=Pow(f[0],Mod-2), void();
    int m=(n+1)>>1, len=1;
    inv(h,m);
    while(len<(n<<1)) len<<=1;
    for(int i=0;i<n;i++) g[i]=f[i];
    for(int i=n;i<len;i++) g[i]=0;
    for(int i=m;i<len;i++) h[i]=0;
    NTT(h,len,1), NTT(g,len,1);
    for(int i=0;i<len;i++) h[i]=h[i]*(2-g[i]*h[i]%Mod+Mod)%Mod;
    NTT(h,len,-1);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>m;
    for(int i=0;i<m;i++) cin>>f[i];
    while(n<m) n<<=1;
    inv(h,n);
    for(int i=0;i<m;i++) cout<<h[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}