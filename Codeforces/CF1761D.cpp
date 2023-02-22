#include<bits/stdc++.h>
#include <cstdio>
using namespace std;
#define ll long long
const ll Mod=1e9+7;
const int N=1e6+10;
ll fac[N],inv[N],three[N];
ll Mul(ll x,ll y) {
	ll sum=1;
	while(y) {
		if(y&1) sum=sum*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return sum;
}
void init() {
	fac[0]=three[0]=inv[0]=1;
	for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod, three[i]=three[i-1]*3ll%Mod;
	inv[N-1]=Mul(fac[N-1],Mod-2);
	for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll C(ll x,ll y) {
    if(x==-1&&y==-1) return 1;
    if(x<0||y<0||x<y) return 0;
	return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
int n,k;
ll calc(int x,int y) {
    if((x>k||y>n-k)&&n-2*x+1<0) return 0;
    return C(k-1,x-1)*C(n-k-1,y-1)%Mod*(((x!=y+1&&n-2*x>=0)? three[n-2*x]:0)+((x==y||x==y+1)? three[n-2*x+1]:0))%Mod;
}
int main() {
	init();
    scanf("%d%d",&n,&k);
    ll ans=0;
    for(int x=0;x<=n/2+n%2;x++) {
        ans=((ans+calc(x,x-1))%Mod+calc(x,x)+calc(x,x+1))%Mod;
    }
    printf("%lld\n",ans);
	return 0;
}