#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
using PLI=pair<ll,int>;
const int N=1e5+10;
bool mem1;
int n,t,Q,a[N],b[N],vis[N],fa[N][20],dep[N];
ll ans[N],dis[N],d1[N],d2[N],v1[N][20],v2[N][20];
string s;
vector<PII> g[N];
void dfs(int x,int from,int k) {
	fa[x][0]=from, dep[x]=dep[from]+1;
	for(auto y:g[x]) if(y.first!=from) {
		d1[y.first]=d1[x]+y.second;
		d2[y.first]=d2[x]+(y.second-1)/(1<<k)+1;
		dfs(y.first,x,k);
	}
}
struct node { ll l,r1,r2; };
node lca(int x,int y) {
	ll res1=dis[x]-d1[x]+d2[x],res2=dis[y]+d1[y]-d2[y];
	if(dep[x]>dep[y]) {
		for(int h=dep[x]-dep[y],i=0;h;h>>=1,i++)
			if(h&1) res1=min(res1,v1[x][i]), x=fa[x][i];
	}
	else {
		for(int h=dep[y]-dep[x],i=0;h;h>>=1,i++)
			if(h&1) res2=min(res2,v2[y][i]), y=fa[y][i];
	}
	if(x==y) return {x,res1,res2};
	for(int i=19;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			res1=min(res1,v1[x][i]), res2=min(res2,v2[y][i]), x=fa[x][i], y=fa[y][i];
	res1=min(res1,v1[x][0]), res2=min(res2,v2[y][0]);
	return {fa[x][0],res1,res2};
}
void calc(int k) {
	priority_queue<PLI,vector<PLI>,greater<PLI>> q;
	for(int i=1;i<=n;i++) {
		vis[i]=0, dis[i]=1e15;
		if(s[i-1]=='1') dis[i]=0, q.emplace(0,i);
	}
	while(q.size()) {
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(auto y:g[x]) {
			if(dis[y.first]>dis[x]+y.second+(y.second-1)/(1<<k)+1)
				dis[y.first]=dis[x]+y.second+(y.second-1)/(1<<k)+1, q.emplace(dis[y.first],y.first);
		}
	}
	dfs(1,0,k);
	for(int i=1;i<=n;i++) {
		int j=fa[i][0];
		v1[i][0]=dis[j]-d1[j]+d2[j], v2[i][0]=dis[j]+d1[j]-d2[j];	
	}
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++) {
			fa[i][j]=fa[fa[i][j-1]][j-1];
			v1[i][j]=min(v1[i][j-1],v1[fa[i][j-1]][j-1]);
			v2[i][j]=min(v2[i][j-1],v2[fa[i][j-1]][j-1]);
		}
	for(int i=1;i<=Q;i++) {
		node now=lca(a[i],b[i]);
		if(!k) ans[i]=min(ans[i],d1[a[i]]+d1[b[i]]-2*d1[now.l]);
		ans[i]=min({ans[i],
					k*t+now.r1+d1[a[i]]-2*d2[now.l]+d2[b[i]],
					k*t+now.r2+d1[a[i]]-2*d1[now.l]+d2[b[i]]
					});
	}
}
void solve() {
	cin>>n>>t;
	for(int i=1;i<=n;i++) g[i].clear();
	for(int i=1,x,y,z;i<n;i++) {
		cin>>x>>y>n>z;
		g[x].emplace_back(y,z), g[y].emplace_back(x,z);
	}
	cin>>s>>Q;
	for(int i=1;i<=Q;i++) cin>>a[i]>>b[i], ans[i]=1e15;
	for(int i=0;i<=20;i++) calc(i);
	for(int i=1;i<=Q;i++) cout<<ans[i]<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
