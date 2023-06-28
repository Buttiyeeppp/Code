#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
ll a[N],ans[N],n;
ll gcd(ll x,ll y) {
	if(x==0) return y;
	else return gcd(y%x,x);
}
void solve() {
	ll cnt=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	while(n>=2&&(n%2==1)&&a[n]+a[n-1]==0) cnt+=2, n-=2;
	if(n==1) {
		n+=2, cnt-=2;
		ll G=abs(gcd(a[n-2],a[n-1]));
		ans[n-2]=-2*a[n-1]/G;
		ans[n-1]=a[n-2]/G;
		ans[n]=-a[n-2]/G;
	}
	else {
		for(int i=1;i<=n;i+=2) {
			if(i==n) continue;
			ll G;
			if(i+2==n) {
				G=abs(gcd(a[i],a[i+1]+a[i+2]));
				ans[i]=(a[i+1]+a[i+2])/G, ans[i+1]=-a[i]/G, ans[i+2]=-a[i]/G;
			}
			else {
				G=abs(gcd(a[i],a[i+1]));	
				ans[i]=a[i+1]/G, ans[i+1]=-a[i]/G;
			}
		}
	}
	for(int i=n+1;i<=n+cnt;i++) ans[i]=1;
	for(int i=1;i<=n+cnt;i++) cout<<ans[i]<<" ";
	return;
	
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

