#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
ll n,k;
int sz[N],p[N],dep[N],w[N];
vector<int> eg[N],nd;
void dfs(int x,int from) {
	sz[x]=1, dep[x]=dep[from]+1;
	for(auto y:eg[x]) if(y!=from) {
		dfs(y,x), sz[x]+=sz[y];
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);

	cin>>n>>k;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		eg[x].push_back(y), eg[y].push_back(x);
	}
	dfs(1,0);
	// for(int i=1;i<=n;i++) cerr<<sz[i]<<" ";
	// cerr<<endl;
	for(int i=1;i<=n;i++) w[i]=-dep[i], p[i]=i;
	sort(p+1,p+n+1,[](const int &x,const int &y){ return sz[x]>sz[y]; });
	k-=n;
	for(int i=1;i<=n;i++) if(p[i]!=1&&k>=sz[p[i]]) k-=sz[p[i]], w[p[i]]=dep[p[i]];
	if(k!=0) return cout<<"No"<<endl, 0;
	sort(p+1,p+n+1,[](const int &x,const int &y){ return w[x]<w[y]; });
	for(int i=1;i<=n;i++) w[p[i]]=i;
	cout<<"Yes"<<endl;
	for(int i=1;i<=n;i++) cout<<w[i]<<" ";
	cout<<endl;

	#ifdef xxzx
	cerr<<"Time: "<<clo<<"MS"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}