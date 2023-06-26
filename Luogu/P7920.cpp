#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=5e3+10;
bool mem1;
int n,ind[N],sz[N];
vector<int> ans[N<<1],g[N],out,nd[N];
bool cmp(int x,int y) {
	if(sz[x]!=sz[y]) return (sz[x]<sz[y]);
	return (ans[x]>ans[y]);
}
void calc(int x,int from) {
	sz[x]=1;
	for(auto y:g[x]) if(y!=from) {
		calc(y,x);
		sz[x]+=sz[y];
		nd[x].push_back(y);
	}
	sort(nd[x].begin(),nd[x].end(),cmp);
	ans[x].push_back(1);
	int mx=sz[x];
	for(auto now:nd[x]) {
		for(int i=0;i<sz[now];i++)
			ans[x].push_back(ans[now][i]+mx-sz[now]);
		mx-=sz[now];
	}
}
void dfs(int x,int from) {
	if(from) {
		int mx=n-sz[x];
		ans[x+n].push_back(1); sz[x+n]=n-sz[x];
		for(auto now:nd[from]) if(now!=x) {
			for(int i=0;i<sz[now];i++)
				ans[x+n].push_back(ans[now][i]+mx-sz[now]);
			mx-=sz[now];
		}
		nd[x].push_back(x+n);
		sort(nd[x].begin(),nd[x].end(),cmp);
		vector<int> nans;
		mx=n; nans.push_back(1);
		for(auto now:nd[x]) {
			for(int i=0;i<sz[now];i++)
				nans.push_back(ans[now][i]+mx-sz[now]);
			mx-=sz[now];
		}
		if(nans>out) out=nans;
	}
	for(auto y:g[x]) 
		if(y!=from) dfs(y,x);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	cin>>n;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		ind[x]++, ind[y]++;
		g[x].push_back(y), g[y].push_back(x);
	}
	calc(1,0); out=ans[1];
	dfs(1,0);
	for(int i=0;i<n;i++) cout<<out[i]<<" "; cout<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
