#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
const int N=1e5+10;
const ll Mod=1000003;
const ll Mod2=1000037;
const ll P=1331;
int n,m,k,deg[N],vis[N],eg[Mod],eg2[Mod2];
vector<int> g[N];
struct Edge { int u,v; }edge[N];
void init() {
	for(int i=1;i<=n;i++) g[i].clear(), deg[i]=vis[i]=0;
	for(int i=1,u,v;i<=m;i++) {
		u=edge[i].u, v=edge[i].v;
		eg[(u*P+v)%Mod]=eg[(v*P+u)%Mod]=eg2[(u*P+v)%Mod2]=eg2[(v*P+u)%Mod2]=0;
	}
}
void solve() {
	cin>>n>>m>>k;
	for(int i=1,u,v;i<=m;i++) {
		cin>>u>>v;
		g[u].push_back(v), g[v].push_back(u);
		deg[u]++, deg[v]++;
		eg[(u*P+v)%Mod]=eg[(v*P+u)%Mod]=eg2[(u*P+v)%Mod2]=eg2[(v*P+u)%Mod2]=1;	
		edge[i]=(Edge){u,v};
	}
	queue<int> q;
	for(int i=1;i<=n;i++) if(deg[i]<k-1) q.push(i), vis[i]=1;
	while(q.size()) {
		int u=q.front(); q.pop();
		for(auto to:g[u])
			if(--deg[to]==k-2) q.push(to), vis[to]=1;
	}
	for(int i=1;i<=n;i++) if(deg[i]==k-1) q.push(i);
	while(q.size()) {
		int ok=1, u=q.front(); q.pop();
		vis[u]=1;
		vector<int> node;
        node.push_back(u);
        for(auto to:g[u]) if(!vis[to]) node.push_back(to);
		if(1ll*k*(k-1)/2>m||deg[u]<k-1) { ok=0; }
		else {
            // assert((int)node.size()==k);
    		for(auto to:node) if(to!=u) {
				for(auto now:node) if(now!=to&&(!eg[(to*P+now)%Mod]||!eg2[(to*P+now)%Mod2])) { ok=0; break; }
				if(!ok) break;
			}
		}
		if(ok) {
			cout<<"2\n";
			for(auto now:node) cout<<now<<" "; cout<<endl;
			init();
			return;
		}
		for(auto to:node) if(to!=u)
			if(--deg[to]==k-1) q.push(to);
	}
	vector<int> node;
	for(int i=1;i<=n;i++) if(!vis[i]) node.push_back(i);
	if(node.empty()) return cout<<"-1\n", init(), void();
	cout<<"1 "<<node.size()<<endl;
	for(auto now:node) cout<<now<<" "; cout<<endl;
	init();
	return;
}
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}