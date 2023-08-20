#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const ll Mod=1e9+7;
bool mem1;
int n,p[N],phi[N];
vector<int> P;
void Get_Prime() {
	for(int i=2;i<N;i++) {
		if(!p[i]) P.push_back(i), phi[i]=(i-1);
		for(auto now:P) {
			if(1ll*now*i>=N) break;
			p[i*now]=1;
			if(i%now==0) {
				phi[i*now]=phi[i]*now;
				break;
			}
			phi[i*now]=phi[i]*(now-1);
		}
	}
}
int gcd(int x,int y) {
	if(!x) return y;
	return gcd(y%x,x);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	Get_Prime();
	ll ans=0;
	for(int i=1;i<=n;i++) {
		for(int j=2;j*i<n;j++) {
			ans=(ans+1ll*(n-i*j)/gcd(n-i*j,i)*i*phi[j])%Mod;
		}
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

