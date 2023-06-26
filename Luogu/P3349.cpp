#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
bool mem1;
const int N=20;
int n,m,eg[N][N];
vector<int> g[N];
ll f[N][N];
void dfs(int x,int from,int s) {
	for(auto y:g[x]) if(y!=from) dfs(y,x,s);
	for(int i=1;i<=n;i++) if((1<<(i-1))&s) {
		f[x][i]=1;
		for(auto y:g[x]) if(y!=from) {
			ll v=0;
			for(int j=1;j<=n;j++)
				if(eg[i][j]) v+=f[y][j];
			f[x][i]=f[x][i]*v;
		}
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y;
		eg[x][y]=eg[y][x]=1;
	}
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		g[x].push_back(y), g[y].push_back(x);
	}
	ll ans=0;
	for(int s=1;s<(1<<n);s++) {
		memset(f,0,sizeof(f));
		dfs(1,0,s);
		ll res=0, cnt=0;
		for(int i=1;i<=n;i++) if((1<<(i-1))&s) res+=f[1][i], cnt++;
		ans=ans+((n-cnt)%2==0? 1:-1)*res;
	}
	cout<<ans<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

