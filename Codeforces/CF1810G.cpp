#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e9+7;
const int N=5e3+10;
bool mem1;
ll n,g[N][N],p[N];
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		ll x,y; cin>>x>>y;
		p[i]=x*Pow(y,Mod-2)%Mod;
	}
	for(int i=0;i<=n+2;i++)
		for(int j=0;j<=n+2;j++) g[i][j]=0;
	for(int i=0;i<=n;i++) cin>>g[0][i];
	for(int i=1;i<=n;i++)
		for(int j=0;j<=n;j++) g[i][j]=(p[i]*g[i-1][j+1]+(1-p[i]+Mod)*g[i-1][max(j-1,0)])%Mod;
	for(int i=1;i<=n;i++) cout<<g[i][0]<<" ";
	cout<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	int T; cin>>T;
	while(T--) solve();

	#ifdef xxzx
	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}
