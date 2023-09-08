#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
bool mem1;
ll n,a[N],f[N][N][2],s[N];
void solve() {
	for(int i=1;i<=n;i++)
		cin>>a[i], f[i][i][0]=a[i], f[i][i][1]=-a[i], s[i]=s[i-1]+a[i];
	for(int l=2;l<=n;l++)
		for(int i=1;i+l-1<=n;i++) {
			int j=i+l-1;
			f[i][j][0]=s[j]-s[i-1], f[i][j][1]=-(s[j]-s[i-1]);
			for(int k=i;k<j;k++) {
				f[i][j][0]=max(f[i][j][0],s[k]-s[i-1]+f[k+1][j][1]);
				f[i][j][1]=min(f[i][j][1],-(s[k]-s[i-1])+f[k+1][j][0]);
			}
			for(int k=i+1;k<=j;k++) {
				f[i][j][0]=max(f[i][j][0],s[j]-s[k-1]+f[i][k-1][1]);
				f[i][j][1]=min(f[i][j][1],-(s[j]-s[k-1])+f[i][k-1][0]);
			}
		}
	cout<<f[1][n][0]<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	while(cin>>n&&n) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

