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
int n,m,dfn[N],low[N],tim,st[N],top,cnt,w[N],sz[N];
vector<int> g[N],ng[N];
void tarjan(int x) {
	dfn[x]=low[x]=++tim, st[++top]=x, ng[x].clear();
	for(auto y:g[x]) {
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]) {
				cnt++, w[cnt+n]=0, ng[cnt+n].clear();
				while(st[top+1]!=y) {
					ng[cnt+n].push_back(st[top]);
					ng[st[top]].push_back(cnt+n);
					top--, w[cnt+n]++;
				}
				ng[cnt+n].push_back(x);
				ng[x].push_back(cnt+n);
				w[cnt+n]++;
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
ll ans;
void dfs(int x,int from) {
	ll v=0;
	if(x<=n) w[x]=-1, sz[x]=1;
	for(auto y:ng[x]) if(y!=from) {
		dfs(y,x);
		v+=1ll*sz[x]*sz[y], sz[x]+=sz[y];
	}
	v+=1ll*(tim-sz[x])*sz[x], ans+=w[x]*v;
}
void sol(int x) {
	tim=top=0;
	tarjan(x), dfs(x,0);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++)
		cin>>x>>y, g[x].push_back(y), g[y].push_back(x);
	for(int i=1;i<=n;i++) if(!dfn[i]) sol(i);
	cout<<ans*2<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

