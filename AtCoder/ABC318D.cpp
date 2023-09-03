#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=20;
bool mem1;
ll n,d[N][N],f[1<<N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++) cin>>d[i][j];
	ll ans=0;
	for(int s=0;s<(1<<n);s++) {
		for(int i=1;i<=n;i++) if(!((1<<(i-1))&s))
			for(int j=i+1;j<=n;j++) if(!((1<<(j-1))&s)) {
				f[s|(1<<(i-1))|(1<<(j-1))]=max(f[s|(1<<(i-1))|(1<<(j-1))],f[s]+d[i][j]);
			}
		ans=max(ans,f[s]);
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

