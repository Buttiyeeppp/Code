#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,Q;
struct SegmentTree {
	int rt[N],s[N*20],ls[N*20],rs[N*20],tot;
	SegmentTree() { 
		tot=0; 
		memset(rt,0,sizeof(rt)), memset(s,0,sizeof(s)), memset(ls,0,sizeof(ls)), memset(rs,0,sizeof(rs)); 
	}
	void build(int &id,int l,int r) {
		id=++tot;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(ls[id],l,mid), build(rs[id],mid+1,r);
	}
	void Modify(int &id,int l,int r,int x) {
		tot++, s[tot]=s[id]+1, ls[tot]=ls[id], rs[tot]=rs[id], id=tot;
		if(l==r) return;
		int mid=(l+r)>>1;
		if(x<=mid) Modify(ls[id],l,mid,x);
		else Modify(rs[id],mid+1,r,x);
	}
	int Kth(int id1,int id2,int l,int r,int v) {
		if(l==r) return l;
		int x=s[ls[id2]]-s[ls[id1]], mid=(l+r)>>1;
		if(x>=v) return Kth(ls[id1],ls[id2],l,mid,v);
		else return Kth(rs[id1],rs[id2],mid+1,r,v-x);
	}
}St;
struct TemplateTree {
	int fa[N][20],dep[N],dfn[N],mxdfn[N],tim,pos[N];
	TemplateTree() {
		tim=0;
		memset(fa,0,sizeof(fa)), memset(dep,0,sizeof(dep)), memset(pos,0,sizeof(pos));
		memset(dfn,0,sizeof(dfn)), memset(mxdfn,0,sizeof(mxdfn));
	}
	vector<int> g[N];
	void dfs(int x,int from) {
		dfn[x]=++tim, pos[tim]=x;
		fa[x][0]=from, dep[x]=dep[from]+1;
		for(auto y:g[x]) if(y!=from) dfs(y,x);
		mxdfn[x]=tim;
	}
	void build() {
		for(int i=1,x,y;i<n;i++) 
			cin>>x>>y, g[x].push_back(y), g[y].push_back(x);
		dfs(1,0);
		for(int j=1;j<20;j++)
			for(int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
		St.build(St.rt[0],1,n);
		for(int i=1;i<=n;i++) St.Modify(St.rt[i]=St.rt[i-1],1,n,pos[i]);
	}
	int lca(int x,int y) {
		if(dep[x]<dep[y]) swap(x,y);
		for(int h=dep[x]-dep[y],i=0;h;h>>=1,i++)
			if(h&1) x=fa[x][i];
		if(x==y) return x;
		for(int i=19;i>=0;i--)
			if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
		return fa[x][0];
	}
	int dis(int x,int y) {
		int l=lca(x,y);
		return dep[x]+dep[y]-2*dep[l];
	}
}Tt;
struct BigTree {
	int pre[N],node,fa[N][20],dep[N];
	ll st[N],cnt,dist[N][20],lnk[N];
	BigTree() { 
		node=cnt=0;
		memset(pre,0,sizeof(pre)),memset(dep,0,sizeof(dep)), memset(fa,0,sizeof(fa));
		memset(st,0,sizeof(st)), memset(dist,0,sizeof(dist)), memset(lnk,0,sizeof(lnk));
	}
	int Getroot(ll x) {
		int l=0, r=node+1;
		while(l+1<r) {
			int mid=(l+r)>>1;
			if(x>=st[mid]) l=mid;
			else r=mid;
		}
		return l;
	}
	int Getpre(ll x) {
		int rt=Getroot(x), id=pre[rt];
		return St.Kth(St.rt[Tt.dfn[id]-1],St.rt[Tt.mxdfn[id]],1,n,x-st[rt]+1);
	}
	void build() {
		node=1, st[1]=1, cnt=n, pre[1]=1;
		for(int i=1;i<=m;i++) {
			ll x,y; cin>>x>>y; 
			ll rty=Getroot(y); node++;
			lnk[node]=y, pre[node]=x,st[node]=++cnt;
			dep[node]=dep[rty]+1, fa[node][0]=rty, dist[node][0]=Tt.dep[Getpre(y)]-Tt.dep[pre[rty]]+1;
            cnt+=Tt.mxdfn[x]-Tt.dfn[x];
		}
		for(int j=1;j<20;j++)
			for(int i=1;i<=node;i++) fa[i][j]=fa[fa[i][j-1]][j-1], dist[i][j]=dist[i][j-1]+dist[fa[i][j-1]][j-1];
	}
	int lca(int x,int y) {
		if(dep[x]<dep[y]) swap(x,y);
		for(int h=dep[x]-dep[y],i=0;h;h>>=1,i++)
			if(h&1) x=fa[x][i];
		if(x==y) return x;
		for(int i=19;i>=0;i--)
			if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
		return fa[x][0];
	}
	ll dis(ll x,ll y) {
		int rtx=Getroot(x), rty=Getroot(y);
		if(rtx==rty) {
			x=Getpre(x), y=Getpre(y);
			return Tt.dis(x,y);
		}
		ll disx=Tt.dep[Getpre(x)]-Tt.dep[pre[rtx]], disy=Tt.dep[Getpre(y)]-Tt.dep[pre[rty]], ans=0;
        ll memx=x, memy=y;
		x=rtx, y=rty;
		if(dep[x]<dep[y]) swap(x,y), swap(disx,disy), swap(memx,memy);
		if(lca(x,y)==y) {
			for(int h=dep[x]-dep[y]-1,i=0;h;h>>=1,i++)
				if(h&1) ans+=dist[x][i], x=fa[x][i];
			x=Getpre(lnk[x]), y=Getpre(memy);
			return disx+ans+Tt.dis(x,y)+1;
		}
		for(int h=dep[x]-dep[y],i=0;h;h>>=1,i++)
			if(h&1) ans+=dist[x][i], x=fa[x][i];
		for(int i=19;i>=0;i--)
			if(fa[x][i]!=fa[y][i]) ans+=dist[x][i]+dist[y][i], x=fa[x][i], y=fa[y][i];
		x=Getpre(lnk[x]), y=Getpre(lnk[y]);
		return disx+disy+ans+Tt.dis(x,y)+2;
	}
	
}Bt;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>Q;
	Tt.build(), Bt.build();
	for(int i=1;i<=Q;i++) {
		ll x,y; cin>>x>>y;
		cout<<Bt.dis(x,y)<<endl;
	}
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}