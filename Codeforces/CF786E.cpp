#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e4+10;
const int INF=0x3f3f3f3f;
bool mem1;
int n,m,top[N],sz[N],son[N],dfn[N],tim,dep[N],fa[N];
vector<int> g[N];
void dfs1(int x,int from) {
	if(!top[x]) top[x]=x;
	dfn[x]=++tim;
	if(son[x]) top[son[x]]=top[x], dfs1(son[x],x);
	for(auto y:g[x]) if(y!=from&&y!=son[x]) {
		dfs1(y,x);
	}
}
void dfs(int x,int from) {
	sz[x]=1, dep[x]=dep[from]+1, fa[x]=from;
	for(auto y:g[x]) if(y!=from) {
		dfs(y,x);
		sz[x]+=sz[y];
		if(!son[x]||sz[y]>sz[son[x]]) son[x]=y;
	}
}
int tot,rt,ls[N<<4],rs[N<<4];
int head[N<<4],cnt=1,s,t;
struct Edge {
	int x,to,nxt,w;
}e[N<<5];
void Add(int x,int y,int w) {
	e[++cnt]=Edge{x,y,head[x],w};
	head[x]=cnt;
	
	e[++cnt]=Edge{y,x,head[y],0};
	head[y]=cnt;
}
int pos[N<<4],eg[N<<4];
void build(int &id,int l,int r,int fa) {
	if(!id) id=++tot;
	if(fa) Add(fa,id,INF);
	if(l==r) return Add(id,t,1), pos[l]=id, void();
	int mid=(l+r)>>1;
	build(ls[id],l,mid,id), build(rs[id],mid+1,r,id);
}
void Modify(int id,int l,int r,int x,int y,int v) {
	if(x<=l&&y>=r) return Add(v,id,INF), void();
	int mid=(l+r)>>1;
	if(x<=mid) Modify(ls[id],l,mid,x,y,v);
	if(y>mid) Modify(rs[id],mid+1,r,x,y,v);
}
void add(int v,int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		Modify(rt,1,n,dfn[top[x]],dfn[x],v);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	if(x!=y) Modify(rt,1,n,dfn[y]+1,dfn[x],v);
}
int cur[N<<4],dis[N<<4];
bool bfs() {
	memcpy(cur,head,sizeof(cur));
	memset(dis,0x3f,sizeof(dis));
	queue<int> q;
	dis[s]=0; q.push(s);
	while(q.size()) {
		int u=q.front(); q.pop();
		for(int i=head[u];i>1;i=e[i].nxt) {
			int to=e[i].to;
			if(dis[to]>dis[u]+1&&e[i].w) dis[to]=dis[u]+1, q.push(to);
		}
	}
	return (dis[t]!=0x3f3f3f3f);
}
int dfs2(int x,int flow) {
	if(x==t||!flow) return flow;
	int use=0;
	for(int i=cur[x];i>1;i=e[i].nxt) {
		cur[x]=i;
		int to=e[i].to;
		if(dis[to]!=dis[x]+1||!e[i].w) continue;
		int v=dfs2(to,min(flow,e[i].w));
		if(!v) { dis[to]=-1; continue; }
		flow-=v, use+=v, e[i].w-=v, e[i^1].w+=v;
	}
	return use;
}
int vis[N<<4];
void dfs3(int x) {
	vis[x]=1;
	for(int i=head[x];i>1;i=e[i].nxt) 
		if(e[i].w&&!vis[e[i].to]) dfs3(e[i].to);
}
PII mem[N];
vector<int> ans1,ans2;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++) {
		cin>>u>>v;
		g[u].push_back(v), g[v].push_back(u);
		mem[i]=make_pair(u,v);
	}
	dfs(1,0), dfs1(1,0);
	s=m+1, t=m+2, tot=m+2;
	build(rt,1,n,0);
	for(int i=1,x,y;i<=m;i++) {
		Add(s,i,1);
		cin>>x>>y;
		add(i,x,y);
	}
	int ans=0;
	while(bfs()) ans+=dfs2(s,INF);
	cout<<ans<<endl;
	dfs3(s);
	for(int i=1;i<=m;i++) if(!vis[i]) ans1.push_back(i);
	for(int i=1;i<n;i++) {
		if(dep[mem[i].first]<dep[mem[i].second]) swap(mem[i].first,mem[i].second);
		if(vis[pos[dfn[mem[i].first]]]) ans2.push_back(i);
	}
	cout<<ans1.size()<<" ";
	for(auto now:ans1) cout<<now<<" "; cout<<endl;
	cout<<ans2.size()<<" ";
	for(auto now:ans2) cout<<now<<" "; cout<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}