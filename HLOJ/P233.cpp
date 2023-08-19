#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e3+10;
const ll INF=1e15;
bool mem1;
int n,b,s,m,dis[N],dis2[N],vis[N];
ll v[N],v2[N],f[N][N];
vector<PII> eg[N],eg2[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>b>>s>>m;
	for(int i=1,x,y,z;i<=m;i++) {
		cin>>x>>y>>z;
		eg[x].emplace_back(y,z), eg2[y].emplace_back(x,z);
	}
	priority_queue<PII,vector<PII>,greater<PII>> q;
	memset(dis,0x3f,sizeof(dis));
	q.emplace(0,b+1), dis[b+1]=0;
	while(q.size()) {
		int u=q.top().second; q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto to:eg[u]) {
			if(dis[to.first]>dis[u]+to.second)
				dis[to.first]=dis[u]+to.second, q.emplace(dis[to.first],to.first);
		}
	}
	memset(dis2,0x3f,sizeof(dis2)), memset(vis,0,sizeof(vis));
	q.emplace(0,b+1), dis2[b+1]=0;
	while(q.size()) {
		int u=q.top().second; q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto to:eg2[u]) {
			if(dis2[to.first]>dis2[u]+to.second)
				dis2[to.first]=dis2[u]+to.second, q.emplace(dis2[to.first],to.first);
		}
	}
	for(int i=1;i<=b;i++) dis[i]+=dis2[i];
	sort(dis+1,dis+b+1);
	for(int i=1;i<=b;i++) v[i]=v[i-1]+dis[i];
	memset(f,0x3f,sizeof(f)); f[0][0]=0;
	for(int i=1;i<=s;i++) {
		int k=0;	
		for(int j=1;j<=b;j++) {
			if(n<=500) {
				for(int k=0;k<j;k++) f[i][j]=min(f[i][j],f[i-1][k]+(v[j]-v[k])*(j-k-1));
			}
			else {
				while(i!=1&&k+1<j&&f[i-1][k]+(v[j]-v[k])*(j-k-1)>f[i-1][k+1]+(v[j]-v[k+1])*(j-k-2)) k++;
				f[i][j]=min(f[i][j],f[i-1][k]+(v[j]-v[k])*(j-k-1));
			}
		}
	}
	cout<<f[s][b]<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

