#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,vis[N],ind[N];
vector<int> g[N],eg[N];
void dfs(int x) {
	vis[x]=1;
	for(auto y:g[x]) {
		eg[y].push_back(x), ind[x]++;
		if(!vis[y]) dfs(y);
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,c;i<=n;i++) {
		cin>>c;
		for(int j=1,x;j<=c;j++) {
			cin>>x;
			g[i].push_back(x);
		}
	}
	dfs(1);
	queue<int> q;
	for(int i=1;i<=n;i++) if(vis[i]&&!ind[i]) q.push(i);
	vector<int> ans;
	while(q.size()) {
		int u=q.front(); q.pop();
		if(u!=1) ans.push_back(u);
		for(auto y:eg[u]) {
			ind[y]--;
			if(!ind[y]) q.push(y);
		}
	}
	for(auto now:ans) cout<<now<<" ";
	cout<<endl;
 	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

