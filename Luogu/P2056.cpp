#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,sz[N],fa[N],rt,mx,m,vis[N];
vector<int> g[N];
void find(int x,int from) {
	sz[x]=1;
	int v=0;
	for(auto y:g[x]) if(y!=from&&!vis[y]) {
		find(y,x);
		sz[x]+=sz[y];
		v=max(v,sz[y]);
	}
	v=max(v,m-sz[x]);
	if(v<mx) mx=v, rt=x;
}
struct Treap {
	priority_queue<int> a,b;
	void insert(int x) { a.push(x); }
	void erase(int x) { b.push(x); }
	int size() { return a.size()-b.size(); }
	void pop() {
		while(b.size()&&a.top()==b.top()) a.pop(), b.pop();
		a.pop();
	}
	int top1() {
		while(b.size()&&a.top()==b.top()) a.pop(), b.pop();
		return a.top();
	}
	int top2() {
		int u=top1(),v; pop();
		v=top1(), insert(u);
		return v;
	}
}v1[N],v2[N],ans;
int d[N],f;
void dfs(int x,int from) {
	v2[f].insert(d[x]);
	for(auto y:g[x]) if(y!=from&&!vis[y]) {
		d[y]=d[x]+1;
		dfs(y,x);
	}
}
void build(int x) {
	vis[x]=1;
	find(x,0);
	v1[x].insert(0);
	for(auto y:g[x]) if(!vis[y]) {
		m=sz[y], mx=INT_MAX, find(y,0);
		fa[rt]=x;
		d[y]=1, f=rt, dfs(y,x);
		v1[x].insert(v2[rt].top1());
		build(rt);
	}
	if(v1[x].size()>1) ans.insert(v1[x].top1()+v1[x].top2());
}
int col[N],dis[N][20],cnt;
void change(int x) {
	if(col[x]) {
		cnt--;
		if(v1[x].size()>1) ans.erase(v1[x].top1()+v1[x].top2());
		v1[x].erase(0);
		if(v1[x].size()>1) ans.insert(v1[x].top1()+v1[x].top2());
		for(int i=x,tot=1;fa[i];i=fa[i],tot++) {
			if(v1[fa[i]].size()>1) ans.erase(v1[fa[i]].top1()+v1[fa[i]].top2());
			v1[fa[i]].erase(v2[i].top1());
			v2[i].erase(dis[x][tot]);
			if(v2[i].size()) v1[fa[i]].insert(v2[i].top1());
			if(v1[fa[i]].size()>1) ans.insert(v1[fa[i]].top1()+v1[fa[i]].top2());
		}
	}
	else {
		cnt++;
		if(v1[x].size()>1) ans.erase(v1[x].top1()+v1[x].top2());
		v1[x].insert(0);
		if(v1[x].size()>1) ans.insert(v1[x].top1()+v1[x].top2());
		for(int i=x,tot=1;fa[i];i=fa[i],tot++) {
			if(v1[fa[i]].size()>1) ans.erase(v1[fa[i]].top1()+v1[fa[i]].top2());
			if(v2[i].size()) v1[fa[i]].erase(v2[i].top1());
			v2[i].insert(dis[x][tot]);
			v1[fa[i]].insert(v2[i].top1());
			if(v1[fa[i]].size()>1) ans.insert(v1[fa[i]].top1()+v1[fa[i]].top2());
		}
	}
	col[x]^=1;
}
int top[N],son[N],dep[N],fat[N];
void dfs1(int x,int from) {
	dep[x]=dep[from]+1, sz[x]=1, fat[x]=from;
	for(auto y:g[x]) if(y!=from) {
		dfs1(y,x);
		if(!son[x]||sz[son[x]]<sz[y]) son[x]=y;
	}
}
void dfs2(int x,int from) {
	if(son[x]) top[son[x]]=top[x], dfs2(son[x],x);
	for(auto y:g[x]) if(y!=from&&y!=son[x]) {
		top[y]=y, dfs2(y,x);
	}
}
int lca(int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fat[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return x;
}
int dist(int x,int y) {
	int l=lca(x,y);
	return dep[x]+dep[y]-2*dep[l];
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,x,y;i<n;i++) cin>>x>>y, g[x].push_back(y), g[y].push_back(x);
	m=n, mx=INT_MAX, find(1,0);
	build(rt);
	dfs1(1,0), top[1]=1, dfs2(1,0);
	for(int i=1;i<=n;i++)
		for(int j=fa[i],tot=1;j;j=fa[j],tot++) dis[i][tot]=dist(i,j);
	for(int i=1;i<=n;i++) col[i]=1;
	int Q; cin>>Q;
	cnt=n;
	for(int i=1,x;i<=Q;i++) {
		char op; cin>>op;
		if(op=='C') cin>>x, change(x);
		else {
			if(cnt==1) cout<<0<<endl;
			else if(cnt==0) cout<<-1<<endl;
			else cout<<ans.top1()<<endl;
		}
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
