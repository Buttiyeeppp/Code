#include<bits/stdc++.h>
#include <cstdio>
using namespace std;
#define ll long long
const int N=3e6+10;
ll fac[N],inv[N],Mod;
ll Mul(ll x,ll y) {
	ll sum=1;
	while(y) {
		if(y&1) sum=sum*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return sum;
}
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
	inv[N-1]=Mul(fac[N-1],Mod-2);
	for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll C(ll x,ll y) {
    if(x<0||y<0||x<y) return 0;
	return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
int n;
int main() {
    scanf("%d%lld",&n,&Mod);
	init();
    ll ans, f=1, v;
    v=(2ll*fac[2*n]%Mod-fac[n]-f+Mod+Mod)%Mod, ans=v, f=(f+v)%Mod;
    v=2ll*C(2*n,n)%Mod*fac[n]%Mod*fac[2*n]%Mod;
    for(int a=0;a<=n;a++) v=(v-C(n,a)*C(n,n-a)%Mod*Mul(fac[n],3)%Mod*C(n+a,a)%Mod+Mod)%Mod;
    v=(v-f+Mod)%Mod, ans=(ans+2ll*v%Mod)%Mod, f=(f+v)%Mod;
    v=(fac[3*n]-f+Mod)%Mod, ans=(ans+3ll*v%Mod)%Mod;
    printf("%lld",ans);
	return 0;
}