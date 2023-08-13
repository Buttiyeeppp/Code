#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=998244353;
const int N=1.1e6;
bool mem1;
ll n,f[22][N],g[22][N],fac[N],inv[N];
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
ll C(ll x,ll y) {
	if(x<0||y<0||x<y) return 0;
	return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	init();
	cin>>n;
	int m=(1<<n);
	for(int i=m;i>=1;i--) g[n][i]=(g[n][i+1]+C(i-1-Pow(2,n-1),Pow(2,n-1)-1))%Mod;
	for(int i=n-1;i>=0;i--) {
		for(int j=m;j>=1;j--) {
			f[i][j]=g[i+1][j+1]*fac[Pow(2,i)]%Mod*2%Mod;
			if(i) g[i][j]=(g[i][j+1]+f[i][j]*C(j-1-Pow(2,i-1),Pow(2,i-1)-1))%Mod;
		}
	}
	for(int i=m;i>=1;i--) cout<<f[0][i]<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

