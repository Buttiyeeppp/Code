#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e5+10;
bool mem1;
int n,k,r,fa[N],dis[N],f[N][20],dep[N];
vector<int> g[N];
void dfs(int x,int from) {
	f[x][0]=from, dep[x]=dep[from]+1;
	for(auto y:g[x]) 
		if(y!=from) dfs(y,x);
}
int find(int x) {
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
int Jump(int x,int h) {
	for(int i=0;h;h>>=1,i++)
		if(h&1) x=f[x][i];
	return x;
}
int lca(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	x=Jump(x,dep[x]-dep[y]);
	if(x==y) return x;
	for(int i=19;i>=0;i--)
		if(f[x][i]!=f[y][i]) x=f[x][i], y=f[y][i];
	return f[x][0];
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>k>>r;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		g[x].push_back(i+n), g[i+n].push_back(x);
		g[y].push_back(i+n), g[i+n].push_back(y);
	}
	n+=n-1;
	queue<int> q;
	for(int i=1;i<=n;i++) fa[i]=i, dis[i]=-1;
	for(int i=1,x;i<=r;i++) {
		cin>>x;
		dis[x]=0, q.push(x);
	}
	while(q.size()) {
		int x=q.front(); q.pop();
		if(dis[x]==k) continue;
		for(auto y:g[x]) {
			fa[find(x)]=find(y);
			if(dis[y]==-1) dis[y]=dis[x]+1, q.push(y);
		}
	}
	dfs(1,0);
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++) f[i][j]=f[f[i][j-1]][j-1];
	int Q; cin>>Q;
	for(int i=1,x,y;i<=Q;i++) {
		cin>>x>>y;
		int l=lca(x,y);
		if(dep[x]+dep[y]-2*dep[l]<=2*k) cout<<"YES"<<endl;
		else {
			int l1=dep[x]-dep[l], l2=dep[y]-dep[l], mx=x;
			if(k<=l1) x=Jump(x,k);
			else x=Jump(y,l2-k+l1);
			if(k<=l2) y=Jump(y,k);
			else y=Jump(mx,l1-k+l2);
			cout<<((find(x)==find(y))? "YES":"NO")<<endl;
		}
	}

	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
