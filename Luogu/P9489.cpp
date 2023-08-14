#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define xxzx
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=30;
bool mem1;
int n,l,r,x[N];
int gcd(int x,int y) {
	if(x==0) return y;
	return gcd(y%x,x);
}
int calc(int m) {
	ll l=0,r=1e18+1;
	while(l+1<r) {
		ll mid=(l+r)>>1,v=0;
		for(int i=1;i<=n;i++) v+=mid/x[i];
		if(v<=m) l=mid;
		else r=mid;
	}
	ll ans=0;
	for(int s=1;s<(1<<n);s++) {
		ll v=1,tot=0,pd=1;
		for(int i=1;i<=n;i++) if((1<<(i-1))&s) {
			if((__int128)v/gcd(v,x[i])*x[i]>(__int128)l) { pd=0; break; }
			v=v/gcd(v,x[i])*x[i], tot++;
			if(v>l) break;
		}
		if(!pd) continue;
		ans+=((tot%2==1)? 1:-1)*(l/v);
	}
	return ans;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++) cin>>x[i];
	cout<<calc(r)-calc(l-1)<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

