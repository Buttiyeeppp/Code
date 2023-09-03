#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n;
vector<int> g[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,x;i<=n;i++) cin>>x, g[x].push_back(i);
	ll ans=0;
	for(int i=1;i<=n;i++) {
		ll c1=0, c2=0;
		for(int j=0;j<g[i].size();j++) {
			ans+=c1+c2*(g[i][j]-j);
			c1+=j-g[i][j], c2++;
		}
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

