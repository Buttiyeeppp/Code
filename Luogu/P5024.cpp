#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const ll INF=0x3f3f3f3f3f3f3f3f;
bool mem1;
string type;
int n,m,p[N],fa[N][20],dep[N];
ll f[N][2],g[N][2],h[N][20][2][2];
vector<int> eg[N];
void dfs(int x,int from) {
	fa[x][0]=from, dep[x]=dep[from]+1, f[x][1]=p[x];
	for(auto y:eg[x]) if(y!=from) {
		dfs(y,x);
		f[x][1]+=min(f[y][0],f[y][1]);
		f[x][0]+=f[y][1];
	}
}
void dfs1(int x) {
	for(auto y:eg[x]) if(y!=fa[x][0]) {
		g[y][0]=g[x][1]+f[x][1]-min(f[y][0],f[y][1]);
		g[y][1]=min(g[x][0]+f[x][0]-f[y][1],g[y][0]);
		dfs1(y);
	}
}
ll calc(int x,int a,int y,int b) {
	if(dep[x]<dep[y]) swap(x,y), swap(a,b);
	ll nx[2]={INF,INF}, ny[2]={INF,INF}, c[2];
	nx[a]=f[x][a], ny[b]=f[y][b];
	for(int hi=dep[x]-dep[y],i=0;hi;i++,hi>>=1) if(hi&1) {
		for(int j=0;j<2;j++) c[j]=min({INF,h[x][i][0][j]+nx[0],h[x][i][1][j]+nx[1]});
		nx[0]=c[0], nx[1]=c[1], x=fa[x][i];
	}
	if(x==y) return nx[b]+g[y][b];
	for(int i=19;i>=0;i--)
		if(fa[x][i]!=fa[y][i]) {
			for(int j=0;j<2;j++) c[j]=min({INF,h[x][i][0][j]+nx[0],h[x][i][1][j]+nx[1]});
			nx[0]=c[0], nx[1]=c[1], x=fa[x][i];
			for(int j=0;j<2;j++) c[j]=min({INF,h[y][i][0][j]+ny[0],h[y][i][1][j]+ny[1]});
			ny[0]=c[0], ny[1]=c[1], y=fa[y][i];
		}
	int lca=fa[x][0];
	return min(f[lca][0]-f[x][1]-f[y][1]+nx[1]+ny[1]+g[lca][0],
			   f[lca][1]-min(f[x][1],f[x][0])-min(f[y][1],f[y][0])+min(nx[1],nx[0])+min(ny[1],ny[0])+g[lca][1]);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>type;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		eg[x].push_back(y), eg[y].push_back(x);
	}
	dfs(1,0), dfs1(1);
	memset(h,0x3f,sizeof(h));
	for(int i=1;i<=n;i++) {
		int j=fa[i][0];
		h[i][0][0][1]=h[i][0][1][1]=f[j][1]-min(f[i][0],f[i][1]);
		h[i][0][1][0]=f[j][0]-f[i][1];
	}
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++) {
			fa[i][j]=fa[fa[i][j-1]][j-1];
			for(int a=0;a<2;a++)
				for(int b=0;b<2;b++) {
					for(int c=0;c<2;c++) h[i][j][a][b]=min(h[i][j][a][b],h[i][j-1][a][c]+h[fa[i][j-1]][j-1][c][b]);
				}
		}
	for(int i=1,a,x,b,y;i<=m;i++) {
		cin>>x>>a>>y>>b;
		if((fa[x][0]==y||fa[y][0]==x)&&a+b==0) cout<<-1<<endl;
		else cout<<calc(x,a,y,b)<<endl;
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
