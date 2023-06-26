#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PLI=pair<ll,int>;
const int N=1e6+10;
bool mem1;
int n,m,fa[N],a[N],dfn[N],mxdfn[N],tim,f[N],vis[N];
vector<int> g[N];
void dfs(int x) {
	dfn[x]=++tim;
	for(auto y:g[x]) dfs(y);
	mxdfn[x]=tim;
}
struct Query {
	int u,v,op;
	bool operator<(const Query &q)const {
		return v<q.v;
	}
}qr[N];
int find(int x) {
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void Merge(int x,int y) {
	int fx=find(x), fy=find(y);
	if(fx!=fy) fa[fx]=fy;
}
ll s[2][N],ans[N];
int lowbit(int x) { return x&-x; }
void Add(int op,int x,ll val) { if(x>0) for(int i=x;i<=n;i+=lowbit(i)) s[op][i]+=val; }
ll Qry(int op,int x) {
	if(x<=0) return 0;
	ll res=0;
	for(int i=x;i>0;i-=lowbit(i)) res+=s[op][i];
	return res;
}
ll Sum(int op,int x) { return Qry(op,mxdfn[x])-Qry(op,dfn[x]-1); }
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=2;i<=n;i++) cin>>f[i], g[f[i]].push_back(i);
	dfs(1);
	priority_queue<PLI,vector<PLI>,greater<PLI>> q;
	for(int i=1;i<=n;i++) {
		cin>>a[i], q.emplace(-a[i],i);
		Add(0,dfn[i],1), Add(0,dfn[f[i]],-1);
		Add(1,dfn[i],a[i]), Add(1,dfn[f[i]],-a[i]);
	}
	for(int i=1;i<=m;i++) cin>>qr[i].u>>qr[i].v, qr[i].op=i;
	sort(qr+1,qr+m+1);
	vis[1]=1;
	for(int i=1;i<=m;i++) {
		while(q.size()&&q.top().first<=qr[i].v) {
			int u=q.top().second; ll sum=Sum(1,u), sz=Sum(0,u); q.pop();
			if(vis[u]) continue; vis[u]=1;
			Merge(u,f[u]);
			int fd=find(u);
			Add(0,dfn[f[u]],sz), Add(0,dfn[f[fd]],-sz);
			Add(1,dfn[f[u]],sum), Add(1,dfn[f[fd]],-sum);
			if(!vis[fd]) q.emplace(ceil(-1.*Sum(1,fd)/Sum(0,fd)),fd);
		}
		ans[qr[i].op]=Sum(1,qr[i].u)+qr[i].v*Sum(0,qr[i].u);
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl; 
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

