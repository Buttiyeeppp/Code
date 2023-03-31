#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+10;
const int M=5e5+10;
const ll Mod=998244353;
int n,k,b[N],appear[M];
ll fac[M],inv[M];
ll Mul(ll x,ll y) {
	ll sum=1;
	while(y) {
		if(y&1) sum=sum*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return sum;
}
void init() {
	fac[0]=1;
	for(int i=1;i<M;i++) fac[i]=fac[i-1]*i%Mod;
	inv[M-1]=Mul(fac[M-1],Mod-2);
	for(int i=M-2;i;i--) inv[i]=inv[i+1]*(i+1)%Mod;
	return;
}
ll C(ll x,ll y) {
	if(x<y||y<0) return 0;
	if(y==0||x==y) return 1;
	return fac[x]*inv[y]%Mod*inv[x-y]%Mod;		
}
int main() {
	init();
	scanf("%d%d",&n,&k);
	for(int i=1,x;i<=n;i++) scanf("%d",&x), appear[x]=1;
	for(int i=1,j=0;i<=k+1;i++) {
		while(appear[j]) j++;
		b[i]=(j++);
	}
	ll ans=0;
	for(int i=1;i<=k+1;i++) {
//		cerr<<i<<" "<<b[i]<<" "<<C(k-(i-1)+b[i]-1,b[i]-1)<<" "<<k-(i-1)+b[i]-1<<" "<<b[i]-1<<endl;
		ans=(ans+C(k-(i-1)+b[i]-1,b[i]-1))%Mod;
	}
	printf("%lld",ans);
	return 0;
}