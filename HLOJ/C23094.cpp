#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,ll>;
const int N=1e5+10;
bool mem1;
int n,m,vis[N],fa[N],dfn[N],mxdfn[N],tim;
ll dis[N],ans[N];
vector<PII> eg[N];
struct edge {
	int x,y,l;
}g2[N];
void dfs(int x,int from) {
	fa[x]=from, dfn[x]=++tim;
	for(auto y:eg[x]) if(y.first!=from) {
		dis[y.first]=dis[x]+y.second;
		dfs(y.first,x);
	}
	mxdfn[x]=tim;
}
void calc(int x,int y,int l) {
	if(fa[x]!=y) {
		int u=y;
		while(dfn[x]<dfn[u]||dfn[x]>mxdfn[u]) {
			ans[u]=min(ans[u],dis[x]+l+dis[y]-dis[u]);
			u=fa[u];
		}
	}
	
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	int tot2=0;
	for(int i=1,x,y,l,op;i<=m;i++) {
		cin>>x>>y>>l>>op;
		if(op) eg[x].emplace_back(y,l), eg[y].emplace_back(x,l);
		else g2[++tot2]=(edge){x,y,l};
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) ans[i]=1e17;
	for(int i=1;i<=tot2;i++) {
		int x=g2[i].x, y=g2[i].y, l=g2[i].	l;
		calc(x,y,l), calc(y,x,l);
	}
	for(int i=2;i<=n;i++) cout<<((ans[i]==1e17)? -1:ans[i])<<" ";
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
/*
5 9 
 3 1 3 1
  1 4 2 1 
 2 1 6 0 
 2 3 4 0 
 5 2 3 0 
 3 2 2 1 
 5 3 1 1 
 3 5 2 0 
 4 5 4 0
*/
