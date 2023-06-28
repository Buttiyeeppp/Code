#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
bool mem1;
void solve() {
	ll n,ans=1,cnt=0;
	cin>>n;
	for(int i=1,x;i<=n;i++) {
		cin>>x;
		if(x==0) ans*=2;
		if(x==1) cnt++;
	}
	cout<<ans*cnt<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	int T; cin>>T;
	while(T--) solve();
		
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

