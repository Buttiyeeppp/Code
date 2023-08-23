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
int n,m,q,w[N];
vector<int> g[N],ng[N];
int dfn[N],low[N],tim,st[N],_top,cnt;
multiset<int> s[N];
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
int fa[N],top[N],sz[N],son[N],dep[N],pos[N];
void dfs(int x,int from) {
	sz[x]=1, fa[x]=from, dep[x]=dep[from]+1;
	for(auto y:ng[x]) if(y!=from) {
		if(x>n) s[x].insert(w[y]);
		dfs(y,x), sz[x]+=sz[y];
		if(!son[x]||sz[y]>sz[son[x]]) son[x]=y;
	}
}
void dfs1(int x) {
	dfn[x]=++tim, pos[tim]=x;
	if(son[x]) top[son[x]]=top[x], dfs1(son[x]);
	for(auto y:ng[x]) if(y!=fa[x]&&y!=son[x]) {
		top[y]=y, dfs1(y);
	}
}
int v[N<<2];
#define ls (id<<1)
#define rs (id<<1|1)
void Build(int id,int l,int r) {
	if(l==r) return v[id]=w[pos[l]], void();
	int mid=(l+r)>>1;
	Build(ls,l,mid), Build(rs,mid+1,r);
	v[id]=min(v[ls],v[rs]);
}
void Modify(int id,int l,int r,int x,int val) {
	if(l==r) return v[id]=val, void();
	int mid=(l+r)>>1;
	if(x<=mid) Modify(ls,l,mid,x,val);
	else Modify(rs,mid+1,r,x,val);
	v[id]=min(v[ls],v[rs]);
}
int Query(int id,int l,int r,int x,int y) {
	if(x<=l&&y>=r) return v[id];
	int mid=(l+r)>>1;
	if(y<=mid) return Query(ls,l,mid,x,y);
	else if(x>mid) return Query(rs,mid+1,r,x,y);
	else return min(Query(ls,l,mid,x,y),Query(rs,mid+1,r,x,y));
}
int Qry(int x,int y) {
	int res=INT_MAX;
	while(top[x]!=top[y]) {
		res=min(res,Query(1,1,n+cnt,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	res=min(res,Query(1,1,n+cnt,dfn[y],dfn[x]));
	return res;
}
int lca(int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return (dep[x]<dep[y])? x:y;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++) cin>>w[i];
	for(int i=1,x,y;i<=m;i++) cin>>x>>y, g[x].push_back(y), g[y].push_back(x);
	tarjan(1), dfs(1,0);
	tim=0, top[1]=1, dfs1(1);
	for(int i=n+1;i<=n+cnt;i++) w[i]=*s[i].begin();
	Build(1,1,n+cnt);	
	for(int i=1,x,y;i<=q;i++) {
		char op; cin>>op>>x>>y;
		if(op=='C') {
			Modify(1,1,n+cnt,dfn[x],y);
			if(fa[x]) {
				s[fa[x]].erase(s[fa[x]].find(w[x]));
				s[fa[x]].insert(y);
				Modify(1,1,n+cnt,dfn[fa[x]],*s[fa[x]].begin());
			}
			w[x]=y;
		}
		else {
			int l=lca(x,y);
			cout<<min({Qry(x,l),Qry(y,l),(l>n&&fa[l])? w[fa[l]]:INT_MAX})<<endl;
		}
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
