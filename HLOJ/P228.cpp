#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,k,f[N],sz[N];
vector<int> g[N];
void dfs(int x,int from) {
	sz[x]=1;
	int pd=0;
	for(auto y:g[x]) if(y!=from) {
		dfs(y,x);
		f[x]+=f[y], sz[x]+=sz[y], pd|=(sz[y]<f[y]*k);
	}
	if(!pd&&x!=1) f[x]++;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>k;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		g[x].push_back(y), g[y].push_back(x);
	}
	dfs(1,0);
	cout<<f[1]<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

