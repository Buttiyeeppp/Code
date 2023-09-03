#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
ll n,d,p,f[N],s[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>d>>p;
	for(int i=1;i<=n;i++) cin>>f[i];
	sort(f+1,f+n+1);
	for(int i=1;i<=n;i++) s[i]=s[i-1]+f[i];
	ll ans=1e18;
	for(int i=0;i<=n;i++) {
		ans=min(ans,s[i]+((n-i+d-1)/d)*p);
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

