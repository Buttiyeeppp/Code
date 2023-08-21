#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,k,rt,mx,m,sz[N],vis[N];
vector<PII> g[N];
void find(int x,int from) {
	int v=0;
	for(auto y:g[x]) if(y.first!=from&&!vis[y.first]) {
		find(y.first,x);
		v=max(v,sz[y.first]);
	}
	v=max(v,m-sz[x]);
	if(v<mx) mx=v, rt=x;
}
ll d1[N],d2[N],f[N],ans=1e18;
vector<int> nd;
void dfs(int x,int from) {
	nd.push_back(x), sz[x]=1;
	if(d2[x]<=k) ans=min(ans,d1[x]+f[k-d2[x]]);
	for(auto y:g[x]) if(y.first!=from&&!vis[y.first]) {
		d1[y.first]=d1[x]+1, d2[y.first]=d2[x]+y.second;
		dfs(y.first,x);
		sz[x]+=sz[y.first];
	}
}
void sol(int x) {
	vector<int> mem;
	for(auto y:g[x]) if(!vis[y.first]) {
		d1[y.first]=1, d2[y.first]=y.second;
		nd.clear();
		dfs(y.first,x);
		for(auto now:nd) if(d2[now]<=k) f[d2[now]]=min(f[d2[now]],d1[now]), mem.push_back(d2[now]);
	}
	for(auto now:mem) if(now) f[now]=1e15;
	vis[x]=1;
	for(auto y:g[x]) if(!vis[y.first]) {
		mx=INT_MAX, m=sz[y.first], find(y.first,0);
		sol(rt);
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>k;
	for(int i=1,x,y,z;i<n;i++) {
		cin>>x>>y>>z;
		x++,y++;
		g[x].emplace_back(y,z), g[y].emplace_back(x,z);
	}
	memset(f,0x3f,sizeof(f)), f[0]=0;
	mx=INT_MAX, m=n, find(1,0);
	sol(rt);
	cout<<(ans<n? ans:-1)<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

