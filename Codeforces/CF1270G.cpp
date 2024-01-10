#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,a[N],ind[N],vis[N];
void dfs(int x) {
	vis[x]=1;
	int y=x-a[x];
	ind[y]++;
	if(!vis[y]) dfs(y);
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) vis[i]=ind[i]=0;
	for(int i=1;i<=n;i++) cin>>a[i];
	dfs(1);
	queue<int> q;
	for(int i=1;i<=n;i++) if(vis[i]&&!ind[i]) q.push(i);
	while(q.size()) {
		int x=q.front(); q.pop();
		vis[x]=0;
		int y=x-a[x];
		ind[y]--;
		if(!ind[y]) q.push(y);
	}
	int sum=0;
	for(int i=1;i<=n;i++) if(vis[i]) sum++;
	cout<<sum<<endl;
	for(int i=1;i<=n;i++) if(vis[i]) cout<<i<<" ";
	cout<<endl;
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