#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,Q,col[N],now[N],B;
vector<int> eg[N];
struct query {
	int x,y,l,r,t,sp,op;
	friend bool operator<(const query &q,const query &p) {
		if((q.l-1)/B==(p.l-1)/B) 
			return ((q.r-1)/B==(p.r-1)/B)? q.t<p.t:(q.r-1)/B<(p.r-1)/B;
		else return (q.l-1)/B<(p.l-1)/B;
	}
}q[N],opt[N];
int in[N],ou[N],tim,fa[N][20],dep[N],dfn[N<<1];
void dfs(int x,int from) {
	in[x]=++tim, dfn[tim]=x;
	fa[x][0]=from, dep[x]=dep[from]+1;
	for(auto y:eg[x]) if(y!=from) dfs(y,x);
	ou[x]=++tim, dfn[tim]=x;
}
int lca(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	for(int h=dep[x]-dep[y],i=0;h;h>>=1,i++)
		if(h&1) x=fa[x][i];
	if(x==y) return x;
	for(int j=19;j>=0;j--)
		if(fa[x][j]!=fa[y][j]) x=fa[x][j], y=fa[y][j];
	return fa[x][0];
}
int vis[N],cnt[N];
ll ans,Ans[N],w[N],v[N];
void upd(int x) {
	x=dfn[x];
	int c=col[x];
	if(vis[x]) ans-=w[cnt[c]]*v[c], cnt[c]--;
	else cnt[c]++, ans+=w[cnt[c]]*v[c];
	vis[x]^=1;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>Q;
	B=pow(n,2./3);
	for(int i=1;i<=m;i++) cin>>v[i];
	for(int i=1;i<=n;i++) cin>>w[i];
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		eg[x].push_back(y), eg[y].push_back(x);
	}
	dfs(1,0);
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
	for(int i=1;i<=n;i++) cin>>col[i], now[i]=col[i];
	int t=1,tot=0;
	for(int i=1,op,x,y;i<=Q;i++) {
		cin>>op>>x>>y;
		if(!op) t++, opt[t].x=x, opt[t].y=y, opt[t].sp=now[x], now[x]=y;
		else {
			if(in[x]>in[y]) swap(x,y);
			q[++tot].x=x, q[tot].y=y, q[tot].t=t, q[tot].op=tot;
			int l=lca(x,y);
			if(l==x) q[tot].l=in[x], q[tot].r=in[y];
			else q[tot].l=ou[x], q[tot].r=in[y], q[tot].sp=l;
		}
	}
	sort(q+1,q+tot+1);
	int l=1,r=0; t=1;
	for(int i=1;i<=tot;i++) {
		while(l>q[i].l) upd(--l);
		while(r<q[i].r) upd(++r);
		while(l<q[i].l) upd(l++);
		while(r>q[i].r) upd(r--);
		while(t!=q[i].t) {                                                                                                                                                                                              
			if(t<q[i].t) t++;
			int x=opt[t].x, y=(t<=q[i].t)? opt[t].y:opt[t].sp, c=col[x];
			if(vis[x]) ans-=v[c]*w[cnt[c]], cnt[c]--;
			col[x]=c=y;
			if(vis[x]) cnt[c]++, ans+=v[c]*w[cnt[c]];
			if(t>q[i].t) t--;
		}
		if(q[i].sp) upd(in[q[i].sp]);
		Ans[q[i].op]=ans;
		if(q[i].sp) upd(in[q[i].sp]);
	}
	for(int i=1;i<=tot;i++) cout<<Ans[i]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
