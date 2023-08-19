#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
void solve() {
	ll a,b;
	cin>>a>>b;
	if(a==b) return cout<<0<<" "<<0<<endl, void();
	if(a<b) swap(a,b);
	ll v=a-b,ans=b;
	ll x=(a/v)*v, y=(b/v)*v;
	if(a-x==b-y) ans=min(ans,a-x);
	x+=v, y+=v;
	if(x-a==y-b) ans=min(ans,x-a);
	cout<<v<<" "<<ans<<endl;
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

