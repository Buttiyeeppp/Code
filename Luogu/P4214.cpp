#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e4+10;
bool mem1;
int n,m,fa[N],head[N],tot=1;
struct edge {
	int nxt,to;
}g[N];
void add(int x,int y) {
	g[++tot]={head[x],y};
	head[x]=tot;
}
PII eg[N];
int find(int x) {
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y) {
	int fx=find(x), fy=find(y);
	if(fx!=fy) fa[fx]=fy;
}
int a,b,tim,dfn[N],low[N],bri[N],col[N];
void tarjan(int x,int from) {
	dfn[x]=low[x]=++tim;
	for(int i=head[x];i;i=g[i].nxt) if((i^1)!=from) {
		int y=g[i].to;
		if((x==a&&y==b)||(x==b&&y==a)) continue;
		if(!dfn[y]) {
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x]) bri[i]=bri[i^1]=1;
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
const ll P=1331;
const ll Mod=1e9+7;
ll hs[N];
void dfs(int x) {
	col[x]=tim;
	if(a) hs[x]=(hs[x]*P+col[x])%Mod;
	for(int i=head[x];i;i=g[i].nxt) if(!bri[i]) {
		int y=g[i].to;
		if((x==a&&y==b)||(x==b&&y==a)) continue;
		if(!col[y]) dfs(y);
	}
}
void e_dcc() {
	memset(dfn,0,sizeof(dfn)), memset(bri,0,sizeof(bri)), tim=0;
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,0);
	memset(col,0,sizeof(col)), tim=0;
	for(int i=1;i<=n;i++) if(!col[i]) tim++, dfs(i);
}
int vis[N][N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y;
		eg[i]={x,y}, merge(x,y), add(x,y), add(y,x);
	}
	int cnt=n*(n-1)/2,ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++) if(find(i)!=find(j)) cnt--, vis[i][j]=1;
	e_dcc();
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++) if(!vis[i][j]&&col[i]!=col[j]) cnt--, ans++, vis[i][j]=1;
	for(int i=1;i<=m;i++) a=eg[i].first, b=eg[i].second, e_dcc();
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++) if(!vis[i][j]&&hs[i]!=hs[j]) cnt--, ans+=2;
	ans+=cnt*3;
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

