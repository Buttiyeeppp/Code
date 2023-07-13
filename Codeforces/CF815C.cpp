#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=5e3+10;
bool mem1;
int n,b,c[N],d[N],sz[N];
ll g[N][2],f[N][N][2];
vector<int> G[N];
void dfs(int x) {
	sz[x]=1;
	f[x][0][0]=0, f[x][1][0]=c[x], f[x][1][1]=c[x]-d[x];
	for(auto y:G[x]) {
		dfs(y);
		for(int i=0;i<=sz[x]+sz[y];i++) g[i][1]=f[x][i][1], g[i][0]=f[x][i][0]; 
		for(int i=0;i<=sz[x];i++)
			for(int j=0;j<=sz[y];j++) {
				g[i+j][1]=min(g[i+j][1],f[x][i][1]+min(f[y][j][1],f[y][j][0])),
				g[i+j][0]=min(g[i+j][0],f[x][i][0]+f[y][j][0]);
			}
		for(int i=0;i<=sz[x]+sz[y];i++) f[x][i][1]=g[i][1], f[x][i][0]=g[i][0];
		sz[x]+=sz[y];
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>b;
	for(int i=1,x;i<=n;i++) {
		cin>>c[i]>>d[i];
		if(i>1) cin>>x, G[x].push_back(i);
	}
	memset(f,0x3f,sizeof(f));
	dfs(1);
	for(int i=n;i>=0;i--) 
		if(min(f[1][i][0],f[1][i][1])<=b) { cout<<i<<endl; break; }
		
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

