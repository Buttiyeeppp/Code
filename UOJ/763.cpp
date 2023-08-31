#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using ull=unsigned long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n;
vector<int> g[N];
ull hs[N],mk;
ull val(ull v) {
	v^=mk;
	v^=(v<<4), v^=(v>>7), v^=(v<<13);
	v^=mk;
	return v;
}
void dfs(int x,int from) {
	hs[x]=1;
	vector<int> nd;
	for(auto y:g[x]) if(y!=from) {
		dfs(y,x);
		hs[x]+=val(hs[y]);
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,x,y;i<n;i++)
		cin>>x>>y, g[x].push_back(y), g[y].push_back(x);
	mt19937 rd(time(0));
	mk=rd();
	dfs(1,0);
	sort(hs+1,hs+n+1);
	int ans=0;
	for(int i=1;i<=n;i++) ans+=(i==1||hs[i]!=hs[i-1]);
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

