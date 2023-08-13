#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
const ll Mod=998244353;
bool mem1;
ll a[N],Catlan[N],fac[N],inv[N],n,k;
map<ll,int> mp;
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
	inv[N-1]=Pow(fac[N-1],Mod-2);
	for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll C(ll x,ll y) {
	if(x<y) return 0;
	return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
void solve() {
	cin>>n>>k;
	for(int i=1;i<=n;i++) a[i]=0;
	mt19937_64 rd(time(0));
	for(int i=1,l,r;i<=k;i++) {
		cin>>l>>r;
		ll v=rd();
		a[l]^=v, a[r+1]^=v;
	}
	mp.clear();
	a[1]^=(ll)rd();
	for(int i=1;i<=n;i++) a[i]^=a[i-1], mp[a[i]]++;
	ll ans=1;
	for(auto now:mp) {
		int v=now.second;
		if(v&1) ans=0;
		else ans=ans*Catlan[now.second/2]%Mod;
	}
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	init();
	for(int i=1;i<N/2;i++) Catlan[i]=(C(2*i,i)-C(2*i,i+1)+Mod)%Mod;
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

