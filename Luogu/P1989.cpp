#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const int M=1e3+10;
bool mem1;
int n,m,tot,id[N];
bitset<N> eg[M];
vector<int> g[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	int B=sqrt(n);
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y;
		g[x].push_back(y), g[y].push_back(x);
	}
	for(int i=1;i<=n;i++) {
		if(g[i].size()>B) {
			id[i]=++tot;
			for(auto to:g[i]) eg[tot][to]=1;
		}	
	}
	ll ans=0; bitset<N> now;
	for(int i=1;i<=n;i++) {
		for(auto y:g[i]) now[y]=1;
		for(auto y:g[i]) {
			if(g[y].size()>B) ans+=(eg[id[y]]&now).count();
			else {
				for(auto to:g[y]) if(now[to]) ans++;
			}
		}
		for(auto y:g[i]) now[y]=0;
	}
	cout<<ans/6<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	return 0;
}

