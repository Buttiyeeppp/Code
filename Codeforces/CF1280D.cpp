#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=3e3+10;
bool mem1;
int n,m,w[N],f[N][N],sz[N];
ll g[N][N],c[N],d[N];
vector<int> G[N];
void dfs(int x,int from) {
	f[x][1]=0, g[x][1]=w[x], sz[x]=1;
	for(auto y:G[x]) if(y!=from) {
		dfs(y,x);
		for(int i=1;i<=sz[x]+sz[y];i++) c[i]=d[i]=-1e18;
		for(int i=1;i<=sz[x];i++)
			for(int j=1;j<=sz[y];j++) {
				if(f[x][i]+f[y][j]+(g[y][j]>0)>c[i+j]) c[i+j]=f[x][i]+f[y][j]+(g[y][j]>0), d[i+j]=g[x][i];
				else if(f[x][i]+f[y][j]+(g[y][j]>0)==c[i+j]) d[i+j]=max(d[i+j],g[x][i]);
				if(f[x][i]+f[y][j]>c[i+j-1]) c[i+j-1]=f[x][i]+f[y][j], d[i+j-1]=g[x][i]+g[y][j];
				else if(f[x][i]+f[y][j]==c[i+j-1]) d[i+j-1]=max(d[i+j-1],g[x][i]+g[y][j]);
			}
		for(int i=1;i<=sz[x]+sz[y];i++) f[x][i]=c[i], g[x][i]=d[i];
		sz[x]+=sz[y];
	}
}
void solve() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>w[i], G[i].clear();
	for(int i=1,x;i<=n;i++) cin>>x, w[i]=x-w[i];
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		G[x].push_back(y), G[y].push_back(x);
	}
	memset(f,0,sizeof(0)), memset(g,-0x3f,sizeof(g));
	dfs(1,0);
	cout<<f[1][m]+(g[1][m]>0)<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
