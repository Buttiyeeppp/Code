#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const ll Mod=998244353;
const ll inv2=499122177;
const int N=1e5+10;
bool mem1;
int v[N],tot;
ll f[N],g[N],n;
unordered_map<int,int> mp;
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
ll sum(ll x,ll y) { return (2*x+y-1)*y%Mod*inv2%Mod; }
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int l=1;l<=n;l++) {
		int z=n/l;
		v[++tot]=z, l=n/z, mp[z]=tot;
	}
	f[tot]=g[tot]=1;
	for(int i=tot-1;i>=1;i--) {
		ll x=v[i];
		for(int l=2;l<=x;l++) {
			ll z=x/l, r=x/z, j=mp[z];
			ll c=(l+r)*(r-l+1)%Mod*inv2%Mod;
			f[i]=(f[i]+c*f[j])%Mod, g[i]=(g[i]+c*g[j])%Mod;
			l=r;
		}
		g[i]=(g[i]*Pow(x-1,Mod-2)+1)%Mod;
		f[i]=(f[i]*Pow(x-1,Mod-2)+g[i])%Mod;
	}
	cout<<f[1]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
