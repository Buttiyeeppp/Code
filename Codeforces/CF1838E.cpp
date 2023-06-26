#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e9+7;
const int N=2e5+10;
bool mem1;
int n,m,k;
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
void solve() {
	cin>>n>>m>>k;
	for(int i=1,x;i<=n;i++) cin>>x;
	ll ans=Pow(k,m), C=1;
	for(int i=0;i<n;i++) ans=(ans-C*Pow(k-1,m-i)%Mod+Mod)%Mod, C=C*(m-i)%Mod*Pow(i+1,Mod-2)%Mod;
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

