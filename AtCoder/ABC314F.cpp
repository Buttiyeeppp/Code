#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define xxzx
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=998244353;
const int N=4e5+10;
bool mem1;
int n;
ll v[N],fa[N],tot,sz[N];
vector<int> g[N];
int find(int x) {
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
void dfs(int x) {
	for(auto y:g[x]) {
		v[y]=(v[y]+v[x])%Mod;
		dfs(y);
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=2*n;i++) fa[i]=i,sz[i]=1;
	tot=n;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		int fx=find(x), fy=find(y);
		ll inv=Pow(sz[fx]+sz[fy],Mod-2);
		v[fx]=(v[fx]+sz[fx]*inv)%Mod, v[fy]=(v[fy]+sz[fy]*inv)%Mod;
		fa[fx]=++tot, fa[fy]=tot, sz[tot]=sz[fx]+sz[fy];
		g[tot].push_back(fx), g[tot].push_back(fy);
	}
	dfs(tot);
	for(int i=1;i<=n;i++) cout<<v[i]<<" ";
	cout<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

