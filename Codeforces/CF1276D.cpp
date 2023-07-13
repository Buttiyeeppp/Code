#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const ll Mod=998244353;
const int N=2e5+10;
bool mem1;
int n;
ll f[N][4],s[N],t[N];
ll Add(ll x,ll y) {
	return (x+y>=Mod)? x+y-Mod:x+y;
}
vector<PII> g[N];
void dfs(int x,int from) {
	if(from&&g[x].size()==1) return f[x][0]=f[x][3]=1, void();
	vector<int> nd,bh;
	for(auto y:g[x]) if(y.second!=from)
		dfs(y.first,y.second), nd.push_back(y.first), bh.push_back(y.second);
	int sz=nd.size();
	s[0]=1;
	for(int i=1;i<=sz;i++)
		s[i]=s[i-1]*Add(f[nd[i-1]][0],f[nd[i-1]][1])%Mod;
	t[sz+1]=1;
	for(int i=sz;i>=1;i--)
		t[i]=t[i+1]*Add(f[nd[i-1]][1],Add(f[nd[i-1]][2],f[nd[i-1]][3]))%Mod;
	int p=0;
	while(p<sz&&bh[p]<from) {
		p++;
		ll ls=(p==1? 1:s[p-1]), rs=(p==sz? 1:t[p+1]);
		f[x][1]=Add(f[x][1],ls*rs%Mod*Add(f[nd[p-1]][2],f[nd[p-1]][3])%Mod);
	}
	ll ls=(p==0? 1:s[p]), rs=(p==sz? 1:t[p+1]);
	f[x][0]=ls*rs%Mod;
	while(p<sz) {
		p++;
		ll ls=(p==1? 1:s[p-1]), rs=(p==sz? 1:t[p+1]);
//		if(x==1) cout<<"Chk "<<p<<" "<<ls<<" "<<rs<<" "<<Add(f[nd[p-1]][2],f[nd[p-1]][3])<<endl;
		f[x][2]=Add(f[x][2],ls*rs%Mod*Add(f[nd[p-1]][2],f[nd[p-1]][3])%Mod);
	}
	f[x][3]=1;
	for(auto now:nd) f[x][3]=f[x][3]*Add(f[now][0],f[now][1])%Mod;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		g[x].emplace_back(y,i), g[y].emplace_back(x,i);
	}
	dfs(1,0);
//	for(int i=1;i<=n;i++)
//		for(int j=0;j<4;j++) cout<<"f "<<i<<" "<<j<<" "<<f[i][j]<<endl;
	cout<<Add(f[1][2],f[1][3])<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
