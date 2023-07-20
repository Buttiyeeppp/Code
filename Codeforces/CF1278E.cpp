#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#define xxzx
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n,R=2,l[N],r[N];
vector<int> g[N];
void dfs(int x,int from) {
	int cnt=1;
	R+=g[x].size(), r[x]=R;	
	for(auto y:g[x]) if(y!=from) {
		l[y]=r[x]-(cnt++);
		dfs(y,x);
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	cin>>n;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		g[x].push_back(y), g[y].push_back(x);
	}
	l[1]=1;
	dfs(1,0);
	for(int i=1;i<=n;i++) cout<<l[i]<<" "<<r[i]<<endl;

	#ifdef xxzx
	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}
