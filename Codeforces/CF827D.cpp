#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,dep[N],fa[N][20],mx[N][20];
int f[N],yep[N],ans[N],faid[N];
struct edge {
	int id,x,y,z;
	bool operator<(const edge &q)const {
		return z<q.z;
	}
}eg[N],neg[N];
vector<edge> g[N];
void dfs(int x,int from) {
	for(auto to:g[x]) if(to.y!=from) {
		fa[to.y][0]=x, mx[to.y][0]=to.z, dep[to.y]=dep[x]+1, faid[to.y]=to.id;
		dfs(to.y,x);
	}
}
int find(int x) {
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
PII lca(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	int res=0;
	for(int h=dep[x]-dep[y],i=0;h;h>>=1,i++)
		if(h&1) res=max(res,mx[x][i]), x=fa[x][i];
	if(x==y) return {x,res};
	for(int i=19;i>=0;i--)
		if(fa[x][i]!=fa[y][i]) res=max({res,mx[x][i],mx[y][i]}), x=fa[x][i], y=fa[y][i];
	return {fa[x][0],max({res,mx[x][0],mx[y][0]})};
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1,x,y,z;i<=m;i++) {
		cin>>x>>y>>z;
		eg[i]={i,x,y,z};
	}
	sort(eg+1,eg+m+1);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++) {
		int fx=find(eg[i].x), fy=find(eg[i].y);
		if(fx!=fy) {
			f[fx]=fy, yep[i]=1;
			g[eg[i].x].push_back({eg[i].id,-1,eg[i].y,eg[i].z}), g[eg[i].y].push_back({eg[i].id,-1,eg[i].x,eg[i].z});
		}
	}
	dfs(1,0);
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1], mx[i][j]=max(mx[i][j-1],mx[fa[i][j-1]][j-1]);
	int tot=0;
	for(int i=1;i<=m;i++) ans[i]=-1;
	for(int i=1;i<=m;i++) if(!yep[i]) {
		ans[eg[i].id]=lca(eg[i].x,eg[i].y).second-1;
		neg[++tot]=eg[i];
	}
	sort(neg+1,neg+tot+1);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=tot;i++) {
		int x=neg[i].x, y=neg[i].y, l=lca(x,y).first;
		x=find(x);
		while(dep[x]>dep[l]) {
			ans[faid[x]]=neg[i].z-1;
			f[x]=find(fa[x][0]);
			x=f[x];	
		}
		x=find(y);
		while(dep[x]>dep[l]) {
			ans[faid[x]]=neg[i].z-1;
			f[x]=find(fa[x][0]);
			x=f[x];	
		}
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<" ";
	cout<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
