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
int n,a[N];
ll ans[N];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	multiset<int> s;
	for(int i=1;i<=n;i++) s.insert(a[i]);
	ll res=0,l=0;
	for(auto it=s.begin();it!=s.end();it=s.upper_bound(l))
		l++, res+=(*it)-l, s.erase(it);
	for(int i=n;i>=1;i--) {
		ans[i]=res, res-=a[i];
		auto it=s.lower_bound(a[i]);
		if(it==s.end()) res+=l--;
		else res+=(*it), s.erase(it);
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
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

