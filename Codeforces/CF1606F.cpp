#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const int B=490;
bool mem1;
int n,f[N][B+10],sz[N],Q,ans[N],g[N];
vector<int> eg[N];
void dfs1(int x,int from) {
	for(auto y:eg[x]) if(y!=from) {
		dfs1(y,x);
		for(int i=0;i<=B;i++) f[x][i]+=max(1,f[y][i]-i);
	}
}
void dfs2(int x,int from) {
	sz[x]=1;
	for(auto y:eg[x]) if(y!=from) {
		dfs2(y,x);
		for(int i=0;i<=min(sz[x]+sz[y],B);i++) g[i]=f[x][i]+1;
		for(int i=0;i<=min(sz[x],B);i++) {
			for(int j=0;j<=min(sz[y],B-i-1);j++) g[i+j+1]=max(g[i+j+1],f[x][i]+f[y][j]);
		}
		for(int i=0;i<=min(sz[x]+sz[y],B);i++) f[x][i]=g[i];
		sz[x]+=sz[y];
	}	
}
struct Query {
	int v,k;
}q[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		eg[x].push_back(y), eg[y].push_back(x);
	}
	cin>>Q;
	for(int i=1;i<=Q;i++) cin>>q[i].v>>q[i].k;
	dfs1(1,0);
	for(int i=1;i<=Q;i++) if(q[i].k<=B) ans[i]=f[q[i].v][q[i].k];
	memset(f,0,sizeof(f));
	dfs2(1,0);
	for(int i=1;i<=Q;i++) if(q[i].k>B) {
		for(int j=0;j<=B;j++) ans[i]=max(ans[i],f[q[i].v][j]-j*q[i].k);
	}
	for(int i=1;i<=Q;i++) cout<<ans[i]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
