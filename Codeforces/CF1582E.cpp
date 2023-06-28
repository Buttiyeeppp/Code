#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const int M=460;
bool mem1;
int n,a[N];
ll f[N][M],sum[N];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i], sum[i]=sum[i-1]+a[i];
	f[n+1][0]=1e18;
	for(int i=n;i>=1;i--) {
		for(int j=0;j<=min(450,n-i+1);j++) {
			f[i][j]=f[i+1][j];
			if(f[i+j][j-1]>sum[i+j-1]-sum[i-1]) f[i][j]=max(f[i][j],sum[i+j-1]-sum[i-1]);
		}
	}
	int ans=0;
	for(int j=450;j>=1;j--) if(f[1][j]) { ans=j; break; }
	cout<<ans<<endl;
	for(int i=1;i<=n+1;i++)
		for(int j=0;j<=450;j++) f[i][j]=0;
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

