#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
const ll Mod=1e9+7;
bool mem1;
int n,a[N],sz[N];
vector<int> g[N];
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
ll fac[N],inv[N];
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
	inv[N-1]=Pow(fac[N-1],Mod-2);
	for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll C(ll x,ll y) {
	if(x<y) return 0;
	return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
ll ans=1;
void dfs(int x) {
	sz[x]=1;
	ll A=0,B=0,v1=1,v2=1;
	for(auto y:g[x]) {
		dfs(y), a[x]+=a[y], sz[x]+=sz[y];
		A+=sz[y], v1=v1*C(A,sz[y])%Mod;
		B+=a[y]-sz[y], v2=v2*C(B,a[y]-sz[y])%Mod;
	}
	ans=ans*v1%Mod*v2%Mod;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	init();
	cin>>n;
	for(int i=2,x;i<=n;i++) cin>>x, g[x].push_back(i);
	for(int i=1;i<=n;i++) cin>>a[i];
	dfs(1);
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

