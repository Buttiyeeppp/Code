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
const ll inv2=499122177;
bool mem1;
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
                ll x=f[j], y=d*f[j+nl]%Mod;
                f[j]=(x+y)%Mod, f[j+nl]=(x-y+Mod)%Mod;
                d=d*t%Mod;
            }
        }
    }
    if(op==-1) {
        ll inv=Pow(n,Mod-2);
        for(int i=0;i<n;i++) f[i]=f[i]*inv%Mod;
    }
}
ll ginv[N];
void Inv(ll *f,ll *g,int n) {
    if(n==1) return f[0]=Pow(g[0],Mod-2), void();
    int m=(n+1)>>1, len=1;
    Inv(f,g,m);
    while(len<(n<<1)) len<<=1;
    for(int i=0;i<n;i++) ginv[i]=g[i];
    for(int i=n;i<len;i++) ginv[i]=0;
    NTT(f,len,1), NTT(ginv,len,1);
    for(int i=0;i<len;i++) f[i]=f[i]*(2-ginv[i]*f[i]%Mod+Mod)%Mod;
    NTT(f,len,-1);
    for(int i=n;i<len;i++) f[i]=0;
}
ll gsqr[N],fi[N];
void Sqrt(ll *f,ll *g,int n) {
    if(n==1) return f[0]=1,void();
    int m=(n+1)>>1, len=1;
    Sqrt(f,g,m);
    while(len<(n<<1)) len<<=1;
    for(int i=0;i<len;i++) gsqr[i]=fi[i]=0;
    for(int i=0;i<n;i++) gsqr[i]=g[i];
    Inv(fi,f,n);
    NTT(fi,len,1), NTT(f,len,1), NTT(gsqr,len,1);
    for(int i=0;i<len;i++) f[i]=(f[i]+fi[i]*gsqr[i])%Mod*inv2%Mod;
    NTT(f,len,-1);
    for(int i=n;i<len;i++) f[i]=0;
}
ll n,f[N],g[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=0;i<n;i++) cin>>g[i];
    Sqrt(f,g,n);
    for(int i=0;i<n;i++) cout<<f[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}