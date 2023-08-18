#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
#define ls (id<<1)
#define rs (id<<1|1)
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,v[N],sz[N],son[N],fa[N];
int dfn[N],ed[N],tim,top[N],f[N][2],g[N][2];
vector<int> eg[N];
void dfs(int x,int from) {
	sz[x]=1, fa[x]=from;
	for(auto y:eg[x]) if(y!=from) {
		dfs(y,x);
		sz[x]+=sz[y];
		if(!son[x]||sz[y]>sz[son[x]]) son[x]=y;
	}
}
void dfs1(int x) {
	dfn[x]=ed[x]=++tim;
	f[x][1]=g[x][1]=v[x];
	if(son[x]) {
		top[son[x]]=top[x], dfs1(son[x]);
		f[x][1]+=f[son[x]][0], f[x][0]+=max(f[son[x]][0],f[son[x]][1]);
		ed[x]=ed[son[x]];
	}
	for(auto y:eg[x]) if(y!=fa[x]&&y!=son[x]) {
		top[y]=y, dfs1(y);
		f[x][1]+=f[y][0], f[x][0]+=max(f[y][0],f[y][1]);
		g[x][1]+=f[y][0], g[x][0]+=max(f[y][0],f[y][1]);
	}
}
struct Matrix {
	int a[3][3];
	Matrix() { memset(a,0,sizeof(a)); }
	Matrix operator*(const Matrix &q)const {
		Matrix res;
		for(int i=1;i<=2;i++)
			for(int j=1;j<=2;j++)
				for(int k=1;k<=2;k++) res.a[i][j]=max(res.a[i][j],a[i][k]+q.a[k][j]);
		return res;
	}
}ma[N],s[N<<2];
void Build(int id,int l,int r) {
	if(l==r) return s[id]=ma[l], void();
	int mid=(l+r)>>1;
	Build(ls,l,mid), Build(rs,mid+1,r);
	s[id]=s[rs]*s[ls];
}
void Modify(int id,int l,int r,int x) {
	if(l==r) return s[id]=ma[l], void();
	int mid=(l+r)>>1;
	if(x<=mid) Modify(ls,l,mid,x);
	else Modify(rs,mid+1,r,x);
	s[id]=s[rs]*s[ls];
}
Matrix Query(int id,int l,int r,int x,int y) {
	if(x<=l&&y>=r) return s[id];
	int mid=(l+r)>>1;
	if(y<=mid) return Query(ls,l,mid,x,y);
	else if(x>mid) return Query(rs,mid+1,r,x,y);
	else return Query(rs,mid+1,r,x,y)*Query(ls,l,mid,x,y);
}
void Update(int x,int y) {
	ma[dfn[x]].a[1][2]+=y-v[x];
	v[x]=y;
	while(x) {
		int nd=top[x];
		Matrix res1=Query(1,1,n,dfn[nd],ed[nd]);
		Modify(1,1,n,dfn[x]);
		Matrix res2=Query(1,1,n,dfn[nd],ed[nd]);
		x=fa[nd];
		ma[dfn[x]].a[1][1]+=max(res2.a[1][1],res2.a[1][2])-max(res1.a[1][1],res1.a[1][2]);
		ma[dfn[x]].a[2][1]=ma[dfn[x]].a[1][1];
		ma[dfn[x]].a[1][2]+=res2.a[1][1]-res1.a[1][1];
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>v[i];
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		eg[x].push_back(y), eg[y].push_back(x);
	}
	dfs(1,0);
	top[1]=1, dfs1(1);
	for(int i=1;i<=n;i++) {
		ma[dfn[i]].a[1][1]=ma[dfn[i]].a[2][1]=g[i][0];
		ma[dfn[i]].a[1][2]=g[i][1];
		ma[dfn[i]].a[2][2]=-0x3f3f3f3f;
	}
	Build(1,1,n);
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y;
		Update(x,y);
		Matrix ans=Query(1,1,n,dfn[1],ed[1]);
		cout<<max(ans.a[1][1],ans.a[1][2])<<endl;
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
