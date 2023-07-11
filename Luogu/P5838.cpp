#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,t[N],fa[N][21],dep[N],col[N],ans[N];
vector<int> g[N];
struct query {
	int f,c,id;
};
vector<query> q[N];
void dfs1(int x,int from) {
	col[t[x]]++;
	for(auto now:q[x]) ans[now.id]+=now.f*col[now.c];
	for(auto y:g[x]) if(y!=from) dfs1(y,x);
	col[t[x]]--;
}
void dfs(int x,int from) {
	fa[x][0]=from, dep[x]=dep[from]+1;
	for(auto y:g[x]) if(y!=from) dfs(y,x);
}
int lca(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	for(int h=dep[x]-dep[y],i=0;h;i++,h>>=1)
		if(h&1) x=fa[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)
		if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
	return fa[x][0];
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>t[i];
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		g[x].push_back(y), g[y].push_back(x);
	}
	dfs(1,0);
	for(int j=1;j<=20;j++)
		for(int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
	for(int i=1,a,b,c;i<=m;i++) {
		cin>>a>>b>>c;
		q[a].push_back({1,c,i});
		q[b].push_back({1,c,i});
		q[fa[lca(a,b)][0]].push_back({-2,c,i});
	}
	dfs1(1,0);
	for(int i=1;i<=m;i++) cout<<(ans[i]!=0);
	cout<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

