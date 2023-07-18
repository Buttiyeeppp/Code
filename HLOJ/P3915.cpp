#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,s,fa[N],sz[N],vis[N];
struct edge {
	int x,y,z;
}eg[N];
int find(int x) {
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
bool check(int l,int r) {
	vector<edge> g;
	for(int i=l;i<=r;i++) g.push_back(eg[i]);
	sort(g.begin(),g.end(),[](const edge q,const edge p){ return q.z<p.z;});
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1,vis[i]=0;
	ll res=0,gs=0;
	for(auto now:g) {
		int fx=find(now.x), fy=find(now.y);
		if(fx!=fy) {
			if(sz[fx]>sz[fy]) swap(fx,fy);
			sz[fy]+=sz[fx], fa[fx]=fy, res+=now.z;
		}
	}
	for(int i=1;i<=n;i++) if(!vis[find(i)]) gs++, vis[fa[i]]=1;
	return (res<=s&&gs==1);
}
void solve() {
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++) cin>>eg[i].x>>eg[i].y>>eg[i].z;
	int i=1,ans=0;
	while(i+n-2<=m) {
		int l,r=i,d=1;
		while(d<m-i&&!check(i,r+d)) l=r+d,d=min(d<<1,m-i);
		if(r+d==m&&!check(i,r+d)) break;
		r=r+d+1;
		while(l+1<r) {
			int mid=(l+r)>>1;
			if(check(i,mid)) r=mid;
			else l=mid;
		}
		ans++,i=r+1;
	}
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	int T; cin>>T;
	while(T--) solve();

	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
