#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e3+10;
const ll Mod=998244353;
bool mem1;
ll n,k,f[N],fac[N];
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
void init() {
	fac[0]=1;
	for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
}
void solve() {
	cin>>n>>k;
	for(int i=0;i<=n;i++) f[i]=0;
	f[k]=fac[k];
	for(int i=k;i<=n;i++)
		for(int j=1;i+j<=n&&j<k;j++)
			f[i+j]=(f[i+j]-f[i]*fac[j]%Mod+Mod)%Mod;
	ll ans=0;
//	for(int i=k;i<=n;i++) cout<<f[i]<<" "; 
//	cout<<endl;
	for(int i=k;i<=n;i++) ans=(ans+(n-i+1)*f[i]%Mod*Pow(k,n-i))%Mod;
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	init();
	int T=1;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
