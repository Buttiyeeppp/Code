#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,tot,f[N],w[N],w1[N];
struct Edge {
	int u,v;
}eg[N];
vector<int> g[N];
int find(int x) { return (x==f[x])? x:f[x]=find(f[x]); }
int fa[N][20],dep[N],dfn[N],mxdfn[N],tim;
void dfs(int x,int from) {
	dfn[x]=++tim;
	for(auto y:g[x]) if(y!=from)
		dep[y]=dep[x]+1, fa[y][0]=x, dfs(y,x);
	mxdfn[x]=tim;
}
int lca(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	for(int h=dep[x]-dep[y],i=0;h;h>>=1,i++)
		if(h&1) x=fa[x][i];
	if(x==y) return x;
	for(int i=19;i>=0;i--)
		if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
	return fa[x][0];
}
int Jump(int x,int v) {
	for(int i=0;v;v>>=1,i++)
		if(v&1) x=fa[x][i];
	return x;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y;
		int fx=find(x), fy=find(y);
		if(fx!=fy) f[fx]=fy, g[x].push_back(y), g[y].push_back(x);
		else eg[++tot]=(Edge){x,y};
	}
	dfs(1,0);
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
	for(int i=1;i<=tot;i++) {
		int u=eg[i].u, v=eg[i].v, l=lca(u,v);
		if(l==u||l==v) {
			if(dep[u]>dep[v]) swap(u,v);
			u=Jump(v,dep[v]-dep[u]-1);
			w[dfn[u]]++, w[mxdfn[u]+1]--, w[dfn[v]]--, w[mxdfn[v]+1]++;
		}
		else w1[1]++, w1[dfn[u]]--, w1[mxdfn[u]+1]++, w1[dfn[v]]--, w1[mxdfn[v]+1]++;
	}
	for(int i=1;i<=n;i++) w[i]+=w[i-1], w1[i]+=w1[i-1];
	for(int i=1;i<=n;i++) cout<<(w[dfn[i]]==0&&w1[dfn[i]]==0);
	cout<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

