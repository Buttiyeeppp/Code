#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int n; cin>>n;
	ll ans=0;
	priority_queue<int> q;
	for(int i=1,x;i<=n;i++) {
		cin>>x;
		q.push(x), q.push(x);
		ans+=abs(q.top()-x);
		q.pop();
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

