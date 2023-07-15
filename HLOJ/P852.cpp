#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,v[N],fa[N],tot[N];
vector<int> g[N],nd;
int find(int x) {
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
bool cmp(int x,int y) { return v[x]<=v[y]; }
ll ans=0;
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>v[i], nd.push_back(i);
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y; x++, y++;
		g[x].push_back(y), g[y].push_back(x);
	}
	sort(nd.begin(),nd.end(),cmp);
	for(int i=1;i<=n;i++) fa[i]=i, tot[i]=1;
	ll ans=n;
	for(auto i:nd) {
		int f=find(i);
		for(auto to:g[i]) {
			int ft=find(to);
			if(ft!=f&&v[ft]<=v[f]) {
				fa[ft]=f;
				if(v[ft]==v[f]) ans+=1ll*tot[f]*tot[ft], tot[f]+=tot[ft];
			}
		}
	}
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T=1;
	while(T--) solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

