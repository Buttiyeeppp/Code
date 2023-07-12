#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,q,deg[N],yep[N],chain[N],cnt[N],vis[N];
ll len[N];
struct Edge {
	int u,v;
};
vector<Edge> eg[N];
vector<int> g[N];
int fa[N][20],dep[N];
void dfs(int x,int from) {
	for(auto y:g[x]) if(y!=from) {
		fa[y][0]=x, dep[y]=dep[x]+1;
		dfs(y,x);
	}
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
multiset<ll> ans,val[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>q;
	for(int i=1,u,v,w,c;i<n;i++) {
		cin>>u>>v>>w>>c;
		eg[c].push_back({u,v});
		g[u].push_back(v), g[v].push_back(u);
		len[c]+=w;
	}
	dfs(1,0);
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
	for(int i=1;i<=n;i++) {
		int cnt1=0,cnt2=0,oth=0,a,b;
		set<int> nd;
		for(auto now:eg[i])
			deg[now.u]=deg[now.v]=0, nd.insert(now.u), nd.insert(now.v);
		for(auto now:eg[i]) deg[now.u]++, deg[now.v]++;
		for(auto now:nd) {
			if(deg[now]==1) {
				cnt1++;
				if(cnt1==1) a=now;
				if(cnt1==2) b=now;
			}
			else if(deg[now]==2) cnt2++;
			else oth=1;
		}
		if(!oth&&cnt1==2&&cnt2==(int)nd.size()-2) {
			int l=lca(a,b);
			yep[i]=l, val[l].insert(-len[i]);
			for(auto now:nd) if(now!=l) chain[now]=i;
			cnt[i]=eg[i].size();
		}	
	}
	for(int i=1;i<=n;i++) {
		vis[i]=1;
		if(val[i].size()) ans.insert(*val[i].begin());
	}
	int op,x; ans.insert(0);
	while(q--) {
		cin>>op>>x;
		int ch=chain[x]; vis[x]^=1;
		if(!op) {
			if(ch) {
				if(cnt[ch]==(int)eg[ch].size()) {
					int pd=0;
					if(vis[yep[ch]]&&*val[yep[ch]].begin()==-len[ch]) ans.erase(-len[ch]), pd=1;
					val[yep[ch]].erase(-len[ch]);
					if(pd&&val[yep[ch]].size()) ans.insert(*val[yep[ch]].begin()); 
				}
				cnt[ch]--;
			}
			if(val[x].size()) ans.erase(*val[x].begin());
		}
		else {
			if(ch) {
				cnt[ch]++;
				if(cnt[ch]==(int)eg[ch].size()) {
					if(vis[yep[ch]]) {
						if(val[yep[ch]].empty()) ans.insert(-len[ch]);
						else if(-len[ch]<*val[yep[ch]].begin()) ans.erase(*val[yep[ch]].begin()), ans.insert(-len[ch]);
					}
					val[yep[ch]].insert(-len[ch]);
				}
			}
			if(val[x].size()) ans.insert(*val[x].begin());
		}
		cout<<-*ans.begin()<<endl;
	}
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
