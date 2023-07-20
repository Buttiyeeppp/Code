#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e4+10;
bool mem1;
int n,m,p[N],c[N],d,k[N];
int Ans[N],yep[N],match[N],vis[N],now;
vector<int> g[N];
void Add(int x,int y) { g[x].push_back(y); } 
bool dfs(int x) {
	for(auto y:g[x]) {
		if(vis[y]==now) continue;
		vis[y]=now;
		if(match[y]==-1||dfs(match[y]))
			return match[y]=x, true;
	}
	return false;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	cin>>d;
	for(int i=1;i<=d;i++) cin>>k[i], yep[k[i]]=1;
	for(int i=1;i<=n;i++) if(!yep[i]) g[p[i]].push_back(c[i]);
	int ans=0; now=1;
	memset(match,-1,sizeof(match));
	for(int i=d;i>=1;i--) {
		while(dfs(ans)) ans++, now++;
		now++, Ans[i]=ans;
		g[p[k[i]]].push_back(c[k[i]]);
	}
	for(int i=1;i<=d;i++) cout<<Ans[i]<<endl; 
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
