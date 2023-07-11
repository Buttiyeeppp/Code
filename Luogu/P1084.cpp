#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,fa[N][20],dep[N],top[N];
ll w[N][20],d[N];
vector<PII> g[N];
void dfs(int x,int from) {
	for(auto y:g[x]) if(y.first!=from) {
		top[y.first]=(x!=1)? top[x]:y.first;
		d[y.first]=d[x]+y.second;
		fa[y.first][0]=x, w[y.first][0]=y.second;
		dfs(y.first,x);
	}
}
int dfn[N],mxdfn[N],tim;
void dfs1(int x) {
	if(g[x].size()==1&&x!=1) return dfn[x]=mxdfn[x]=++tim, void();
	dfn[x]=INT_MAX, mxdfn[x]=INT_MIN;
	for(auto y:g[x]) if(y.first!=fa[x][0])
		dfs1(y.first), dfn[x]=min(dfn[x],dfn[y.first]), mxdfn[x]=max(mxdfn[x],mxdfn[y.first]);
}
bool cmp(ll x,ll y) { return x>y; }
int m,p[N],s[N],pos[N],pre[N],vis[N];
bool check(ll t) {
	memset(vis,0,sizeof(vis));
	memset(pos,0,sizeof(pos));
	memset(s,0,sizeof(s));
	for(int i=1;i<=m;i++) {
		int u=p[i];
		if(d[u]<=t) {
			if(d[u]+w[top[u]][0]>t&&(!pos[top[u]]||d[u]>d[p[pos[top[u]]]])) 
				pos[top[u]]=i;
		}
		else {
			for(ll c=t,j=19;j>=0;j--)
				if(fa[u][j]&&c>=w[u][j]) c-=w[u][j], u=fa[u][j];
			s[dfn[u]]++, s[mxdfn[u]+1]--;
		}
	}
	for(int i=1;i<=tim;i++) {
		s[i]+=s[i-1];
		if(s[i]>0) {
			if(i>1&&s[i-1]>0) pre[i]=pre[i-1];
			else pre[i]=i;
		}
		else pre[i]=i+1;
	}
	vector<ll> val1,val2;
	for(auto to:g[1]) {
		if(pre[mxdfn[to.first]]<=dfn[to.first]) continue;
		if(pos[to.first]) vis[pos[to.first]]=1;
		else val1.push_back(w[to.first][0]);
	}
	for(int i=1;i<=m;i++) if(!vis[i]) {
		int u=p[i];
		if(d[u]<=t) val2.push_back(t-d[u]);
	}
	sort(val1.begin(),val1.end(),cmp), sort(val2.begin(),val2.end(),cmp);
	if(val2.size()<val1.size()) return false;
	for(int i=0,j=0;i<val1.size();i++,j++)
		if(val1[i]>val2[j]) return false;
	return true;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,x,y,w;i<n;i++) {
		cin>>x>>y>>w;
		g[x].emplace_back(y,w), g[y].emplace_back(x,w);
	}
	dfs(1,0);
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++)
			fa[i][j]=fa[fa[i][j-1]][j-1], w[i][j]=w[i][j-1]+w[fa[i][j-1]][j-1];
	dfs1(1);
	cin>>m;
	for(int i=1;i<=m;i++) cin>>p[i];
	ll l=-1, r=6e13;
	while(l+1<r) {
		ll mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid;
	}
	cout<<(r==6e13? -1:r)<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

