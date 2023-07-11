#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,s,dis[N],fa[N],u=1;
vector<PII> g[N];
void dfs1(int x) {
	if(dis[x]>dis[u]) u=x;
	for(auto y:g[x]) if(y.first!=fa[x]) {
		dis[y.first]=dis[x]+y.second;
		fa[y.first]=x;
		dfs1(y.first);
	}
}
int f[N],vis[N],mx;
void dfs2(int x) {
	vis[x]=1, mx=max(mx,f[x]);
	for(auto y:g[x]) if(!vis[y.first]) {
		f[y.first]=f[x]+y.second;
		dfs2(y.first);
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>s;
	for(int i=1,x,y,w;i<n;i++) {
		cin>>x>>y>>w;
		g[x].emplace_back(y,w), g[y].emplace_back(x,w);
	}
	dfs1(1);
	memset(fa,0,sizeof(fa)), dis[u]=0;
	int v=u; dfs1(u);
	vector<int> node;
	while(v!=u) node.push_back(u), u=fa[u];
	node.push_back(v);
	reverse(node.begin(),node.end());
//	for(auto now:node) cout<<now<<" "; cout<<endl;
//	for(auto now:node) cout<<dis[now]<<" "; cout<<endl;
	for(auto now:node) vis[now]=1;
	for(auto now:node) dfs2(now);
//	cout<<"Mx "<<mx<<endl;
	int p=0,ans=INT_MAX;
	for(int i=0;i<node.size();i++) {
		while(p+1<node.size()&&dis[node[p+1]]-dis[node[i]]<=s) p++;
//		cout<<node[i]<<" "<<node[p]<<" "<<dis[node[i]]<<" "<<dis[node.back()]-dis[node[p]]<<endl;
		ans=min(ans,max({mx,dis[node[i]],dis[node.back()]-dis[node[p]]}));
	}
	cout<<ans<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

