#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
ll prime[N],n,Mod;
vector<ll> P;
void Get_Prime() {
	for(int i=2;i<N;i++) {
		if(!prime[i]) P.push_back(i);
		for(auto now:P) {
			if(1ll*now*i>=N) break;
			prime[now*i]=1;
			if(i%now==0) break;
		}
	}
}
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	Get_Prime();
	cin>>n>>Mod;
	ll ans=n%Mod;
	for(ll m=n,p=0;m;m>>=1,p++) {
		if(m&1) ans=Pow(ans,P[p]);
	}
	cout<<ans<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
