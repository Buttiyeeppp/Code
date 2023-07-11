#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,dfn[N],mxdfn[N],tim,ans;
vector<int> g1[N],g2[N];
void dfs2(int x) {
	dfn[x]=++tim;
	for(auto y:g2[x]) dfs2(y);
	mxdfn[x]=tim;
}
set<PII> s;
int m[N];
PII mem[N];
void add(int id,PII now) {
	PII x=*(--s.upper_bound(now));
	if(x.first<=now.first&&x.second>=now.second) {
		s.erase(x), s.insert(now);
		mem[id]=x, m[id]=1;
		return;
	}
	x=*s.upper_bound(now);
	if(!(now.first<=x.first&&now.second>=x.second)) s.insert(now), m[id]=1;
}
void dfs1(int x) {
	add(x,make_pair(dfn[x],mxdfn[x]));
	for(auto y:g1[x]) dfs1(y); 
	if(g1[x].empty()) ans=max(ans,(int)s.size()-2);
	
	if(m[x]) s.erase(make_pair(dfn[x],mxdfn[x]));
	if(mem[x].first!=0) s.insert(make_pair(mem[x].first,mem[x].second));
	m[x]=0, mem[x]=make_pair(0,0);
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) g1[i].clear(), g2[i].clear();
	for(int i=2,x;i<=n;i++) cin>>x, g1[x].push_back(i);
	for(int i=2,x;i<=n;i++) cin>>x, g2[x].push_back(i);
	tim=0, ans=0;
	s.clear(); s.insert(make_pair(0,0)), s.insert(make_pair(n+1,n+1));
	dfs2(1), dfs1(1);
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

