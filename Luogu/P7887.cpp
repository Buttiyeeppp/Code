#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const ll Mod=1e9+7;
bool mem1;
ll n,x[N],y[N],z[N],b[N],fac[N],inv[N],s[N];
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
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i]>>z[i], b[i]=y[i];
	b[n]=(x[n]+y[n])%Mod;
	for(int i=1;i<n;i++) {
		ll k=y[i+1]*Pow(x[i],Mod-2)%Mod;
		b[i+1]=(b[i+1]+b[i]*k)%Mod, z[i+1]=(z[i+1]+z[i]*k)%Mod;
	}
	s[n]=z[n]*Pow(b[n],Mod-2)%Mod;
	if(!b[n]&&!z[n]) return cout<<Mod<<endl, void();
	if(!b[n]&&z[n]) return cout<<0<<endl, void();
	for(int i=1;i<n;i++) {
		z[i]=(z[i]-b[i]*s[n]%Mod+Mod)%Mod, s[i]=z[i]*Pow(x[i],Mod-2)%Mod;
		if(!b[i]&&!z[i]) return cout<<Mod<<endl, void();
		if(!b[i]&&z[i]) return cout<<0<<endl, void();
	}
	cout<<1<<endl;
	for(int i=1;i<=n;i++) cout<<(s[i]-s[i-1]+Mod)%Mod<<" ";
	cout<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
