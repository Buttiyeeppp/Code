#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e4+10;
const ll INF=(1ll<<61)-1;
bool mem1;
ll n,a[N],l[N],r[N];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i], a[i]^=a[i-1], l[i]=r[i]=0;
	for(int len=n;len>=1;len--)
		for(int i=1;i+len-1<=n;i++) {
			ll j=i+len-1, v=a[j]^a[i-1], yep=(len==n);
			yep|=(l[i]&v)|(r[j]&v)|(l[i]==INF)|(r[j]==INF);
			if(yep) {
				ll res=(v? (1ll<<(63-__builtin_clzll(v))):INF);
				l[i]|=res, r[j]|=res;
			}
			if(len==1) cout<<(yep!=0);
		}
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

