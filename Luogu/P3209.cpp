#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e4+10;
bool mem1;
int n,m,w[N],pos[N];
struct Edge {
	int u,v;
	bool operator<(const Edge &x)const {
		return (pos[u]==pos[x.u]? pos[v]<pos[x.v]:pos[u]<pos[x.u]);
	}
}eg[N];
int fa[N<<1];
int find(int x) {
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y) {
	int fx=find(x), fy=find(y);
	if(fx!=fy) fa[fx]=fy;
}
void solve() {
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>eg[i].u>>eg[i].v;
	for(int i=1;i<=n;i++) cin>>w[i], pos[w[i]]=i;
	for(int i=1;i<=(m<<1);i++) fa[i]=i;
	for(int i=1;i<=m;i++) if(pos[eg[i].u]>pos[eg[i].v]) swap(eg[i].u,eg[i].v);
	for(int i=1;i<=m;i++) {
		for(int j=1;j<=m;j++) {
			if(pos[eg[i].u]<pos[eg[j].u]&&pos[eg[i].v]<pos[eg[j].v]&&pos[eg[i].v]>pos[eg[j].u]) {
				merge(i,j+m), merge(i+m,j);
			}
		}
	}
	for(int i=1;i<=m;i++)
		if(find(i)==find(i+m)) return cout<<"NO"<<endl, void();
	cout<<"YES"<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

