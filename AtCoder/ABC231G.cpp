#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e3+10;
const ll Mod=998244353;
int n,k,d[N];
ll f[N],g[N];
ll Mul(ll x,ll y) {
    ll sum=1;
    while(y) {
        if(y&1) sum=sum*x%Mod;
        x=x*x%Mod;
        y>>=1;
    }
    return sum;
}
ll fac[N],inv[N];
void init() {
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Mul(fac[N-1],Mod-2);
    for(int i=N-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
int main() {
    init();
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);
    f[0]=1;
    for(int i=1;i<=n;i++)
        for(int j=i;j>=1;j--) f[j]=(f[j]+f[j-1]*d[i])%Mod;
    ll invn=Mul(n,Mod-2);
    g[0]=Mul(n,k);
    for(int i=1;i<=min(n,k);i++) g[i]=g[i-1]*(k-i+1)%Mod*invn%Mod;
    ll ans=0;
    for(int i=0;i<=min(n,k);i++) ans=(ans+g[i]*f[n-i])%Mod;
    printf("%lld",ans*Mul(Mul(n,k),Mod-2)%Mod);
    return 0;
}