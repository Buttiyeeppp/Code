#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using ull=unsigned long long;
using PII=pair<int,int>;
const int N=55;
bool mem1;
int n,m;
vector<int> g[N];
ull hs[N],mk,f[N];
ull calc(ull v) {
	v^=mk;
	v^=(v<<6), v^=(v>>7), v^=(v<<27);
	v^=mk;
	return v;
}
void dfs(int x) {
	hs[x]=1;
	for(auto y:g[x]) {
		dfs(y), hs[x]+=calc(hs[y]);
	}
}
void dfs1(int x) {
	for(auto y:g[x]) {
		f[y]=hs[y]+calc(f[x]-calc(hs[y]));
		dfs1(y);
	}
}
map<ull,int> mp;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>m;
	mt19937 rd(time(0));
	mk=rd();
	for(int q=1;q<=m;q++) {
		cin>>n;
		for(int i=0;i<=n;i++) g[i].clear();
		for(int i=1,x;i<=n;i++) cin>>x, g[x].push_back(i);
		int rt=g[0][0];
		dfs(rt);
		f[rt]=hs[rt], dfs1(rt);
		ull val=1;
		for(int i=1;i<=n;i++) val+=calc(f[i]);
		if(!mp[val]) mp[val]=q;
		cout<<mp[val]<<endl;
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

