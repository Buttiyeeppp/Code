#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e9+7;
const int N=1e3+10;
bool mem1;
ll n,m,f[N][N],g[N][N];
void solve() {
	cin>>n>>m;
	g[0][0]=1;
	for(int k=1;k<=n;k++) {
		for(int i=1;i<=m;i++) {
			for(int j=0;j+k<=n;j++) {
				if(g[i-1][j])
					f[i][j+k]=(f[i][j+k]+f[i-1][j]+1ll*k*k*g[i-1][j]%Mod)%Mod, g[i][j+k]=(g[i][j+k]+g[i-1][j])%Mod;
			}
		}
	}
	cout<<f[m][n]<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T=1;
	while(T--) solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

