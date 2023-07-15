#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const ll Mod=998244353;
bool mem1;
void solve() {
	ll ans=0,n;
	cin>>n;
	for(ll i=1;i<=1000000;i++) {
		ll l=i-1, r=n+1;
		while(l+1<r) {
			ll mid=(l+r)>>1;
			if(2*i*mid-i*i<=n) l=mid;
			else r=mid;
		}
//		cout<<i<<" "<<l-i+1<<" "<<l<<endl;
		ans=(ans+l-i+1)%Mod;
	}
	cout<<ans<<endl;
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

