#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
ll n,a[N];
ll gcd(ll x,ll y) {
	if(!x) return y;
	return gcd(y%x,x);
}
struct node {
	ll r,g;
}b[N],nb[N];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	ll ans=0,m=0;
	for(int i=n;i>=1;i--) {
		for(int j=1;j<=m;j++) b[j].g=gcd(b[j].g,a[i]);
		b[++m]={i,a[i]};
		int p=0;
		for(int j=1;j<=m;j++) {
			if(j>1&&b[j].g==b[j-1].g) continue;
			nb[++p]=b[j];
		}
		m=p;
		for(int j=1;j<=m;j++) b[j]=nb[j], ans=max(ans,(b[j].r-i+1)*b[j].g);
	}
	cout<<ans<<endl;
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
