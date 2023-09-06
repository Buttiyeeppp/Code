#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const ll Mod=998244353;
bool mem1;
ll n,f[N],g[N],sz[N],ans;
vector<int> eg[N];
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
void dfs(int x,int from) {
	ll c=1; sz[x]=1;
	for(auto y:eg[x]) if(y!=from) {
		dfs(y,x);
		c=c*f[y]%Mod, sz[x]+=sz[y];
	}
	g[x]=c;
	if(x==1) {
		ans=c;
		for(int i=1;i<n;i++) ans=ans*i%Mod;
	}	
	for(auto y:eg[x]) if(y!=from) {
		g[x]=(g[x]+Pow(sz[x]-sz[y],Mod-2)*c%Mod*Pow(f[y],Mod-2)%Mod*g[y])%Mod;
	}
	f[x]=g[x]*Pow(sz[x],Mod-2)%Mod;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		eg[x].push_back(y), eg[y].push_back(x);
	}
	dfs(1,0);
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

