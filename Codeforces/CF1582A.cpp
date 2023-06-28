#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
bool mem1;
void solve() {
	ll a,b,c;
	cin>>a>>b>>c;
	if(a>50) a-=2*(int)((a-50)/2);
	if(b>50) b-=2*(int)((b-50)/2);
	if(c>50) c-=2*(int)((c-50)/2);
	ll ans=1e18;
	for(int i=0;i<=a;i++)
		for(int j=0;j<=b;j++)
			for(int k=0;k<=c;k++) {
				ans=min(ans,abs((a-2*i)+2*(b-2*j)+3*(c-2*k)));
			}
	cout<<ans<<endl;
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

