#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n;
struct option {
	ll a,h,k;
	bool operator<(const option &q)const {
		return h<q.h;
	}
}d[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>d[i].a>>d[i].h>>d[i].k;
	sort(d+1,d+n+1);
	ll x=0;
	for(int i=1;i<=n;i++) {
		ll y=(ll)min(x+(__int128)d[i].a*d[i].k,(__int128)d[i].h);
		x=max(x,y);
	}
	cout<<x<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
