#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e4+10;
const int M=2e3+10;
bool mem1;
int a[N][M];
ll n,Mod,f[N];
int prime[N];
vector<int> P;
void Get_Prime() {
	for(int i=2;i<N;i++) {
		if(!prime[i]) {
			P.push_back(i), prime[i]=i;
		}
		for(auto now:P) {
			if(1ll*now*i>=N) break;
			prime[now*i]=now;
			if(i%now==0) break;
		}
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	Get_Prime();
	cout<<P.size()<<endl;
//	return 0;
	
	cin>>n>>Mod;
	ll ans=1;
	f[0]=1;
	for(int i=1;i<=n;i++) {
		for(auto now:P) {
			if(now>i) break;
			f[i]=(f[i]+f[i-now]*now)%Mod;
		}
		ans=(ans+f[i])%Mod;
	}
	cout<<ans<<endl;
		
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

