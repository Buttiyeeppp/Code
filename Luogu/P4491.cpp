#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e7+10;
const ll Mod=1004535809;
bool mem1;
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
int fac[N],inv[N],invv[N];
void init() {
    fac[0]=inv[0]=invv[0]=1;
    for(int i=1;i<N;i++) fac[i]=1ll*fac[i-1]*i%Mod;
    inv[N-1]=Pow(fac[N-1],Mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%Mod;
    for(int i=1;i<N;i++) invv[i]=1ll*inv[i]*fac[i-1]%Mod;
}
ll C(int x,int y) {
    if(x<y) return 0;
    return 1ll*fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
int tr[N];
int init(int len) {
    int n=1;
    while(n<=len) n<<=1;
    for(int i=0;i<n;i++) tr[i]=(tr[i>>1]>>1)|((i&1)? n>>1:0);
    return n;
}
void NTT(int *f,int n,int op) {
    for(int i=0;i<n;i++)
        if(i<tr[i]) swap(f[i],f[tr[i]]);
    for(int l=2,nl=1;l<=n;l<<=1,nl<<=1) {
        for(int i=0;i<n;i+=l) {
            int t=Pow(3,(Mod-1)/l),d=1;
            if(op==-1) t=Pow(t,l-1);
            for(int j=i;j<i+nl;j++) {
                int a=f[j], b=1ll*d*f[j+nl]%Mod;
                f[j]=(a+b)%Mod, f[j+nl]=(a-b+Mod)%Mod;
                d=1ll*d*t%Mod;
            }
        }
    }
    if(op==-1) {
        int inv=Pow(n,Mod-2);
        for(int i=0;i<n;i++) f[i]=1ll*f[i]*inv%Mod;
    }
}
void Mul(int *f,int *g,int n) {
    n=init(n);
    NTT(f,n,1), NTT(g,n,1);
    for(int i=0;i<n;i++) f[i]=1ll*f[i]*g[i]%Mod;
    NTT(f,n,-1);
}
int c[N];
void Inv(int *h,int *f,int n) {
    if(n==1) return h[0]=Pow(f[0],Mod-2), void();
    int m=(n+1)>>1;
    Inv(h,f,m);
    int len=init(n<<1);
    for(int i=0;i<n;i++) c[i]=f[i];
    fill(c+n,c+len,0), fill(h+m,h+len,0);
    NTT(h,len,1), NTT(c,len,1);
    for(int i=0;i<len;i++) h[i]=1ll*h[i]*(2-1ll*c[i]*h[i]%Mod+Mod)%Mod;
    NTT(h,len,-1);
    fill(h+n,h+len,0);
}
void deri(int *h,int *f,int n) {
    for(int i=0;i<n;i++) h[i]=1ll*f[i+1]*(i+1)%Mod;
}
void inte(int *h,int *f,int n) {
    h[0]=0;
    for(int i=1;i<n;i++) h[i]=1ll*f[i-1]*invv[i]%Mod;
}
int a[N],b[N];
void Ln(int *h,int *f,int n) {
    memset(a,0,sizeof(a)), memset(b,0,sizeof(b));
    deri(a,f,n), Inv(b,f,n);
    Mul(a,b,n<<1);
    inte(h,a,n);
}
int d[N];
void Exp(int *h,int *f,int n) {
    n=init(n), h[0]=1;
    for(int l=2;l<=n;l<<=1) {
        Ln(d,h,l);
        fill(d+l,d+(l<<1),0);
        for(int i=0;i<l;i++) d[i]=(f[i]-d[i]+Mod)%Mod;
        d[0]=(d[0]+1)%Mod;
        Mul(h,d,l);
        fill(h+l,h+(l<<1),0);
    }
}
int n,m,s,w[N],f[N],F[N],G[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    cin>>n>>m>>s;
    for(int i=0;i<=m;i++) cin>>w[i];
    int len=min(n/s,m);
    for(int i=0,val=1;i<=len;i++) {
        f[i]=1ll*C(m,i)*val%Mod*Pow(m-i,n-s*i)%Mod;
        val=1ll*val*C(n-s*i,s)%Mod;
    }
    for(int i=0;i<=len;i++) {
        F[i]=1ll*fac[i]*f[i]%Mod;
        G[i]=inv[i];
        if(i&1) G[i]=Mod-G[i];
    }
    reverse(F,F+len+1);
    Mul(F,G,len<<1);
    reverse(F,F+len+1);
    for(int i=0;i<=len;i++) F[i]=1ll*F[i]*inv[i]%Mod;
    ll ans=0;
    for(int i=0;i<=len;i++) ans=(ans+1ll*w[i]*F[i])%Mod;
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}