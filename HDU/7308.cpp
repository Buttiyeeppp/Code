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
int n,a1[N],b1[N],c1[N],a[N],b[N],c[N],yep[N];
void solve() {
	cin>>n;
	set<PII> A,B,C;
	for(int i=1;i<=n;i++) {
		cin>>a1[i]>>b1[i]>>c1[i];
		cin>>a[i]>>b[i]>>c[i];
		yep[i]=0;
		A.insert({a1[i],i}), B.insert({b1[i],i}), C.insert({c1[i],i});
	}
	int mx,val,ans=INT_MAX;
	while(1) {
		int v1=(*(--A.end())).first-(*A.begin()).first;
		int v2=(*(--B.end())).first-(*B.begin()).first;
		int v3=(*(--C.end())).first-(*C.begin()).first;
		mx=max({v1,v2,v3});
		ans=min(ans,mx);
		int u;
		if(v1==mx) u=(*A.begin()).second;
		else if(v2==mx) u=(*B.begin()).second;
		else u=(*C.begin()).second;
		if(yep[u]) break;
		yep[u]=1;
		A.erase({a1[u],u}), B.erase({b1[u],u}), C.erase({c1[u],u});
		A.insert({a[u],u}), B.insert({b[u],u}), C.insert({c[u],u});
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
