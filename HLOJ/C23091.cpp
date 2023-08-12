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
int n,x[N],y[N];
void solve() {
	cin>>n;
	int v1=INT_MAX,v2=INT_MAX,v3=INT_MIN,v4=INT_MIN;
	for(int i=1;i<=n;i++) {
		cin>>x[i]>>y[i];
		v1=min(v1,x[i]), v2=min(v2,y[i]);
		v3=max(v3,x[i]), v4=max(v4,y[i]);
	}
	for(int i=1;i<=n;i++) {
		if((x[i]==v1||x[i]==v3)&&(y[i]==v2||y[i]==v4)) return cout<<1<<endl, void();
	}
	cout<<2<<endl;
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

