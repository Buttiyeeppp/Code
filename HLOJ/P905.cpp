#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,c,cnt[N],vis[N];
struct node {
	int x,b;
}a[N];
vector<int> pos[N];
vector<PII> ans;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>c;
	for(int i=1;i<=m;i++) cin>>a[i].x>>a[i].b, pos[a[i].b].push_back(i);
	priority_queue<PII> q;
	a[0].x=0, a[m+1].x=n+1;
	for(int i=1;i<=m;i++) {
		cnt[a[i].b]+=a[i+1].x-a[i].x;
		if(a[i-1].b!=a[i].b) cnt[a[i].b]+=a[i].x-a[i-1].x-1;
	}
	for(int i=1;i<=c;i++) q.emplace(cnt[i],i);
	vis[0]=1;
	while(q.size()) {
		PII now=q.top(); q.pop();
		int u=now.second;
		if(now.first!=cnt[u]||vis[u]) continue;
		vis[u]=1, ans.emplace_back(cnt[u],u);
		for(auto now:pos[u]) {
			if(!vis[a[now+1].b]) cnt[a[now+1].b]-=a[now+1].x-a[now].x-1, q.emplace(cnt[a[now+1].b],a[now+1].b);
			if(!vis[a[now-1].b]) cnt[a[now-1].b]-=a[now].x-a[now-1].x-1, q.emplace(cnt[a[now-1].b],a[now-1].b);
		}
	}
	for(auto now:ans) cout<<now.first<<" "<<now.second<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

