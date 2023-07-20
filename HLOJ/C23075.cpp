#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=3e4+10;
bool mem1;
int n,m,t,w[N],vis[N];
vector<int> g[N],ng[N];
struct edge { int x,y; }eg[N];
bool mem2;
int main() {
//	freopen("ex_link.in","r",stdin);
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>t;
	for(int i=1;i<=m;i++) {
		int x,y;
		cin>>x>>y, g[x].push_back(y), g[y].push_back(x);
		eg[i]=edge{x,y};
	}
	for(int i=1;i<=m;i++) {
		int x=eg[i].x, y=eg[i].y;
		if(g[x].size()==g[y].size()) {
			if(x>y) swap(x,y);
			ng[x].push_back(y);
		}
		else {
			if(g[x].size()>g[y].size()) swap(x,y);
			ng[x].push_back(y);
		}
	}
	for(int i=1;i<=n;i++) cin>>w[i];
	ll ans=0,mx=-1;
	for(int i=1;i<=n;i++) {
		sort(g[i].begin(),g[i].end(),[](const int x,const int y){ return w[x]>w[y]; });
		ll a=0,b=0;
		for(auto to:g[i]) { a+=w[to], b+=w[to]*w[to]; }
		ans+=(a*a-b)/2;
		for(auto to:ng[i]) vis[to]=i;
		for(auto to:ng[i]) {
			for(auto tto:ng[to]) {
				if(vis[tto]==i) ans-=w[i]*w[tto]+w[i]*w[to]+w[to]*w[tto];
			}
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) {
		for(auto to:g[i]) vis[to]=i; vis[i]=i;
		for(auto to:g[i]) {
			for(auto tto:g[to]) {
				if(vis[tto]==i) continue;
				if(w[tto]*w[i]<=mx) break;
				if(w[tto]*w[i]>mx) { mx=w[tto]*w[i]; break; }
			}
		}
	}
	cout<<(t!=2? mx:0)<<endl;
	cout<<(t!=1? ans*2:0)<<endl;

	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

