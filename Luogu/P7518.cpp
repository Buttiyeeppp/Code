#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
inline int read() {
	int f=1,z=0; char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { z=z*10+ch-'0'; ch=getchar(); }
	return f*z;
}
inline void write(int x) {
	if(x<0) putchar('-'), x=-x;
	if(x>=10) write(x/10);
	putchar((x%10)+'0');
}
int n,m,c,p[N],pos[N],w[N],q,ans[N];
int fa[N][20],dep[N],f[N][20],f1[N][20];
vector<int> g[N];
int rt[N],ls[N*20],rs[N*20],tot,v[N*20];
void Modify(int id1,int &id2,int l,int r,int x,int val) {
	if(!id2) id2=++tot;
	if(l==r) return v[id2]=val, void();
	int mid=(l+r)>>1;
	if(x<=mid) rs[id2]=rs[id1], Modify(ls[id1],ls[id2],l,mid,x,val);
	else ls[id2]=ls[id1], Modify(rs[id1],rs[id2],mid+1,r,x,val);
}
int Query(int id,int l,int r,int x) {
	if(x<0||x>m||!id) return 0;
	if(l==r) return v[id];
	int mid=(l+r)>>1;
	return (x<=mid)? Query(ls[id],l,mid,x):Query(rs[id],mid+1,r,x);
}
void dfs(int x) {
	Modify(rt[fa[x][0]],rt[x],1,m,w[x],x);
	for(auto y:g[x]) if(y!=fa[x][0]) {
		fa[y][0]=x, dep[y]=dep[x]+1;
		dfs(y);
	}
}
int lca(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	for(int h=dep[x]-dep[y],i=0;h;i++,h>>=1)
		if(h&1) x=fa[x][i];
	if(x==y) return x;
	for(int i=17;i>=0;i--)
		if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
	return fa[x][0];
}
int Jump(int x,int v) {
	for(int i=0;v;i++,v>>=1)
		if(v&1) x=fa[x][i];
	return x;
}
int nxt[N],pre[N];
bool check(int s,int t,int _p,int x) {
	s=Query(rt[s],1,m,p[_p+x-1]);
	int res=0;
//	for(int i=17;i>=0;i--) {
//		if(f1[s][i]&&dep[f1[s][i]]>=dep[t]) res+=(1<<i), s=pre[f1[s][i]];
//	}
	if(f1[s][17]&&dep[f1[s][17]]>=dep[t]) res+=(1<<17), s=pre[f1[s][17]];
	if(f1[s][16]&&dep[f1[s][16]]>=dep[t]) res+=(1<<16), s=pre[f1[s][16]];
	if(f1[s][15]&&dep[f1[s][15]]>=dep[t]) res+=(1<<15), s=pre[f1[s][15]];
	if(f1[s][14]&&dep[f1[s][14]]>=dep[t]) res+=(1<<14), s=pre[f1[s][14]];
	if(f1[s][13]&&dep[f1[s][13]]>=dep[t]) res+=(1<<13), s=pre[f1[s][13]];
	if(f1[s][12]&&dep[f1[s][12]]>=dep[t]) res+=(1<<12), s=pre[f1[s][12]];
	if(f1[s][11]&&dep[f1[s][11]]>=dep[t]) res+=(1<<11), s=pre[f1[s][11]];
	if(f1[s][10]&&dep[f1[s][10]]>=dep[t]) res+=(1<<10), s=pre[f1[s][10]];
	if(f1[s][9]&&dep[f1[s][9]]>=dep[t]) res+=(1<<9), s=pre[f1[s][9]];
	if(f1[s][8]&&dep[f1[s][8]]>=dep[t]) res+=(1<<8), s=pre[f1[s][8]];
	if(f1[s][7]&&dep[f1[s][7]]>=dep[t]) res+=(1<<7), s=pre[f1[s][7]];
	if(f1[s][6]&&dep[f1[s][6]]>=dep[t]) res+=(1<<6), s=pre[f1[s][6]];
	if(f1[s][5]&&dep[f1[s][5]]>=dep[t]) res+=(1<<5), s=pre[f1[s][5]];
	if(f1[s][4]&&dep[f1[s][4]]>=dep[t]) res+=(1<<4), s=pre[f1[s][4]];
	if(f1[s][3]&&dep[f1[s][3]]>=dep[t]) res+=(1<<3), s=pre[f1[s][3]];
	if(f1[s][2]&&dep[f1[s][2]]>=dep[t]) res+=(1<<2), s=pre[f1[s][2]];
	if(f1[s][1]&&dep[f1[s][1]]>=dep[t]) res+=(1<<1), s=pre[f1[s][1]];
	if(f1[s][0]&&dep[f1[s][0]]>=dep[t]) res+=(1<<0), s=pre[f1[s][0]];
	
	return (res>=x);
}
bool mem2;
int main() {
//	freopen("P7518_11.in","r",stdin);
//	freopen("a.txt","w",stdout);
	ios::sync_with_stdio(false), cin.tie(0);
	
	n=read(), m=read(), c=read();
	for(int i=1;i<=c;i++) p[i]=read(), pos[p[i]]=i;
	for(int i=1;i<=n;i++) w[i]=read();
	for(int i=1,x,y;i<n;i++) {
		x=read(), y=read();
		g[x].push_back(y), g[y].push_back(x);
	}
	dfs(1);
	for(int i=1;i<=n;i++) 
		nxt[i]=Query(rt[i],1,m,p[pos[w[i]]+1]), pre[i]=Query(rt[i],1,m,p[pos[w[i]]-1]);
	for(int i=1;i<=n;i++) f[i][0]=f1[i][0]=(pos[w[i]]? i:0);
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n;i++) {
			f[i][j]=f[nxt[f[i][j-1]]][j-1];
			f1[i][j]=f1[pre[f1[i][j-1]]][j-1];
			fa[i][j]=fa[fa[i][j-1]][j-1];
		}
	q=read();
	for(int i=1,s,t,_lca,res;i<=q;i++) {
		s=read(), t=read();
		_lca=lca(s,t), res=0;
		int u=Query(rt[s],1,m,p[1]);
		for(int j=17;j>=0;j--) {
			if(res+(1<<j)<=c&&f[u][j]&&dep[f[u][j]]>=dep[_lca]) {
				res+=(1<<j);
				if(res==c||f[u][j]==1) break;
				u=nxt[f[u][j]];
			}
		}
		if(_lca==t) ans[i]=res;
		else {
			int u=Jump(t,dep[t]-dep[_lca]-1);
			int l=0,r=c-res+1;
			while(l+1<r) {
				int mid=(l+r)>>1;
				if(check(t,u,res+1,mid)) l=mid;
				else r=mid;
			}
			ans[i]=res+l;	
		}
	}
	for(int i=1;i<=q;i++) write(ans[i]), putchar('\n');
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
