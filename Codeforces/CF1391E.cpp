#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n,m,fa[N],dep[N],vis[N];
vector<int> eg[N],g[N],nd[N];
void dfs(int x) {
	vis[x]=1, nd[dep[x]].push_back(x);
	for(auto y:eg[x]) if(!vis[y]) {
		g[x].push_back(y);
		dep[y]=dep[x]+1, fa[y]=x;
		dfs(y);
	}
}
void solve() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) eg[i].clear(), g[i].clear(), vis[i]=0, nd[i].clear();
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y;
		eg[x].push_back(y), eg[y].push_back(x);
	}
	dep[1]=1, dfs(1);
	for(int i=1;i<=n;i++) if(dep[i]>=(n+1)/2) {
		cout<<"PATH"<<endl<<dep[i]<<endl;
		while(i) {
			cout<<i<<" ";
			i=fa[i];
		}
		cout<<endl;
		return;
	}
	vector<PII> vc;
	for(int i=1;i<=n;i++) {
		for(int j=0;j+1<(int)nd[i].size();j+=2)
			vc.emplace_back(nd[i][j],nd[i][j+1]);
	}
	cout<<"PAIRING"<<endl<<vc.size()<<endl;
	for(auto i:vc) cout<<i.first<<" "<<i.second<<endl;
	return;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);

	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time "<<clo<<"MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}