#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e4+10;
bool mem1;
int n,a[N],f[2][4010];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	memset(f,0x3f,sizeof(f)); f[0][0]=0;
	for(int i=1;i<=n;i++) {
		for(int j=0;j<=2000;j++) f[i&1][j]=0x3f3f3f3f;
		for(int j=0;j<=2000;j++) {
			f[i&1][max(0,j-a[i])]=min(f[i&1][max(0,j-a[i])],f[(i&1)^1][j]+a[i]);
			if(j+a[i]<2010) f[i&1][j+a[i]]=min(f[i&1][j+a[i]],max(f[(i&1)^1][j]-a[i],0));
		}
	}
	int ans=INT_MAX;
	for(int j=0;j<=2000;j++) ans=min(ans,j+f[n&1][j]);
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

