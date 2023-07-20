#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define xxzx
#ifdef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,a[N],col[N],s[N],tot,cnt,sum[3];
int yep[N],vis[N],pd,Yep;
vector<int> g[N],ng[N];
struct edge { int x,y; }eg[N];
void dfs(int x) {
	col[x]=cnt, s[cnt]+=a[x];
	for(auto y:g[x]) if(!col[y]) dfs(y);
}
void dfs2(int x) {
	sum[vis[x]]+=s[x];
	if(yep[x]) Yep=1;
	for(auto y:ng[x]) {
		if(vis[y]&&vis[y]==vis[x]) pd=0;
		else if(!vis[y]) vis[y]=(vis[x]==1? 2:1), dfs2(y);
	}
}
void init() {
	memset(s,0,sizeof(s));
	memset(col,0,sizeof(col));
	memset(yep,0,sizeof(yep));
	memset(vis,0,sizeof(vis));
	tot=cnt=0;
	for(int i=1;i<=n;i++) g[i].clear(), ng[i].clear();
}
void solve() {
	cin>>n>>m;
	init();
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,x;i<=n;i++) cin>>x, a[i]-=x;
	for(int i=1,op,x,y;i<=m;i++) {
		cin>>op>>x>>y;
		if(op==1) eg[++tot]=edge{x,y};
		else g[x].push_back(y), g[y].push_back(x);
	}
	for(int i=1;i<=n;i++) if(!col[i]) ++cnt, dfs(i);
	for(int i=1;i<=tot;i++) {
		int x=col[eg[i].x], y=col[eg[i].y];
		if(x!=y) ng[x].push_back(y), ng[y].push_back(x);
		else yep[x]=1;
	}
	for(int i=1;i<=cnt;i++) if(!vis[i]) {
		sum[1]=sum[2]=Yep=0,vis[i]=pd=1,dfs2(i);
		if(!pd&&abs(sum[1]+sum[2])%2) return cout<<"NO"<<endl, void();
		if(pd)
			if((Yep&&abs(sum[1]-sum[2])%2)||(!Yep&&sum[1]!=sum[2]) ) return cout<<"NO"<<endl, void();
	}
	cout<<"YES"<<endl;
}
bool mem2;
int main() {
	#ifdef xxzx
	ios::sync_with_stdio(false), cin.tie(0);
	#endif
	
	int T; cin>>T;
	while(T--) solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
