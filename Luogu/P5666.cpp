#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=6e5+10;
bool mem1;
int n,sz[N],mx1[N],mx2[N];
vector<int> g[N];
void dfs(int x,int from) {
	sz[x]=1;
	for(auto y:g[x]) if(y!=from) {
		dfs(y,x);
		sz[x]+=sz[y];
		if(!mx1[x]||sz[y]>sz[mx1[x]]) mx2[x]=mx1[x] ,mx1[x]=y;
		else if(!mx2[x]||sz[y]>sz[mx2[x]]) mx2[x]=y;
	}
}
int s[N],rt;
int lowbit(int x) { return x&-x; }
ll Query(int x) {
	if(x<0) return 0;
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=s[i];
	return res;
}
ll Sum(int l,int r) { return (l<=r)? Query(r)-Query(l-1):0; }
void Add(int x,int val) {
	for(int i=x;i<=n;i+=lowbit(i)) s[i]+=val;
}
ll ans;
void dfs1(int x,int from) {
	if(x!=rt) {
		Add(sz[x],-1), Add(n-sz[x],1);
		ans+=x*Sum(n-2*sz[x],n-2*sz[mx1[x]]);
	}
	for(auto y:g[x]) if(y!=from) dfs1(y,x);
	if(x!=rt) Add(sz[x],1), Add(n-sz[x],-1);
}
void dfs2(int x,int from) {
	if(x==mx1[rt]) ans-=rt*Query(n-2*sz[mx2[rt]]);
	else if(from==rt) ans-=rt*Query(n-2*sz[mx1[rt]]);
//	if(x==mx1[rt]) cout<<"A "<<x<<" "<<Query(n-2*sz[mx2[rt]])<<endl;
//	else if(from==rt) cout<<"A "<<x<<" "<<Query(n-2*sz[mx1[rt]])<<endl;
	Add(sz[x],1);
	if(x!=rt) ans+=x*Sum(n-2*sz[x],n-2*sz[mx1[x]]);
	
	for(auto y:g[x]) if(y!=from) dfs2(y,x);
	
	if(x!=rt) ans-=x*Sum(n-2*sz[x],n-2*sz[mx1[x]]);
	if(x==mx1[rt]) ans+=rt*Query(n-2*sz[mx2[rt]]);
	else if(from==rt) ans+=rt*Query(n-2*sz[mx1[rt]]);
//	if(x==mx1[rt]) cout<<"B "<<x<<" "<<Query(n-2*sz[mx2[rt]])<<endl;
//	else if(from==rt) cout<<"B "<<x<<" "<<Query(n-2*sz[mx1[rt]])<<endl;
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) g[i].clear();
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		g[x].push_back(y), g[y].push_back(x);
	}
	memset(mx1,0,sizeof(mx1)), memset(mx2,0,sizeof(mx2)), dfs(1,0);
	for(int i=1;i<=n;i++) if(2*sz[mx1[i]]<=n&&2*(n-sz[i])<=n) rt=i;
	memset(mx1,0,sizeof(mx1)), memset(mx2,0,sizeof(mx2)), dfs(rt,0);
	memset(s,0,sizeof(s)), ans=0;
	for(int i=1;i<=n;i++) if(i!=rt) Add(sz[i],1);
	dfs1(rt,0);
	for(int i=1;i<=n;i++) if(i!=rt) Add(sz[i],-1);
	dfs2(rt,0);
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
