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
int n,m,dfn[N],low[N],tim,st[N],_top,cnt;
vector<int> g[N],ng[N];
void tarjan(int x) {
	dfn[x]=low[x]=++tim, st[++_top]=x;
	for(auto y:g[x]) {
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]) {
				cnt++;
				ng[x].push_back(n+cnt), ng[n+cnt].push_back(x);
				while(st[_top+1]!=y) {
					ng[st[_top]].push_back(n+cnt);
					ng[n+cnt].push_back(st[_top]);
					_top--;
				}
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
int fa[N],top[N],sz[N],son[N],dep[N],w[N];
void dfs(int x,int from) {
	sz[x]=1, fa[x]=from, dep[x]=dep[from]+1, son[x]=0;
	if(x<=n) w[x]=1;
	for(auto y:ng[x]) if(y!=from) {
		dfs(y,x), sz[x]+=sz[y];
		if(!son[x]||sz[y]>sz[son[x]]) son[x]=y;
	}
}
void dfs1(int x) {
	dfn[x]=++tim, w[x]+=w[fa[x]];
	if(son[x]) top[son[x]]=top[x], dfs1(son[x]);
	for(auto y:ng[x]) if(y!=fa[x]&&y!=son[x]) {
		top[y]=y, dfs1(y);
	}
}
int lca(int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return (dep[x]<dep[y])? x:y;
}
void calc() {
	vector<int> nd;
	int total; cin>>total;
	for(int i=1,x;i<=total;i++) cin>>x, nd.push_back(x);
	sort(nd.begin(),nd.end(),[](const int &x,const int &y) { return dfn[x]<dfn[y]; });
	int u=-1,ans=0;
	for(int i=0;i<(int)nd.size();i++) {
		int j=(i+1<(int)nd.size())? i+1:0;
		int l=lca(nd[i],nd[j]);
		if(u==-1||dep[l]<dep[u]) u=l;
		ans+=w[nd[i]]+w[nd[j]]-2*w[l];
	}
	ans/=2;
	if((~u)&&u<=n) ans++;
	cout<<ans-total<<endl; 
}
void solve() {
	cin>>n>>m;
	for(int i=1;i<=(n<<1);i++) g[i].clear(), ng[i].clear(), w[i]=dfn[i]=0;
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y;
		g[x].push_back(y), g[y].push_back(x);
	}
	tim=_top=cnt=0, tarjan(1), dfs(1,0);
	tim=0, top[1]=1, dfs1(1);
	int q; cin>>q;
	while(q--) calc();
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
