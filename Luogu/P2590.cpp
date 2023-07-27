#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#define ls (id<<1)
#define rs (id<<1|1)
#define xxzx
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e4+10;
bool mem1;
int n,w[N],mx[N<<2],s[N<<2];
int dfn[N],pos[N],tim,sz[N],top[N],dep[N],fa[N],son[N];
vector<int> g[N];
void dfs1(int x,int from) {
	dfn[x]=++tim, pos[tim]=x, fa[x]=from;
	if(son[x]) top[son[x]]=top[x], dfs1(son[x],x);
	for(auto y:g[x]) if(y!=from&&y!=son[x]) top[y]=y, dfs1(y,x);
}
void dfs(int x,int from) {
	sz[x]=1, dep[x]=dep[from]+1;
	for(auto y:g[x]) if(y!=from) {
		dfs(y,x);
		sz[x]+=sz[y];
		if(!son[x]||sz[y]>sz[son[x]]) son[x]=y;
	}
}
void Build(int id,int l,int r) {
	if(l==r) return mx[id]=s[id]=w[pos[l]], void();
	int mid=(l+r)>>1;
	Build(ls,l,mid), Build(rs,mid+1,r);
	mx[id]=max(mx[ls],mx[rs]), s[id]=s[ls]+s[rs];
}
void Modify(int id,int l,int r,int x,int v) {
	if(l==r) return mx[id]=s[id]=v, void();
	int mid=(l+r)>>1;
	if(x<=mid) Modify(ls,l,mid,x,v);
	else Modify(rs,mid+1,r,x,v);
	mx[id]=max(mx[ls],mx[rs]), s[id]=s[ls]+s[rs];
}
PII Query(int id,int l,int r,int x,int y) {
	if(x<=l&&y>=r) return {mx[id],s[id]}; 
	int mid=(l+r)>>1;
	if(y<=mid) return Query(ls,l,mid,x,y);
	else if(x>mid) return Query(rs,mid+1,r,x,y);
	else {
		PII lres=Query(ls,l,mid,x,y), rres=Query(rs,mid+1,r,x,y);
		return {max(lres.first,rres.first),lres.second+rres.second};
	}
}
int Max(int x,int y) {
	int res=INT_MIN;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=max(res,Query(1,1,n,dfn[top[x]],dfn[x]).first);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	res=max(res,Query(1,1,n,dfn[x],dfn[y]).first);
	return res;
}
int Sum(int x,int y) {
	int res=0;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res+=Query(1,1,n,dfn[top[x]],dfn[x]).second;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	res+=Query(1,1,n,dfn[x],dfn[y]).second;
	return res;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,a,b;i<n;i++) {
		cin>>a>>b;
		g[a].push_back(b), g[b].push_back(a);
	}
	for(int i=1;i<=n;i++) cin>>w[i];
	dfs(1,0);
	top[1]=1;
	dfs1(1,0);
	Build(1,1,n);
	int Q; cin>>Q;
	while(Q--) {
		string op; int u,v;
		cin>>op>>u>>v;
		if(op=="CHANGE") Modify(1,1,n,dfn[u],v);
		if(op=="QMAX") cout<<Max(u,v)<<endl;
		if(op=="QSUM") cout<<Sum(u,v)<<endl;
	}

	#ifdef xxzx
	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}
