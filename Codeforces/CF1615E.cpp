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
int n,k,leaf,d[N],l[N],a[N],tot,fa[N];
vector<int> g[N];
void dfs(int x,int from) {
	d[x]=x, fa[x]=from, l[x]=1;
	if(from&&g[x].size()==1) leaf++;
	for(auto y:g[x]) if(y!=from) {
		dfs(y,x);
		if(d[x]==x||l[y]+1>l[x]) d[x]=d[y], l[x]=l[y]+1;
	}
	for(auto y:g[x]) if(y!=from) {
		if(d[x]!=d[y]) a[++tot]=l[y];
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>k;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		g[x].push_back(y), g[y].push_back(x);
	}
	dfs(1,0), a[++tot]=l[1];
	if(k>=leaf) {
		ll ans=-1e18;
		for(int i=leaf;i<=k;i++) ans=max(ans,1ll*i*(n-i));
		cout<<ans<<endl;
	}
	else {
		sort(a+1,a+tot+1,[](const int &x,const int &y){ return x>y; });
		int B=n;
		for(int i=1;i<=k;i++) B-=a[i];
		ll ans=1e18;
		for(int i=0;i<=B;i++) ans=min(ans,1ll*(n-k-i)*(k-i));
		cout<<ans<<endl;
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

