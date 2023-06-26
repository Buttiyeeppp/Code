#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e7+10;
const ll Mod=1e9+7;
bool mem1;
int ok[N];
ll fac[N],inv[N];
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
	inv[N-1]=Pow(fac[N-1],Mod-2);
	for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;

}
ll C(ll x,ll y) {
	if(x<y) return 0;
	return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	init();
	int l,r; ll cnt=0;
	cin>>l>>r;
	for(int i=l;i<=r;i++) {
		if(!ok[i]) {
			cnt++;
			for(int j=1;j*i<=r;j++) ok[j*i]=1;	
		}
	}
	ll ans=0;
	for(int i=cnt;i<=r-l+1;i++) {
		ans=(ans+i*fac[cnt]%Mod*C(i-1,cnt-1)%Mod*fac[r-l+1-cnt])%Mod;
	}
	cout<<ans<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
