#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const ll Mod=998244353;
bool mem1;
int n,a[N];
ll fac[N],inv[N],pre[N],suf[N];
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
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i], pre[i]=pre[i-1]+a[i];
	suf[n+1]=0;
	for(int i=n;i>=1;i--) suf[i]=suf[i+1]+a[i];
	ll ans=1;
	for(int l=1,r=n;l<=r;) {
		while(suf[r]<pre[l]&&r>l) r--;
		if(pre[l]!=suf[r]) { l++; continue; }
		int x=l,y=r;
		while(pre[x+1]==pre[l]&&x<y) x++;
		while(suf[y-1]==suf[r]&&x<y) y--;
		if(x==y) ans=ans*Pow(2,r-l)%Mod;
		else {
			int l1=x-l+1,l2=r-y+1; ll sum=0;
			for(int j=0;j<=min(l1,l2);j++) sum=(sum+C(l1,j)*C(l2,j))%Mod;
			ans=ans*sum%Mod;
		}
		l=x+1,r=y-1;
	}
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	init();
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
