#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
const int M=1e3+10;
bool mem1;
int n,a[M],X[N],tot;
vector<int> g[N];
int vis[M],match[M];
bool dfs(int x) {
	for(auto y:g[x]) {
		if(vis[y]) continue;
		vis[y]=1;
		if(!match[y]||dfs(match[y]))
			return match[y]=x, true;
	}
	return false;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		for(int j=1;j<=n;j++) X[++tot]=a[i]*j;
	}
	sort(X+1,X+tot+1); tot=unique(X+1,X+tot+1)-X-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) {
			int u=lower_bound(X+1,X+tot+1,a[i]*j)-X;
			g[u].push_back(i);
		}
	ll ans=0,cnt=0;
	for(int i=1;i<=tot;i++) {
		if(dfs(i)) {
			memset(vis,0,sizeof(vis));
			ans+=X[i], cnt++;
		}
		if(cnt==n) break;
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}

